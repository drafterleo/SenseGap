#ifndef COLORPICTURE_H
#define COLORPICTURE_H

#include <QQuickPaintedItem>
#include "colorforms.h"

class ColorPicture : public QQuickPaintedItem
{
    Q_OBJECT
public:
    ColorPicture(QQuickItem *parent = 0);
    ~ColorPicture();
    void paint(QPainter *painter);

    void rgbMax(int &r, int &g, int &b);
    void rgbMin(int &r, int &g, int &b);

    Q_INVOKABLE void genRandom(int layers = 5);
    void lockColorBase();
    void shiftColors(int dR, int dG, int dB);
    void distortColors(int &distR, int &distG, int &distB);

    Q_INVOKABLE void assign(QQuickItem *item);
    ColorPicture &operator=(const ColorPicture &other);


signals:

public slots:

protected:
    void clearColorForms();

private:
    QVector <AbstractColorForm *> m_colorForms;
    QVector <QColor> m_colorBase;
};

#endif // COLORPICTURE_H
