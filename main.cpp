#include "mainwindow.h"
#include <QApplication>

#include "color.h"
#include "geometry.h"
#include "scene.h"
#include "camera.h"
#include "objects.h"
#include "material.h"
#include "raytracer.h"

int main(int argc, char *argv[])
{
    Color c(0.2, 0.3, 0.4);
    Color c1 = c + Color(0.1, 0.1, 0.1);
    qreal r = c.redF();
    gVector v(3.0, 4.0, 0.0);
    gVector v1 = v + gVector(0.1, 0.1, 0.1);
    qreal l = v.length();
    qreal p = Scene::camera().position().x;
    Ray ray = Scene::camera().ray(0.2, 0.3);
    gVector vn = v.normalize();
    Sphere s(v, 2.0);
    Triangle t(v, v, v);
    qreal mar = s.material.ambient().redF();
    qreal p1 = Scene::lights().first().position.x;
    gObject o1 = Scene::scene().objects().first();
    Color c3 = Raytracer::trace(ray);
    qreal q = 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
