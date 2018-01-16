#ifndef OBJECTS_H
#define OBJECTS_H

#include "qmath.h"
#include "geometry.h"
#include "camera.h"
#include "material.h"

struct Reflection
{
    Point fragPos;
    gVector normal;
    bool null;

    Reflection(Point const & pos, gVector const & n, bool null = false)
        : fragPos(pos), normal(n), null(null)
    { }
};

class gObject
{
public:
    Material material;

    gObject(Material const & mat) : material(mat)
    { }
    ~gObject(){}

    virtual Reflection cast(Ray const & r)
    {
        return Reflection(Point(), gVector(), true);
    }
};

class Sphere : public gObject
{
public:
    Point position;
    qreal radius;

    Sphere(Point const & pos, qreal r,
           Material const & mat = Material())
        : position(pos), radius(r), gObject(mat)
    { }

    Reflection cast(Ray const & r) override
    {
        gVector rc = r.src - position;

        qreal a = r.dir * r.dir;
        qreal b = 2 * (rc * r.dir);
        qreal c = rc * rc - radius * radius;

        qreal t = solve(a, b, c);
        if (t < 0)
            return Reflection(Point(), gVector(), true);

        Point x = r.src + r.dir * t;
        return Reflection(x, (x - position).normalize());
    }

private:
    qreal solve(qreal a, qreal b, qreal c)
    {
        qreal d = b * b - 4 * a * c;
        if (d >= 0)
        {
            qreal s1 = -b - qSqrt(d) / (2 * a);
            qreal s2 = -b + qSqrt(d) / (2 * a);

            if (s1 > 0 && s2 > 0)
                return qMin(s1, s2);
            else
                return qMax(s1, s2);
        }
        return -1;
    }
};

class Triangle : public gObject
{
public:
    Point a, b, c;

    Triangle(Point const & a, Point const & b, Point const & c,
             Material const & mat = Material())
        : a(a), b(b), c(c), gObject(mat)
    { }

    Reflection cast(Ray const & r) override
    {
        gVector n = (b - a).crossp(c - a).normalize();
        qreal t = -((r.src - a) * n) / (r.dir * n);

        Point x = r.src + r.dir * t;

        gVector v = (x - a).toBasis(b - a, c - a, n);
        if (t > 0.001 && qAbs(r.dir * n) < 0.0001 &&
            v.x >= 0 && v.y >= 0 && v.x + v.y <= 1)
            return Reflection(x, n);

        return Reflection(Point(), gVector(), true);
    }
};

#endif // OBJECTS_H
