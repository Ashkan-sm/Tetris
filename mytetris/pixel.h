#ifndef PIXEL_H
#define PIXEL_H
#include <QColor>
#include <QObject>

class pixel : public QObject
{
    Q_OBJECT
public:
    explicit pixel(QObject *parent = nullptr);
    pixel(QColor _color=Qt::white,QObject *parent = nullptr);
    QColor color;
signals:

};

#endif // PIXEL_H
