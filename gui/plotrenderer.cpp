#include "plotrenderer.h"

#include <QImage>
#include <QPainter>
#include <QtMath>
#include <QPen>
#include <cmath>

namespace {
double round_to(double value, int ndigits)
{
    double base = 1.0;
    for (; ndigits > 0; ndigits--)
        base *= 0.1;
    for (; ndigits < 0; ndigits++)
        base *= 10.0;
    return std::round(value * base) / base;
}

void get_scale(double vmin, double vmax, int grid_count,
               double *scalemin, double *scalemax,
               double *grid0, double *grid_step)
{
    *scalemin = vmin;
    *scalemax = vmax;

    double d = *scalemax - *scalemin;
    if (d == 0.0)
    {
        *scalemin -= 0.5;
        *scalemax += 0.5;
    }

    double step = (*scalemax - *scalemin) / static_cast<double>(qMax(1, grid_count));
    int ndigits = static_cast<int>(std::floor(std::log10(std::fabs(step))));
    *grid_step = round_to(step, ndigits);
    *grid0 = round_to(*scalemin, ndigits);
}
} // namespace

QPixmap PlotRenderer::render(const QList<double> &timestamps,
                             const QMap<int, QList<double>> &channelData,
                             const PlotOptions &options) const
{
    if (timestamps.isEmpty() || options.canvasSize.isEmpty())
        return QPixmap();

    QImage plot(options.canvasSize, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&plot);
    painter.fillRect(0, 0, plot.width(), plot.height(), Qt::black);

    double first_t = timestamps.first();
    double last_t = timestamps.last();
    double tWindow = options.timeScaleSeconds > 0.0 ? options.timeScaleSeconds : (last_t - first_t);
    if (tWindow <= 0.0)
        tWindow = 1e-6;

    double tscale_offset = options.timeOffsetRatio * (last_t - first_t);
    double Tmin = first_t;
    double Tmax = first_t + tWindow;
    double Tgrid0 = 0.0, Tstep = 0.0;
    get_scale(Tmin + tscale_offset, Tmax + tscale_offset, 10, &Tmin, &Tmax, &Tgrid0, &Tstep);

    double vWindow = options.voltageScaleVolts > 0.0 ? options.voltageScaleVolts : options.referenceVoltage;
    if (vWindow <= 0.0)
        vWindow = 1.0;
    double vscale_offset = options.voltageOffsetRatio * options.referenceVoltage;
    double Vmin = 0.0;
    double Vmax = Vmin + vWindow;
    double Vgrid0 = 0.0, Vstep = 0.0;
    get_scale(Vmin + vscale_offset, Vmax + vscale_offset, 10, &Vmin, &Vmax, &Vgrid0, &Vstep);

    const int margin = 15;
    painter.setPen(QPen(Qt::white, 1));
    painter.drawText(QRect(0, 0, plot.width(), plot.height()),
                     Qt::AlignLeft | Qt::AlignTop,
                     QString("TIME: %1 [ms] + %2  [ms/Cell];  "
                             "V: %3 [mV] + %4  [mV/Cell]")
                     .arg(Tgrid0 * 1000.0, 7, 'f', 3)
                     .arg(Tstep  * 1000.0, 7, 'f', 3)
                     .arg(Vgrid0 * 1000.0, 7, 'f', 3)
                     .arg(Vstep  * 1000.0, 7, 'f', 3));

    int minx = margin;
    int maxx = plot.width() - margin;
    int miny = margin;
    int maxy = plot.height() - margin;

    for (double t = Tgrid0; t <= Tmax; t += Tstep)
    {
        if (Tmax == Tmin)
            break;
        int x = minx + static_cast<int>((maxx - minx) * (t - Tmin) / (Tmax - Tmin));
        painter.setPen((t == Tgrid0) ? QPen(Qt::lightGray, 3) : QPen(Qt::darkGray, 1));
        painter.drawLine(x, margin, x, plot.height() - margin);
    }

    for (double v = Vgrid0; v <= Vmax; v += Vstep)
    {
        if (Vmax == Vmin)
            break;
        int y = maxy - static_cast<int>((maxy - miny) * (v - Vmin) / (Vmax - Vmin));
        painter.setPen((v == Vgrid0) ? QPen(Qt::lightGray, 3) : QPen(Qt::darkGray, 1));
        painter.drawLine(margin, y, plot.width() - margin, y);
    }

    double level = options.triggerLevelVolts;
    if (options.triggerEnabled)
        painter.setPen(QPen(Qt::lightGray, 3, Qt::DotLine));
    else
        painter.setPen(QPen(Qt::darkGray, 1, Qt::DotLine));
    if (Vmax != Vmin)
    {
        int y = maxy - static_cast<int>((maxy - miny) * (level - Vmin) / (Vmax - Vmin));
        painter.drawLine(margin, y, plot.width() - margin, y);
    }

    QList<int> channel_nums = channelData.keys();
    QVector<QPolygon> polys(channel_nums.size());
    QVector<QList<double>> channel_series(channel_nums.size());
    for (int j = 0; j < channel_nums.size(); ++j)
        channel_series[j] = channelData.value(channel_nums[j]);

    for (int i = 0; i < timestamps.size(); ++i)
    {
        if (Tmax == Tmin)
            break;
        int x = minx + static_cast<int>((maxx - minx) * (timestamps[i] - Tmin) / (Tmax - Tmin));
        for (int j = 0; j < channel_nums.size(); ++j)
        {
            int ch = channel_nums[j];
            if (channel_series[j].size() <= i || Vmax == Vmin)
                continue;
            int y = maxy - static_cast<int>((maxy - miny) * (channel_series[j][i] - Vmin) / (Vmax - Vmin));
            polys[j].append(QPoint(x, y));
        }
    }

    for (int j = 0; j < channel_nums.size(); ++j)
    {
        int ch = channel_nums[j];
        QColor color = (ch >= 0 && ch < options.channelColors.size()) ?
                    options.channelColors[ch] : Qt::white;
        painter.setPen(QPen(color, 1));
        painter.drawPolyline(polys[j]);
    }

    painter.end();
    return QPixmap::fromImage(plot);
}
