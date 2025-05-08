#include "donor_page.h"
#include <QGraphicsTextItem>
#include <QDebug>







Donor_page::Donor_page(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Donor_page){


    ui->setupUi(this);
    ui->healthcb->setDisabled(false);
    ui->healthcb->hide();
    body =new QSvgWidget("C:/Users/nithi/Documents/dsa/LifeSync/images/body.svg");
    ui->bodylay->addWidget(body);
    QLabel* imageLabel = new QLabel(this);
    QPixmap pix("C:/Users/nithi/Documents/dsa/LifeSync/images/hero.png"); // use the correct path as per .qrc
    imageLabel->setPixmap(pix);
    imageLabel->setScaledContents(true); // Optional, to make it fit
    imageLabel->setFixedSize(1159, 429);  // Adjust size as needed

    // Add it to your layout
    ui->herol->addWidget(imageLabel);
    // Styling for checkboxes
    QString checkboxStyle = "QCheckBox::indicator {"
                            "    border: solid red;"
                            "    border-width: 1px;"
                            "}"
                            "QCheckBox::indicator:checked {"
                            "    background-color: green;"
                            "    border: 2px solid darkgreen;"
                            "}";
    ui->cweight->setStyleSheet(checkboxStyle);
    ui->checkinfi->setStyleSheet(checkboxStyle);
    ui->cbmi->setStyleSheet(checkboxStyle);
    ui->checksur->setStyleSheet(checkboxStyle);
    ui->checkver->setStyleSheet(checkboxStyle);
    ui->checkgenetic->setStyleSheet(checkboxStyle);
    ui->checkill->setStyleSheet(checkboxStyle);
    ui->checkmedi->setStyleSheet(checkboxStyle);
    // Connect buttons
    connect(ui->registerdo, &QPushButton::clicked, this, &Donor_page::registerClicked);
    connect(ui->backmain, &QPushButton::clicked, this, &Donor_page::backmain);
    connect(ui->healthcb, &QPushButton::clicked, this, &Donor_page::healthcheck);


}

Donor_page::~Donor_page() {
    delete ui;
}

QVBoxLayout* Donor_page::getbodylayout() {
    return ui->bodylay;
}

QPushButton* Donor_page::getregisterbutton() {
    return ui->registerdo;
}

void Donor_page::set_register() {
    if (ui->registerdo->isVisible()) {
        ui->registerdo->hide();
        ui->registerdo->setDisabled(true);
    } else {
        ui->registerdo->show();
        ui->registerdo->setDisabled(false);
    }
}

void Donor_page::set_healthcheck() {
    if (ui->healthcb->isVisible()) {
        ui->healthcb->hide();
        ui->healthcb->setDisabled(true);
    } else {
        ui->healthcb->show();
        ui->healthcb->setDisabled(false);
        ui->statuslogin->setText(" ✔ Step 1: Register");
        ui->statuslogin->setStyleSheet("color:Green");
        ui->statuscheck->setText("➤ Step 2: Health Check");
        ui->statuscheck->setStyleSheet("color:white;");
    }
}

std::map<QString, bool> Donor_page::get_checklist() {
    std::map<QString, bool> checklist;
    if (ui->checkill->isChecked()) checklist["checkill"] = true;
    if (ui->checkgenetic->isChecked()) checklist["checkgenetic"] = true;
    if (ui->checkinfi->isChecked()) checklist["checkinfi"] = true;
    if (ui->cbmi->isChecked()) checklist["cbmi"] = true;
    if (ui->checkmedi->isChecked()) checklist["checkmedi"] = true;
    if (ui->checksur->isChecked()) checklist["checksur"] = true;
    if (ui->checkver->isChecked()) checklist["checkver"] = true;
    if (ui->cweight->isChecked()) checklist["cbmi"] = true;
    return checklist;
}


