#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <qmath.h>

class gVector
{
public:
    qreal x, y, z;

    gVector(qreal x = 0.0, qreal y = 0.0, qreal z = 0.0) : x(x), y(y), z(z)
    { }

    gVector operator +(gVector const & other) const
    {
        return gVector(x + other.x, y + other.y, z + other.z);
    }

    gVector operator -(gVector const & other) const
    {
        return gVector(x - other.x, y - other.y, z - other.z);
    }

    gVector operator *(qreal k) const
    {
        return gVector(x * k, y * k, z * k);
    }

    gVector operator /(qreal k) const
    {
        return gVector(x / k, y / k, z / k);
    }

    qreal operator *(gVector const & other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    qreal length() const
    {
        return qSqrt(*this * *this);
    }

    gVector normalize() const
    {
        return *this / length();
    }

    gVector crossp(gVector const & o) const
    {
        return gVector(y * o.z - z * o.y,
                       z * o.x - x * o.z,
                       x * o.y - y * o.x);
    }

    gVector reflect(gVector const & n) const
    {
        gVector v(*this);
        return v - n * (v * n) * 2;
    }

    gVector toBasis(gVector const & bv1,
                    gVector const & bv2,
                    gVector const & bv3)
    {
        qreal d = det(bv1, bv2, bv3);
        return gVector(det(*this, bv2, bv3),
                       det(bv1, *this, bv3),
                       det(bv1, bv2, *this)) / d;
    }

private:
    qreal det(gVector const & bv1,
              gVector const & bv2,
              gVector const & bv3)
    {
        return bv1.x * bv2.y * bv3.z +
               bv1.y * bv2.z * bv3.x +
               bv1.z * bv2.x * bv3.y -
               bv1.z * bv2.y * bv3.x -
               bv1.y * bv2.x * bv3.z -
               bv1.x * bv2.z * bv3.y;
    }
};

typedef gVector Point;

#endif // GEOMETRY_H
