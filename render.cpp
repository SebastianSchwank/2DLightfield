#include "render.h"


static unsigned int x,iteration;

renderer::renderer(data *Daten,unsigned long scale)
{
    _Daten = Daten;
    _RenderOut = new QImage ( scale, scale, QImage::Format_RGB32);
    _scale = scale;
    RenderTask = new raytracer(_Daten,_scale);
    QRgb value;
    value = qRgb(0, 0, 0); // Fill the whole image Black
    _RenderOut->fill(value);
    for(unsigned int x = 0; x < scale; x++)
    {
        QVector<renderPixel> Row;
        for(unsigned int y = 0; y < scale; y++)
        {
            renderPixel value;
            value.r = 0;
            value.g = 0;
            value.b = 0;
            Row.push_back(value);
        }
        RgbiImage.push_back(Row);
    }
    x = 0;
    iteration = 1;
}

double renderer::renderSp(unsigned long samples)
{
    double time = 0;

    while(x < _scale)
    {
        //#pragma omp parallel for
        for(unsigned int y = 0;y < _scale; y++)
        {
            renderPixel value;
            QRgb RgbVal;

            value = RenderTask->renderPix(x,y);
            RgbiImage[y][x].r = (double) value.r;
            RgbiImage[y][x].g = (double) value.g;
            RgbiImage[y][x].b = (double) value.b;
            RgbVal = qRgb(limit(RgbiImage[y][x].r)*255,limit(RgbiImage[y][x].g)*255,limit(RgbiImage[y][x].b)*255);
            _RenderOut->setPixel(x,y,RgbVal);
        }

        x++;

        if(x % samples == 0 && x < _scale)
        {

            for(unsigned int y = 0; y < _scale; y++)
            {
                QRgb RgbVal;
                RgbVal = qRgb(255,0,0);
                _RenderOut->setPixel(x,y,RgbVal);
            }
            return 0;
        }

    }
    x = 0;
    iteration++;
    return time;
}

QImage renderer::getImage()
{
    return *_RenderOut;
}

double renderer::limit(double input)
{
    if(input > 1.0)
    {
        return 1.0;
    }
    return input;
}
