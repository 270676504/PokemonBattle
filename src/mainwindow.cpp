#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bgPix(":/image/Time-For-Lunch-2.jpg");

    QGraphicsScene *scene =new QGraphicsScene (-350, -350, 700, 700);
    ui->graphicsView->setScene(scene);

    QGraphicsItem *buttonParent = new QGraphicsRectItem;
    Button *ellipseButton = new Button(QPixmap(":/image/image/1.jpg"), buttonParent);
    Button *figure8Button = new Button(QPixmap(":/image/image/1.jpg"), buttonParent);
    Button *randomButton = new Button(QPixmap(":/image/image/1.jpg"), buttonParent);
    Button *tiledButton = new Button(QPixmap(":/image/image/1.jpg"), buttonParent);
    Button *centeredButton = new Button(QPixmap(":/image/image/1.jpg"), buttonParent);

    ellipseButton->setPos(-100, -100);
    figure8Button->setPos(100, -100);
    randomButton->setPos(0, 0);
    tiledButton->setPos(-100, 100);
    centeredButton->setPos(100, 100);

    scene->addItem(buttonParent);
    buttonParent->setTransform(QTransform::fromScale(0.75, 0.75), true);
    buttonParent->setPos(200, 200);
    buttonParent->setZValue(65);

    ui->graphicsView->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Animated Tiles"));
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setBackgroundBrush(bgPix);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);


    connect(ellipseButton,&Button::pressed,this,[&](){
        qDebug()<<"clicked";
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
