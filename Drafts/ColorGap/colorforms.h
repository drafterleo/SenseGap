#ifndef COLORFORMS_H
#define COLORFORMS_H

#include <QRectF>
#include <QColor>
#include <QPainter>

class AbstractColorForm
{
public:
    AbstractColorForm(const QRectF & aRect, const QColor & aColor, qreal anAngle = 0);
    virtual ~AbstractColorForm(){}
    virtual void paintTo(QPainter *painter) = 0;
    virtual AbstractColorForm *clone() = 0;

    QRectF rect;
    qreal  angle;
    QColor color;
};


class RectColorForm: public AbstractColorForm
{
public:
    RectColorForm(const QRectF & aRect, const QColor & aColor, qreal anAngle = 0);
    void paintTo(QPainter *painter);
    AbstractColorForm *clone();
};


class EllipseColorForm: public AbstractColorForm
{
public:
    EllipseColorForm(const QRectF & aRect, const QColor & aColor, qreal anAngle = 0);
    void paintTo(QPainter *painter);
    AbstractColorForm *clone();
};



#endif // COLORFORMS_H
