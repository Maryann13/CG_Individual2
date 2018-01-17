#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"

struct Ray
{
    Point src;
    gVector dir;

    Ray(Point const & src, gVector const & dir)
        : src(src), dir(dir)
    { }
};

class Camera
{
    Point f_position;
    qreal f_width, f_height;

public:
    Camera(Point const & pos, qreal w, qreal h)
        : f_position(pos), f_width(w), f_height(h)
    { }

    const Point& position() const { return f_position; }

    qreal width() const { return f_width; }

    qreal height() const { return f_height; }

    Ray ray(qreal x, qreal y) const
    {
        return Ray(f_position,
                   gVector(f_width * (x - 0.5),
                           f_height * (y - 0.5), -1.0).normalize());
    }
};

#endif // CAMERA_H
