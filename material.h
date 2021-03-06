#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

class Material
{
    Color f_specular, f_diffuse, f_ambient, f_reflect;
    qreal f_shininess;

public:
    Material(Color const & s = Color(0.0, 0.0, 0.0),
             Color const & d = Color(0.8, 0.8, 0.8),
             Color const & a = Color(0.2, 0.2, 0.2),
             qreal alpha = 0.0,
             Color const & r = Color())
        : f_specular(s), f_diffuse(d), f_ambient(a),
          f_reflect(r),
          f_shininess(alpha)
    { }

    const Color& specular() const { return f_specular; }

    const Color& diffuse() const { return f_diffuse; }

    const Color& ambient() const { return f_ambient; }

    const Color& reflect() const { return f_reflect; }

    qreal shininess() const { return f_shininess; }

    static Material metal(Color const & c)
    {
        return Material(c * 0.3, c * 0.15, c * 0.15, 290.0, c * 0.24);
    }

    static Material gold() { return metal(Color(0.9, 0.9, 0.3)); }

    static Material silver() { return metal(Color(0.9, 0.9, 0.9)); }

    static Material bronze() { return metal(Color(0.9, 0.6, 0.3)); }

    static Material wallpaper()
    {
        Color c(0.97, 0.93, 0.69);
        return Material(c * 0.6, c * 0.6, c * 0.3, 10.0, c * 0.1);
    }
};

#endif // MATERIAL_H
