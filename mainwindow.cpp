#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "raytracer.h"

#include <QtWidgets>

void showImage(QGraphicsView * view, QGraphicsPixmapItem * pixmapItem,
               QImage const & img)
{
    pixmapItem->setVisible(true);
    QPixmap pixmap = QPixmap::fromImage(img);
    pixmapItem->setPixmap(pixmap);
    view->scene()->setSceneRect(0, 0, pixmap.width(), pixmap.height());
    view->fitInView(pixmapItem, Qt::KeepAspectRatio);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(nullptr);
    pixmapItem = new QGraphicsPixmapItem();

    ui->graphicsView->setScene(scene);
    scene->addItem(pixmapItem);

    quint64 w = ui->graphicsView->width();
    quint64 h = ui->graphicsView->height();

    imgRendered = QImage(w, h, QImage::Format_ARGB32);

    quint64 pixCnt = w * h;
    QRgb* iCp = (QRgb*)imgRendered.bits();

    for (quint64 i = 0; i < pixCnt; ++i)
        iCp[i] = Raytracer::getFrag((qreal)(i / pixCnt) / w,
                                    (qreal)(i % pixCnt) / h).rgb();

    showImage(ui->graphicsView, pixmapItem, imgRendered);
}

MainWindow::~MainWindow()
{
    delete ui;
}
