#include "colorpicture.h"
#include <QtDebug>

ColorPicture::ColorPicture(QQuickItem *parent): QQuickPaintedItem(parent)
{
    setAntialiasing(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    genRandom(5);
}

ColorPicture::~ColorPicture()
{
    clearColorForms();
}

void ColorPicture::clearColorForms()
{
    while (m_colorForms.isEmpty() == false) {
        delete m_colorForms.takeFirst();
    }
    update();
}

void ColorPicture::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << "mouse";
}

void ColorPicture::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "mouse press";
}

void ColorPicture::paint(QPainter *painter)
{
    painter->setBrush(Qt::black);
    painter->drawRect(0, 0, width(), height());
    for (int i = 0; i < m_colorForms.count(); ++i) {
        m_colorForms.at(i)->paintTo(painter);
    }
}

void ColorPicture::rgbMax(int &r, int &g, int &b)
{
    r = g = b = 0;
    for (int i = 0; i < m_colorForms.count(); ++i) {
        QColor color = m_colorForms.at(i)->color;
        if (color.red() > r)   r = color.red();
        if (color.green() > g) g = color.green();
        if (color.blue() > b)  b = color.blue();
    }
}

void ColorPicture::rgbMin(int &r, int &g, int &b)
{
    r = g = b = 255;
    for (int i = 0; i < m_colorForms.count(); ++i) {
        QColor color = m_colorForms.at(i)->color;
        if (color.red() < r)   r = color.red();
        if (color.green() < g) g = color.green();
        if (color.blue() < b)  b = color.blue();
    }
}

QColor rndColor(bool useAlpha = false)
{
    int r = qrand() % 155 + 50;
    int g = qrand() % 155 + 50;
    int b = qrand() % 155 + 50;
    int alpha = 255;
    if (useAlpha) {
        alpha = qrand() % 250 + 5;
    }
    return QColor(r, g, b, alpha);
}

QRectF rndRect(int minW, int minH, int maxW, int maxH, qreal scalar)
{
    int w = qrand() % (maxW - minW) + minW;
    int h = qrand() % (maxH - minH) + minH;
    int maxX = scalar - w;
    int maxY = scalar - h;
    int x = qrand() % maxX;
    int y = qrand() % maxY;
    return QRectF(x/scalar, y/scalar, w/scalar, h/scalar);
}

void ColorPicture::genRandom(int layers)
{
    clearColorForms();
    RectColorForm *bgForm = new RectColorForm(QRectF(0.0, 0.0, 1.0, 1.0), rndColor());
    m_colorForms.append(bgForm);
    int scalar = 1000;
    for(int i = 0; i < layers; i++) {
        int min = scalar/(i + 2);
        int max = scalar/(i + 1);
        int formCount = qrand() % 15 + 5;
        for(int f = 0; f < formCount; ++f) {
            QRectF formRect = rndRect(min, min, max, max, scalar);
            qreal angle = qrand() % 360;
            bool useAlpha = (qrand() % 2) > 1;
            int formType = qrand() % 2;
            if (formType == 0) {
                m_colorForms.append(new EllipseColorForm(formRect, rndColor(useAlpha), angle));
            } else {
                m_colorForms.append(new RectColorForm(formRect, rndColor(useAlpha), angle));
            }
        }
    }
    lockColorBase();
    update();
}

void ColorPicture::lockColorBase()
{
    m_colorBase.clear();
    for (int i = 0; i < m_colorForms.count(); ++i) {
       m_colorBase.append(m_colorForms.at(i)->color);
    }
}

void ColorPicture::shiftColors(int dR, int dG, int dB)
{
    for (int i = 0; i < m_colorForms.count(); ++i) {
        int r, g, b, a;
        QColor formColor = m_colorBase[i];
        formColor.getRgb(&r, &g, &b, &a);
        r = qBound(0, r + dR, 255);
        g = qBound(0, g + dG, 255);
        b = qBound(0, b + dB, 255);
        m_colorForms[i]->color = QColor(r, g, b, a);
    }
    update();
}

void ColorPicture::distortColors(int &distR, int &distG, int &distB)
{
    int minR, minG, minB;
    int maxR, maxG, maxB;
    rgbMin(minR, minG, minB);
    rgbMax(maxR, maxG, maxB);
    distR = qrand() % 50 - 25;
    distG = qrand() % 50 - 25;
    distB = qrand() % 50 - 25;

    for (int i = 0; i < m_colorForms.count(); ++i) {
        int r, g, b, a;
        QColor formColor = m_colorForms.at(i)->color;
        formColor.getRgb(&r, &g, &b, &a);
        r = qBound(0, r + distR, 255);
        g = qBound(0, g + distG, 255);
        b = qBound(0, b + distB, 255);
        m_colorForms[i]->color = QColor(r, g, b, a);
    }
    lockColorBase();
    update();
}

void ColorPicture::assign(QQuickItem *item)
{
    ColorPicture *pic = dynamic_cast<ColorPicture *>(item);
    if (pic) {
        *this = *pic;
    }
}

ColorPicture &ColorPicture::operator=(const ColorPicture &other)
{
    clearColorForms();
    for (int i = 0; i < other.m_colorForms.count(); ++ i) {
        m_colorForms.append(other.m_colorForms.at(i)->clone());
    }
    lockColorBase();
    update();
    return *this;
}



