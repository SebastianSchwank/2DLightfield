#ifndef RENDER_H
#define RENDER_H

#include <QImage>
#include <data.h>
#include <raytracer.h>
#include <qmath.h>
#include <QCoreApplication>

class renderer
{
public:
    renderer(data *Daten,unsigned long scale);
    double renderSp(unsigned long samples);
    QImage getImage();

private:
    double limit(double input);

    raytracer *RenderTask;
    QImage *_RenderOut;
    data *_Daten;
    unsigned long _scale;
    QVector< QVector<renderPixel> > RgbiImage;
};



#endif // RENDER_H
