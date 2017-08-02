#include "maininfo.h"
#include "ui_maininfo.h"

MainInfo::MainInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainInfo)
{
    ui->setupUi(this);
}

MainInfo::~MainInfo()
{
    delete ui;
}
