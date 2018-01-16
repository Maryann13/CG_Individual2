#ifndef COLOR_H
#define COLOR_H

#include <QColor>

class Color : public QColor
{
public:
    Color(qreal r = 0.0, qreal g = 0.0, qreal b = 0.0, qreal alpha = 1.0)
    {
        setRedF(r), setGreenF(g), setBlueF(b), setAlphaF(alpha);
    }

    Color operator +(Color const & other) const
    {
        Color c(*this);
        c.setRedF  (qMin(1.0, redF() + other.redF()));
        c.setGreenF(qMin(1.0, greenF() + other.greenF()));
        c.setBlueF (qMin(1.0, blueF() + other.blueF()));
        c.setAlphaF(qMin(1.0, alphaF() + other.alphaF()));
        return c;
    }

    Color operator *(qreal k) const
    {
        Color c(*this);
        c.setRedF  (qMin(1.0, redF() * k));
        c.setGreenF(qMin(1.0, greenF() * k));
        c.setBlueF (qMin(1.0, blueF() * k));
        c.setAlphaF(qMin(1.0, alphaF() * k));
        return c;
    }
};

#endif // COLOR_H
