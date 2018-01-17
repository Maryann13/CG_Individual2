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
    QList<gObject *> f_objects;

    Scene()
    {
        addRoom(Point(0, 0, -15), 50.0, Material::wallpaper());
        addCube(Point(-7, 8.5, -13), 7.0, Material::silver());
        f_objects << new Sphere(Point(-2.0, 4.6, -17.5), 4.5, Material::bronze())
                  << new Sphere(Point(5.9, 3.78, -10), 4.5, Material::gold());
    }

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

public:
    ~Scene()
    {
        for (auto it = f_objects.begin(); it < f_objects.end(); ++it)
            delete *it;
    }

    static const Camera& camera()
    {
        static Camera cam(Point(0.0, 0.0, 0.0), 2.0, 2.0);
        return cam;
    }

    static const QList<Light>& lights()
    {
        static QList<Light> ls({
            Light(Point(-4.0, 1.5, -12.0), Color(0.0, 0.0, 0.8)),
            Light(Point(2.0, 0.5, -12.0), Color(1.0, 0.2, 0.2)),
            Light(Point(-4.0, 2.0, -12.0), Color(1.0, 1.0, 1.0))
        });
        return ls;
    }

    const QList<gObject *>& objects() const { return f_objects; }

    static Scene& scene()
    {
        static Scene s;
        return s;
    }

    void addPlane(Point const & a, Point const & b,
                         Point const & c, Point const & d,
                         Material const & mat = Material())
    {
        f_objects << new Triangle(a, b, c, mat) << new Triangle(b, d, c, mat);
    }

    void addRoom(Point const & pos, qreal size,
                        Material const & mat = Material())
    {
        gVector a, b, c, d, e, f, g, h;
        qreal sz = size / 2;
        a = pos + gVector(-1.0,  0.7, -1.0) * sz;
        b = pos + gVector( 1.0,  0.7, -1.0) * sz;
        c = pos + gVector(-1.0,  0.7,  1.0) * sz;
        d = pos + gVector( 1.0,  0.7,  1.0) * sz;
        e = pos + gVector(-1.0, -0.7, -1.0) * sz;
        f = pos + gVector( 1.0, -0.7, -1.0) * sz;
        g = pos + gVector(-1.0, -0.7,  1.0) * sz;
        h = pos + gVector( 1.0, -0.7,  1.0) * sz;

        addPlane(a, c, b, d, mat);
        addPlane(e, f, g, h, mat);
        addPlane(c, g, d, h, mat);
        addPlane(d, h, b, f, mat);
        addPlane(b, f, a, e, mat);
        addPlane(a, e, c, g, mat);
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
        addPlane(e, g, f, h, mat);
        addPlane(c, d, g, h, mat);
        addPlane(d, b, h, f, mat);
        addPlane(b, a, f, e, mat);
        addPlane(a, c, e, g, mat);
    }
};

#endif // SCENE_H
