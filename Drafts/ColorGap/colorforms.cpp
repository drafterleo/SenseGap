#include "colorforms.h"

AbstractColorForm::AbstractColorForm(const QRectF & aRect, const QColor & aColor, qreal anAngle)
    : rect(aRect),
      color(aColor),
      angle(anAngle)
{

}

/* ----------------------------------------------------------------------- */

RectColorForm::RectColorForm(const QRectF & aRect, const QColor & aColor, qreal anAngle)
    : AbstractColorForm(aRect, aColor, anAngle)
{

}

void RectColorForm::paintTo(QPainter *painter)
{
    if (painter) {
        QRect drawArea = painter->window();
        int x = qRound(rect.left() * drawArea.width());
        int y = qRound(rect.top() * drawArea.height());
        int w = qRound(rect.width() * drawArea.width());
        int h = qRound(rect.height() * drawArea.height());
        painter->setPen(color);
        painter->setBrush(color);
        if (angle == 0) {
            painter->drawRect(x, y, w, h);
        } else {
            painter->save();
            painter->translate(x + w/2, x + h/2);
            painter->rotate(angle);
            painter->drawRect(-(x + w/2), -(y + h/2), w, h);
            painter->restore();
        }
    }
}

AbstractColorForm *RectColorForm::clone()
{
    return new RectColorForm(rect, color, angle);
}

/* ----------------------------------------------------------------------- */

EllipseColorForm::EllipseColorForm(const QRectF & aRect, const QColor & aColor, qreal anAngle)
    : AbstractColorForm(aRect, aColor, anAngle)
{

}

void EllipseColorForm::paintTo(QPainter *painter)
{
    if (painter) {
        QRect drawArea = painter->window();
        int x = qRound(rect.left() * drawArea.width());
        int y = qRound(rect.top() * drawArea.height());
        int w = qRound(rect.width() * drawArea.width());
        int h = qRound(rect.height() * drawArea.height());
        painter->setPen(color);
        painter->setBrush(color);
        if (angle == 0) {
            painter->drawEllipse(x, y, w, h);
        } else {
            painter->save();
            painter->translate(x + w/2, x + h/2);
            painter->rotate(angle);
            painter->drawEllipse(-(x + w/2), -(y + h/2), w, h);
            painter->restore();
        }
    }
}

AbstractColorForm *EllipseColorForm::clone()
{
    return new EllipseColorForm(rect, color, angle);
}
