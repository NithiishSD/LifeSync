#ifndef DONOR_PAGE_H
#define DONOR_PAGE_H

#include <QWidget>
#include "ui_donor_page.h"
#include <map>
#include <QtSvgWidgets/QtSvgWidgets>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSvgRenderer>
//#include <QGraphicsSvgItem>
#include <QPainterPath>
#include <QFile>
#include <QDomDocument>
namespace Ui {
class Donor_page;
}

class OrganItem;

class Donor_page : public QWidget
{
    Q_OBJECT

public:
    explicit Donor_page(QWidget *parent = nullptr);
    QVBoxLayout * getbodylayout();
    QPushButton* getregisterbutton();
    void set_register();
    void set_healthcheck();
    std::map<QString,bool> get_checklist();
    QSvgWidget *body;

    ~Donor_page();

private:
    Ui::Donor_page *ui;




signals:
    void registerClicked();
    void backmain();
    void healthcheck();



};


#endif // DONOR_PAGE_H
