#include "render.h"


static unsigned int xi;

renderer::renderer(data *Daten,unsigned long scale,QuadTree *_QTree)
{
    _Daten = Daten;
    _RenderOut = new QImage ( scale, scale, QImage::Format_RGB32);
    _scale = scale;
    RenderTask = new raytracer(_Daten,_scale,_QTree);
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
            value.i = 0;
            Row.push_back(value);
        }
        RgbiImage.push_back(Row);
    }
    xi = 1;
}

double renderer::renderSp(unsigned long samples)
{
    double time = 0;

    while(xi < _scale-1)
    {
        //#pragma omp parallel for
        for(unsigned int y = 1;y < _scale-1; y++)
        {
            renderPixel value;

            value = RenderTask->renderPix(xi,y,&RgbiImage);
            (RgbiImage)[y][xi].i++;
            (RgbiImage)[y][xi].r = ((RgbiImage)[y][xi].r * (RgbiImage)[y][xi].i + value.r)/((RgbiImage)[y][xi].i + 1);
            (RgbiImage)[y][xi].g = ((RgbiImage)[y][xi].g * (RgbiImage)[y][xi].i + value.g)/((RgbiImage)[y][xi].i + 1);
            (RgbiImage)[y][xi].b = ((RgbiImage)[y][xi].b * (RgbiImage)[y][xi].i + value.b)/((RgbiImage)[y][xi].i + 1);
        }

        xi++;

        if(xi % samples == 0 && xi < _scale-5)
        {
            for(int x = 0; x < _scale; x++)
            {
                for(int y = 0; y < _scale; y++)
                {
                    QRgb RgbVal;
                    RgbVal = qRgb(limit(RgbiImage[y][x].r)*255,limit(RgbiImage[y][x].g)*255,limit(RgbiImage[y][x].b)*255);
                    _RenderOut->setPixel(x,y,RgbVal);
                }
            }

            for(unsigned int y = 5; y < _scale-5; y++)
            {
                QRgb RgbVal;
                RgbVal = qRgb(255,0,0);
                _RenderOut->setPixel(xi,y,RgbVal);
            }
            return 0;
        }

    }
    xi = 1;
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
