#ifndef PLOTRENDERER_H
#define PLOTRENDERER_H

#include <QColor>
#include <QList>
#include <QMap>
#include <QPixmap>
#include <QSize>
#include <QVector>

struct PlotOptions
{
    double timeScaleSeconds;
    double timeOffsetRatio;
    double voltageScaleVolts;
    double voltageOffsetRatio;
    double referenceVoltage;
    double triggerLevelVolts;
    bool triggerEnabled;
    QSize canvasSize;
    QVector<QColor> channelColors;
};

class PlotRenderer
{
public:
    PlotRenderer() = default;

    QPixmap render(const QList<double> &timestamps,
                   const QMap<int, QList<double>> &channelData,
                   const PlotOptions &options) const;
};

#endif // PLOTRENDERER_H
