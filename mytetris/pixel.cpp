#include "pixel.h"

pixel::pixel(QObject *parent)
    : QObject{parent}
{

}

pixel::pixel(QColor _color, QObject *parent)
{
    color=_color;
}
