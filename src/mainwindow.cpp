#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maininfo.h"
#include <QGraphicsProxyWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bgPix(":/image/Time-For-Lunch-2.jpg");

    QGraphicsScene *scene =new QGraphicsScene (-350, -350, 700, 700);
    ui->graphicsView->setScene(scene);

    MainInfo* info1=new MainInfo();
    MainInfo* info2=new MainInfo();
    QGraphicsProxyWidget *gpWidget=scene->addWidget(info1);
    gpWidget->setPos(-0,0);

    gpWidget=scene->addWidget(info2);
    gpWidget->setPos(-300,-300);


    QGraphicsItem *buttonParent = new QGraphicsRectItem;
    QPixmap pix(":/image/image/fire.png");
    int width=pix.width()+10;
    pix=pix.scaled(90,90);
    Button *ellipseButton = new Button(pix, buttonParent);
    Button *figure8Button = new Button(pix, buttonParent);
    Button *tiledButton = new Button(pix, buttonParent);
    Button *centeredButton = new Button(pix, buttonParent);
    ellipseButton->setPos(0-width*1.5, 0);
    figure8Button->setPos(0-width/2, 0);
    tiledButton->setPos(width/2, 0);
    centeredButton->setPos(width*1.5, 0);
    scene->addItem(buttonParent);
    buttonParent->setTransform(QTransform::fromScale(0.75, 0.75), true);
    buttonParent->setPos(-200, 200);
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
