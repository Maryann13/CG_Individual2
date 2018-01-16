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
    static Color trace(Ray const & ray)
    {
        gObject obj = Scene::scene().objects().first();
        Reflection refl = obj.cast(ray);
        bool lighted = false;
        foreach (auto o, Scene::scene().objects())
        {
            Reflection r = o.cast(ray);
            if (lighted = !r.null && zComp(ray.src)(r, refl))
                refl = r, obj = o;
        }
        if (!lighted)
            return Color();
        return lighting(obj.material, refl.fragPos, refl.normal, ray);
    }

    static Color getFrag(qreal x, qreal y)
    {
        return trace(Scene::camera().ray(x, y));
    }

private:
    static Color lighting(Material const & mat, Point const & pos,
                          gVector const & n, Ray const & ray)
    {
        Color res = mat.ambient();
        bool guard = false;
        foreach (auto light, Scene::lights())
        {
            gVector l = (light.position - pos).normalize();
            foreach (auto o, Scene::scene().objects()) {
                if (guard = intersects(o.cast(Ray(pos, l)), pos, light.position))
                    break;
            }
            if (guard)
                break;
            gVector h = (l - ray.dir).normalize();
            Color i = light.color * (10 / (light.position - pos).length());

            res = res + mat.diffuse() * (l * n) +
                        mat.specular() * qPow(h * n, mat.shininess());
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
          return (lhs.fragPos - raySrc).length() <
                 (rhs.fragPos - raySrc).length();
      }

      zComp(Point const & rs) : raySrc(rs)
      { }
    };
};

#endif // RAYTRACER_H
