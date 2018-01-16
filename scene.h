#ifndef SCENE_H
#define SCENE_H

#include "geometry.h"
#include "camera.h"
#include "color.h"
#include "objects.h"
#include "material.h"

struct Light
{
    Point position;
    Color color;

    Light(Point const & pos, Color const & c)
        : position(pos), color(c)
    { }
};

class Scene
{
protected:
    QList<gObject> f_objects;

    Scene()
    {
        addCube(Point(), 15.0, Material::wallpaper());
        addCube(Point(5.0, -5.0, -16.0), 8.0, Material::silver());
        f_objects << Sphere(Point(0, -8.0, -11.0), 1.5, Material::bronze())
                  << Sphere(Point(-4, -8.5, -12.0), 1.8, Material::gold());
    }

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

public:

    static const Camera& camera()
    {
        static Camera cam(Point(0.0, 0.0, 0.0), 1.0, 1.0);
        return cam;
    }

    static const QList<Light>& lights()
    {
        static QList<Light> ls({
            Light(Point(1.0, -2.0, -12.0), Color(0.6, 0.0, 0.0)),
            Light(Point(-2.0, -2.0, -9.0), Color(0.0, 0.0, 0.8)),
            Light(Point(-2.0, 1.0, -12.0), Color(0.0, 0.4, 0.0))
        });
        return ls;
    }

    const QList<gObject>& objects() const { return f_objects; }

    static Scene& scene()
    {
        static Scene s;
        return s;
    }

    void addPlane(Point const & a, Point const & b,
                         Point const & c, Point const & d,
                         Material const & mat = Material())
    {
        f_objects << Triangle(a, b, c, mat) << Triangle(b, d, c, mat);
    }

    void addCube(Point const & pos, qreal size,
                        Material const & mat = Material())
    {
        gVector a, b, c, d, e, f, g, h;
        qreal sz = size / 2;
        a = pos + gVector(-1.0,  1.0, -1.0) * sz;
        b = pos + gVector( 1.0,  1.0, -1.0) * sz;
        c = pos + gVector(-1.0,  1.0,  1.0) * sz;
        d = pos + gVector( 1.0,  1.0,  1.0) * sz;
        e = pos + gVector(-1.0, -1.0, -1.0) * sz;
        f = pos + gVector( 1.0, -1.0, -1.0) * sz;
        g = pos + gVector(-1.0, -1.0,  1.0) * sz;
        h = pos + gVector( 1.0, -1.0,  1.0) * sz;

        addPlane(a, b, c, d, mat);
        addPlane(e, f, g, h, mat);
        addPlane(c, d, g, h, mat);
        addPlane(d, b, h, f, mat);
        addPlane(b, a, f, e, mat);
        addPlane(a, c, e, g, mat);
    }
};

#endif // SCENE_H
