#include "factswindow.h"
#include "ui_factswindow.h"

Factswindow::Factswindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Factswindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&Factswindow::button_clicked);
}

Factswindow::~Factswindow()
{
    delete ui;
}
