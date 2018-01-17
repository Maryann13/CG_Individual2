#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <qmath.h>
#include "color.h"
#include "camera.h"
#include "material.h"
#include "geometry.h"
#include "objects.h"
#include "scene.h"

class Raytracer
{
public:
    static Color trace(Ray const & ray, gObject * object, int depth = 1)
    {
        if (depth == 0)
            return Color();
        gObject * obj = Scene::scene().objects().first();
        Reflection refl = obj->cast(ray);
        bool lighted = false;

        foreach (auto o, Scene::scene().objects())
        {
            if (o == object)
                break;
            Reflection r = o->cast(ray);
            if (!r.null && (refl.null || zComp(ray.src)(r, refl)))
                refl = r, obj = o, lighted = true;
        }
        if (!lighted)
            return Color();
        return lighting(obj, refl, ray, depth);
    }

    static Color getFrag(qreal x, qreal y)
    {
        return trace(Scene::camera().ray(x, y), nullptr, 3);
    }

private:
    static Color lighting(gObject * obj,
                          Reflection const & r, Ray const & ray,
                          int depth)
    {
        Color res = obj->material.ambient();
        bool guard = false;
        foreach (auto light, Scene::lights())
        {
            gVector l = (r.fragPos - light.position).normalize();
            foreach (auto o, Scene::scene().objects()) {
                if (guard = o != obj && intersects(o->cast(Ray(r.fragPos, gVector() - l)),
                                                   r.fragPos, light.position))
                    break;
            }
            if (guard)
                continue;
            gVector h = (ray.dir + l).normalize();
            Color i = light.color * (10 / (light.position - r.fragPos).length());

            res = res + (obj->material.diffuse() * (l * r.normal) +
                  obj->material.specular() * qPow(h * r.normal,
                                                  obj->material.shininess())) * i +
                  obj->material.reflect()
                        * Raytracer::trace(Ray(r.fragPos,
                                               ray.dir.reflect(r.normal)), obj, depth - 1);
        }
        return res;
    }

    static bool intersects(Reflection const & refl,
                           Point const & fpos, Point const & lpos)
    {
        if (refl.null)
            return false;
        else
            return (refl.fragPos - fpos).length() <
                   (lpos - fpos).length();
    }

    struct zComp {
      Point raySrc;

      bool operator ()(Reflection const & lhs,
                       Reflection const & rhs)
      {
          return (lhs.fragPos - raySrc).length() <=
                 (rhs.fragPos - raySrc).length();
      }

      zComp(Point const & rs) : raySrc(rs)
      { }
    };
};

#endif // RAYTRACER_H
