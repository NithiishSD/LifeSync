#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "donormatchwindow.h"
#include "donor_page.h"
#include "factswindow.h"
#include <QScreen>
#include <QTimer>
#include <QLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QGroupBox>
#include <QDebug>
#include <QRegularExpression>
#include <QComboBox>
#include <QStringList>
#include <QRect>
#include <QPixmap>
#include <QPalette>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("LifeSync");
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    /*  this->setStyleSheet("background-image: url(C:/Users/jrabh/OneDrive/Documents/LifeSync/background.jpg);"
                        "background-repeat: no-repeat;"
                        "background-position: center;"
                        "background-origin: content;"
                        "background-size: cover;"
                        "}");*/

    background = new QLabel(this);

    background->setPixmap(QPixmap("C:/Users/nithi/Documents/dsa/LifeSync/images/background.jpg").scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    background->setGeometry(0, 0, width(), height());
    background->lower();  // Moves the background behind other widgets

    //this->statusBar()->showMessage("Welcome , Enter your user&pass or if you don't have ,"
    //                               " make it ;)",10000);
    //nithiish creating a frame for tabs and logo

    top_frame=new QFrame(this);
    top_frame->setObjectName("tf");
    top_frame->setFrameShape(QFrame::StyledPanel);
    top_frame-> setFrameShadow(QFrame::Raised);

    top_frame ->setGeometry(0,0,width(),70);
    top_frame ->setStyleSheet("#tf{background-color:orange;border: 2px solid black;border-radius: 4px;}");
    top_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //create the layout inside the frame so that the widget gets its position automatically

    QHBoxLayout* tf_Layout = new QHBoxLayout(top_frame);//here QVBox or QHhox for vertical and horizoonttal
    tf_Layout->setContentsMargins(0, 0,width()/2-300, 0);
    tf_Layout->setSpacing(40);
    top_frame->setLayout(tf_Layout);
    QLabel * appname =new QLabel("LIFESYNC");
    appname->setStyleSheet(
        "QLabel {"
        "  color: #2E2E2E;"             // Calm blue
        "  font-size: 28px;"            // Prominent size
        "  font-weight: bold;"          // Bold text
        "  font-family: 'Segoe UI', sans-serif;"
        "  padding-left: 20px;"         // Slight indent from left
        "  margin-top: 10px;"           // Slight spacing from top
        "}"
        );
    tf_Layout->addWidget(appname);
    tf_Layout->addStretch();
    QPushButton *og_b= new QPushButton("DONATE ORGAN");//create organ donate button
    og_b->setCursor(Qt::PointingHandCursor);
    og_b->setStyleSheet("background-color:red;color:green");
    tf_Layout->addWidget(og_b);
    //tf_Layout->insertWidget(2,og_b);
    tf_Layout->setAlignment(Qt::AlignRight);

    QPushButton *re_b= new QPushButton("RECEIVER");//create organ receiver button
    re_b->setCursor(Qt::PointingHandCursor);
    re_b->setStyleSheet("background-color:red;color:green");
    tf_Layout->addWidget(re_b);
    //tf_Layout->insertWidget(2,og_b);
    tf_Layout->setAlignment(Qt::AlignRight);


    //this this to create the pop out window

    ogd_popframe=new QFrame(this);
    ogd_popframe->setObjectName("ogd");
    ogd_popframe->setMinimumSize(300,200);

    ogd_popframe->setFrameShape(QFrame::StyledPanel);
    ogd_popframe->setFrameShadow(QFrame::Plain);
    ogd_popframe->setStyleSheet("#ogd{background-color:white;border-top:4px double blue;padding:0px;}");
    ogd_popframe->setGeometry(this->width()/2-50,70,this->width()/2-10,300);
    ogd_popframe->hide();

    rgd_popframe=new QFrame(this);


    connect(og_b,&QPushButton::clicked,this,[this](){
        if(!ogd_popframe->isVisible()){
            ogd_popframe->show();
            rgd_popframe->hide();}
        else if(ogd_popframe->isVisible()){
            ogd_popframe->hide();
            // rgd_popframe->show();
        }
    });


    //creating a layout for this frame
    //QHBoxLayout *odbl=new QHBoxLayout(ogd_popframe);
    //creating a label  inside the frame left side


    rgd_popframe->setMinimumSize(300,200);
    rgd_popframe->setObjectName("ogd");
    rgd_popframe->setFrameShape(QFrame::StyledPanel);
    rgd_popframe->setFrameShadow(QFrame::Plain);
    rgd_popframe->setStyleSheet("#ogd{background-color:white;border-top:4px double blue;padding:0px;}");
    rgd_popframe->setGeometry(this->width()/2-50,70,this->width()/2-10,300);
    rgd_popframe->hide();
    connect(re_b,&QPushButton::clicked,this,[this](){
        if(!rgd_popframe->isVisible()){
            rgd_popframe->show();
            ogd_popframe->hide();
        }
        else if(rgd_popframe->isVisible()){
            rgd_popframe->hide();
            // ogd_popframe->show();
        }
    });
    //creating a layout for this frame
    QHBoxLayout *odbl=new QHBoxLayout(ogd_popframe);
    //creating a label  inside the frame left side
    QHBoxLayout *rgbl=new QHBoxLayout(rgd_popframe);

    donorf_image =new QLabel(ogd_popframe);

    donorf_image->setPixmap(QPixmap("C:/Users/nithi/Documents/dsa/LifeSync/background.jpg"));
    donorf_image->setScaledContents(true); // Allow image to scale
    donorf_image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    odbl->addWidget(donorf_image);
    odbl->setAlignment(Qt::AlignLeft);
    QGridLayout *donor_buttons=new QGridLayout();

    QPushButton *db1=new QPushButton("Register Donor");
    QPushButton *db2=new QPushButton("Myths of Organ Donation");
    donor_buttons->addWidget(db1,0,0);
    donor_buttons->addWidget(db2,1,0);

    donor_buttons->setSpacing(50);
    donor_buttons->setAlignment(Qt::AlignTop);
    donor_buttons->setContentsMargins(10,50,0,0);



    QGridLayout *receiver_buttons=new QGridLayout();

    QPushButton *rb1=new QPushButton("Receiver Register");
    QPushButton *rb2=new QPushButton("Receiver Login");


    /*b1->setStyleSheet("QPushButton {""   font-size: 26px;""   color:black;""   background-color:white;""border:none;""}""QPushButton:hover{"
        "   text-decoration: underline;"
        "   color:blue;"
        "   background-color: transparent;"
        "}");*/
    //connect(b1,&QPushButton::clicked,this,&MainWindow::open_donor_window);


    connect(db1,&QPushButton::clicked,this,&MainWindow::open_donor_window);
    connect(db2,&QPushButton::clicked,this,&MainWindow::go_to_factsw);
    connect(rb1,&QPushButton::clicked,this,&MainWindow::open_receiver_window);
    connect(rb2,&QPushButton::clicked,this,&MainWindow::open_login_window);

    receiver_buttons->addWidget(rb1,0,0);
    receiver_buttons->addWidget(rb2,1,0);

    receiver_buttons->setSpacing(50);
    receiver_buttons->setAlignment(Qt::AlignTop);
    receiver_buttons->setContentsMargins(10,50,0,0);


    QWidget * button_con=new QWidget();
    button_con->setLayout(donor_buttons);

    odbl->addWidget(button_con,2);
    QWidget * button_regcon=new QWidget();
    button_regcon->setLayout(receiver_buttons);
    rgbl->addWidget(button_regcon,2);
    rgd_popframe->setLayout(rgbl);


    ogd_popframe->setLayout(odbl);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete donorp;
    delete stack;
}

QSize MainWindow::sizeHint() const
{
    return QSize(800,600);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);// Call base class implementation

    if (background) {
        background->setGeometry(0, 0, width(), height());  // Resize QLabel
        background->setPixmap(QPixmap("C:/Users/nithi/Documents/dsa/LifeSync/images/background.jpg").scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    }
    if(top_frame){
        top_frame->setGeometry(0,0,this->width(),70);
    }
    if(ogd_popframe){
        ogd_popframe->setGeometry(this->width()/2-350,70,(this->width()/2)-10,400);
    }
    if(ogd_popframe&&ogd_popframe->isVisible()){
        int newWidth = ogd_popframe->width() / 2; // 50% of frame width
        int newHeight = ogd_popframe->height(); // Full height
        donorf_image->setPixmap(QPixmap("C:/Users/nithi/Documents/dsa/LifeSync/images/background.jpg").scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    if(donor){
        donor->setGeometry(0,0,this->width(),this->height());
    }

}


void MainWindow::etch(const QString &text)
{
    QRegularExpression reg("[a-zA-Z]+[a-zA-Z0-9._]*[a-zA-Z0-9]+@[a-zA-Z]+[.]{1}[a-zA-Z]{2,4}");
    if(reg.match(text).hasMatch()){
        this->email->setStyleSheet("color: green");
    }else{
        this->email->setStyleSheet("color: red");
    }
}

void MainWindow::ptch(const QString &text)
{
    QRegularExpression reg1("09[0-9]{9}");
    QRegularExpression reg2("\\+989[0-9]{9}");
    if(reg1.match(text).hasMatch() || reg2.match(text).hasMatch()){
        this->phonenum->setStyleSheet("color: green");
    }else{
        this->phonenum->setStyleSheet("color: red");
    }
}
void MainWindow::open_donor_window(){

    if(background->isVisible()){
        background->hide();

    }
    else{
        background->show();
    }
    if(top_frame->isVisible()){
        top_frame->hide();
        ogd_popframe->hide();
    }
    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    donorp =new Donor_page(this);
    stack->addWidget(donorp);

    connect(donorp,&Donor_page::registerClicked,this,&MainWindow::open_donor_register);
    connect(donorp,&Donor_page::backmain,this,&MainWindow::go_to_main);
    connect(donorp,&Donor_page::healthcheck,this,&MainWindow::go_to_health_check);
    stack->setCurrentWidget(donorp);
        health_check =new QWidget(this);
        QVBoxLayout *healthlayout =new QVBoxLayout;
        QLabel *htitle =new QLabel("🏥 Health Checkup Information");
        htitle->setStyleSheet("font-weight: bold; font-size: 18px;");
        healthlayout->addWidget(htitle);

        hosinfo =new QLabel(hospital_info);
        hosinfo->setWordWrap(true);
        hosinfo->setStyleSheet("font-size:14px;");
        healthlayout->addWidget(hosinfo);
        QLabel* message = new QLabel("🧪 If your health checkup is successful, the hospital will send your report here.\n\n"
                                     "🔔 Based on the result, you will be notified about your eligibility for the final donation stage.\n\n"
                                     "📆 Please allow up to 24–48 hours for processing.");
        message->setWordWrap(true);
        message->setStyleSheet("font-size: 13px; background-color: black; padding: 10px; border-radius: 10px;");
        healthlayout->addWidget(message);
        proceedButton = new QPushButton("✅ Close");
        proceedButton->setCursor(Qt::PointingHandCursor);
        proceedButton->setStyleSheet("background-color: #4CAF50; color: white; padding: 10px; border-radius: 8px;");
        healthlayout->addWidget(proceedButton, 0, Qt::AlignCenter);
        health_check->setLayout(healthlayout);
        stack->addWidget(health_check);


    connect(proceedButton,&QPushButton::clicked,this,&MainWindow::go_to_donorp);
}
void MainWindow::open_donor_register(){

    donor = new QWidget(this);
    donor->setGeometry(0,0,width(),height());
    donor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QFormLayout* fl = new QFormLayout;
    fl->setContentsMargins(100,50,100,0);
    fl->setFormAlignment(Qt::AlignCenter);
    //login->setStyleSheet("padding: 20px");
    donor->setLayout(fl);
    donor->setStyleSheet("QLineEdit {margin: 5px;margin-right:60px;background-color: white;color: blue;"
                         "margin-top: 20px;border: 1px solid aqua;"
                         "border-radius: 10px}"
                         "QComboBox {margin: 5px;margin-right:60px;background-color: white;color: blue;"
                         "margin-top: 20px;border: 1px solid aqua;"
                         "border-radius: 10px}"
                         "QLabel {margin: 5px;margin-left: 60px;margin-top: 20px;border-radius: 10px}"
                         "QPushButton {margin: 5px;margin-top: 20px;border-radius: 10px;"
                         "margin-left: 220px;margin-right: 60px; background-color: blue;color: red}"
                         "QPushButton:pressed {background-color: red;color: blue}");
    QLineEdit* dname = new QLineEdit;
    dname->setPlaceholderText("Name");
    fl->addRow(new QLabel("Name : "),dname);
    donorb = new QPushButton("Register");
    donorb->setCursor(Qt::PointingHandCursor);
    QComboBox* blood = new QComboBox;
    QStringList groups = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    blood->addItems(groups);
    fl->addRow(new QLabel("Blood Group :"), blood);
    QComboBox* organsReq = new QComboBox;
    QStringList organs = {"Liver", "Heart", "Eyes", "Blood", "Kidney", "Intestine", "Tissue"};
    organsReq->addItems(organs);
    fl->addRow(new QLabel("Organs Required :"), organsReq);
    QComboBox* hospital = new QComboBox;
    QStringList hospitals = {
        "City Hospital", "General Medical Center", "St. Mary’s Hospital",
        "Riverside Clinic", "Northside Health", "Southend Medical",
        "Eastview Hospital", "Westgate Center"
    };
    hospital->addItems(hospitals);
    fl->addRow(new QLabel("Nearest Hospital :"), hospital);
    QGroupBox* gb = new QGroupBox;
    gb->setTitle("Gender");
    QButtonGroup* bg = new QButtonGroup;
    QRadioButton* male = new QRadioButton("Male");
    bg->addButton(male,0);
    bg->addButton(new QRadioButton("Female"),1);
    QGridLayout* gl = new QGridLayout(gb);
    gl->addWidget(bg->button(0),0,0);
    gl->addWidget(bg->button(1),0,1);
    fl->addRow(gb);
    this->phonenum = new QLineEdit;
    this->phonenum->setPlaceholderText("Phone Number");
    QObject::connect(this->phonenum,SIGNAL(textChanged(const QString&)),this,SLOT(ptch(const QString&)));
    fl->addRow(new QLabel("Phone Number : "),this->phonenum);
    this->email = new QLineEdit;
    QObject::connect(this->email,SIGNAL(textChanged(const QString &)),this,
                     SLOT(etch(const QString&)));
    this->email->setPlaceholderText("E-mail");
    fl->addRow(new QLabel("E-mail : "),this->email);
    fl->addWidget(donorb);
    stack->addWidget(donor);
    MainWindow::if_registered=true;

    connect(donorb, &QPushButton::clicked, this, [=]() {
        storeDonorData(dname, email, phonenum, blood, organsReq, hospital, male);
    });
    stack->setCurrentWidget(donor);


}
void MainWindow::go_to_main(){
    if(donorp)
    {
        donorp->set_healthcheck();
        donorp->set_register();
        donorp->hide();
        donorp->deleteLater();
        donorp=nullptr;
        if_registered=false;
        if_health_check=false;
    }
    if(factsw)
    {
        factsw->hide();
        factsw->deleteLater();
        factsw=nullptr;
    }
    setCentralWidget(nullptr);
    background->show();
    //ogd_popframe->show();
    top_frame->show();


}
void MainWindow::go_to_donorp() {

    if(MainWindow::if_registered&&!MainWindow::if_health_check){
        if (donorp){
            stack->setCurrentWidget(donorp);
            donorp->set_register();
            donorp->set_healthcheck();
        }

        QWidget *successPopup = new QWidget(nullptr, Qt::Tool | Qt::FramelessWindowHint);
        successPopup->setAttribute(Qt::WA_DeleteOnClose);
        successPopup->setFixedSize(200, 100);

        QRect screen = QGuiApplication::primaryScreen()->geometry();
        int x = (screen.width() - successPopup->width()) / 2;
        int y = (screen.height() - successPopup->height()) / 2;
        successPopup->move(x, y);

        QVBoxLayout *layout = new QVBoxLayout(successPopup);
        QLabel *label = new QLabel("✅ Successfully registered!", successPopup);
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);

        successPopup->setStyleSheet(
            "background-color: #dff0d8;"
            "color: #3c763d;"
            "border: 1px solid #3c763d;"
            "border-radius: 8px;"
            "font-size: 14px;"
            );

        successPopup->show();
        QTimer::singleShot(2000, successPopup, &QWidget::close);
    }
    else if(!if_health_check){
        QWidget *successPopup = new QWidget(nullptr, Qt::Tool | Qt::FramelessWindowHint);
        successPopup->setAttribute(Qt::WA_DeleteOnClose);
        successPopup->setFixedSize(250, 100);

        QRect screen = QGuiApplication::primaryScreen()->geometry();
        int x = (screen.width() - successPopup->width()) / 2;
        int y = (screen.height() - successPopup->height()) / 2;
        successPopup->move(x, y);

        QVBoxLayout *layout = new QVBoxLayout(successPopup);
        QLabel *label = new QLabel("OHH!! SOMETHING WENT WRONG", successPopup);
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);

        successPopup->setStyleSheet(
            "background-color: light red ;"
            "color: red;"
            "border: 1px solid red;"
            "border-radius: 8px;"
            "font-size: 14px;"
            );

        successPopup->show();
        QTimer::singleShot(2000, successPopup, &QWidget::close);

    }
    stack->setCurrentWidget(donorp);
}
void MainWindow::go_to_health_check(){
    hosinfo->setText(select_hospital_info(hospital_info));
    stack->setCurrentWidget(health_check);
    MainWindow::if_registered=false;
    MainWindow::if_health_check=true;

}

void MainWindow::open_receiver_window(){
    if(background->isVisible()){
        background->hide();

    }
    else{
        background->show();
    }
    if(top_frame->isVisible()){
        top_frame->hide();
        ogd_popframe->hide();
        rgd_popframe->hide();
    }

    //setCentralWidget(nullptr);
    rgstack = new QStackedWidget(this);
    setCentralWidget(rgstack);
    receiverReg = new QWidget(this);
    rgstack->addWidget(receiverReg);
    QFormLayout* fl2 = new QFormLayout;
    fl2->setFormAlignment(Qt::AlignCenter);
    receiverReg->setLayout(fl2);
    receiverReg->setStyleSheet("QLineEdit {margin: 5px;margin-right:60px;background-color: white;color: blue;"
                               "margin-top: 20px;border: 1px solid aqua;"
                               "border-radius: 10px}"
                               "QComboBox {margin: 5px;margin-right:60px;background-color: white;color: blue;"
                               "margin-top: 20px;border: 1px solid aqua;"
                               "border-radius: 10px}"
                               "QLabel {margin: 5px;margin-left: 60px;margin-top: 20px;border-radius: 10px}"
                               "QPushButton {margin: 5px;margin-top: 20px;border-radius: 10px;"
                               "margin-left: 220px;margin-right: 60px; background-color: blue;color: red}"
                               "QPushButton:pressed {background-color: red;color: blue}");

    QLineEdit* name = new QLineEdit;
    name->setPlaceholderText("Name");
    fl2->addRow(new QLabel("Name : "),name);
    this->email = new QLineEdit;
    QObject::connect(this->email,SIGNAL(textChanged(const QString &)),this,
                     SLOT(etch(const QString&)));
    this->email->setPlaceholderText("E-mail");
    fl2->addRow(new QLabel("E-mail : "),this->email);
    this->phonenum = new QLineEdit;
    this->phonenum->setPlaceholderText("Phone Number");
    QObject::connect(this->phonenum,SIGNAL(textChanged(const QString&)),this,
                     SLOT(ptch(const QString&)));
    fl2->addRow(new QLabel("Phone Number : "),this->phonenum);
    QComboBox* blood = new QComboBox;
    QStringList groups = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    blood->addItems(groups);
    fl2->addRow(new QLabel("Blood Group :"), blood);
    QComboBox* organsReq = new QComboBox;
    QStringList organs = {"Liver", "Heart", "Eyes", "Blood", "Kidney", "Intestine", "Tissue"};
    organsReq->addItems(organs);
    fl2->addRow(new QLabel("Organs Required :"), organsReq);
    QComboBox* hospital = new QComboBox;
    QStringList hospitals = {
        "City Hospital", "General Medical Center", "St. Mary’s Hospital",
        "Riverside Clinic", "Northside Health", "Southend Medical",
        "Eastview Hospital", "Westgate Center"
    };
    hospital->addItems(hospitals);
    fl2->addRow(new QLabel("Nearest Hospital :"), hospital);
    QGroupBox* gb2 = new QGroupBox;
    gb2->setTitle("Gender");
    QButtonGroup* bg2 = new QButtonGroup;
    QRadioButton* male = new QRadioButton("Male");
    bg2->addButton(male, 0);
    bg2->addButton(new QRadioButton("Female"),1);
    QGridLayout* gl2 = new QGridLayout(gb2);
    gl2->addWidget(bg2->button(0),0,0);
    gl2->addWidget(bg2->button(1),0,1);
    fl2->addRow(gb2);
    QLineEdit* pass = new QLineEdit;
    QLineEdit* reEnter = new QLineEdit;
    pass->setPlaceholderText("Password");
    reEnter->setPlaceholderText("Re-enter password");
    pass->setEchoMode(QLineEdit::Password);
    reEnter->setEchoMode(QLineEdit::Password);
    fl2->addRow(new QLabel("Password : "),pass);
    fl2->addRow(new QLabel("Re-enter Password : "),reEnter);
    QPushButton* receiverb = new QPushButton("Register");
    fl2->addWidget(receiverb);
    rgstack->setCurrentWidget(receiverReg);
    connect(receiverb, &QPushButton::clicked, this, [=]() {
        storeReceiverData(name, email, phonenum, blood, organsReq, hospital, male, pass, reEnter);
    });

}
void MainWindow::go_to_factsw(){
    if(background->isVisible()){
        background->hide();

    }
    else{
        background->show();
    }
    if(top_frame->isVisible()){
        top_frame->hide();
        ogd_popframe->hide();
        rgd_popframe->hide();
    }
    factsw = new Factswindow(this);
    //rgstack->addWidget(factsw);
    //rgstack->setCurrentWidget(factsw);
    setCentralWidget(factsw);
    connect(factsw,&Factswindow::button_clicked,this,&MainWindow::go_to_main);



}


void MainWindow::open_login_window() {
    if(background->isVisible()){
        background->hide();

    }
    else{
        background->show();
    }
    if(top_frame->isVisible()){
        top_frame->hide();
        ogd_popframe->hide();
        rgd_popframe->hide();
    }

    //setCentralWidget(nullptr);
    rgstack = new QStackedWidget(this);
    setCentralWidget(rgstack);
    QWidget* receiverLog = new QWidget(this);
    rgstack->addWidget(receiverLog);
    QFormLayout* fl3 = new QFormLayout;
    fl3->setFormAlignment(Qt::AlignCenter);
    receiverLog->setLayout(fl3);
    receiverLog->setStyleSheet("QLineEdit {margin: 5px;margin-right:60px;background-color: white;color: blue;"
                               "margin-top: 20px;border: 1px solid aqua;"
                               "border-radius: 10px}"
                               "QComboBox {margin: 5px;margin-right:60px;background-color: white;color: blue;"
                               "margin-top: 20px;border: 1px solid aqua;"
                               "border-radius: 10px}"
                               "QLabel {margin: 5px;margin-left: 60px;margin-top: 20px;border-radius: 10px}"
                               "QPushButton {margin: 5px;margin-top: 20px;border-radius: 10px;"
                               "margin-left: 220px;margin-right: 60px; background-color: blue;color: red}"
                               "QPushButton:pressed {background-color: red;color: blue}");
    QLineEdit* uname = new QLineEdit;
    uname->setPlaceholderText("Name");
    fl3->addRow(new QLabel("Name : "),uname);
    QLineEdit* passw = new QLineEdit;
    passw->setPlaceholderText("Password");
    passw->setEchoMode(QLineEdit::Password);
    fl3->addRow(new QLabel("Password : "),passw);
    QPushButton* login = new QPushButton("Login");
    fl3->addWidget(login);
    connect(login, &QPushButton::clicked, this, [=]() {
        MainWindow::matchDonorsForReceiver(uname, passw);
    });
}

void MainWindow::checkUser(const QString& uname, const QString& passw) {
    // Use existing database connection or create a new one
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(QDir::currentPath() + "/Database.db");
    }
    if (!db.open()) {
        qDebug() << "Database Error:" << db.lastError().text();
        return;
    }

    // Prepare query to find user by name and password
    QSqlQuery query;
    query.prepare("SELECT * FROM recipients ");
    //   query.bindValue(":name", uname);
    // query.bindValue(":password", passw);

    if (!query.exec()) {
        qDebug() << "Query Error:" << query.lastError().text();
        db.close();
        return;
    }

    // Check if a matching record is found
    if (query.next()) {
        // Print header
        qDebug() << "ID | Name | Email | Phone | Blood | Organs | Hospital | Gender | Password";
        qDebug() << "---------------------------------------------------";

        // Fetch and print the matching user's data
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString email = query.value("email").toString();
        QString phone = query.value("phone").toString();
        QString blood = query.value("blood").toString();
        QString organs = query.value("organs").toString();
        QString hospital = query.value("hospital").toString();
        QString gender = query.value("gender").toString();
        QString password = query.value("password").toString();

        qDebug() << QString("%1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9")
                        .arg(id, 2)
                        .arg(name, -15)
                        .arg(email, -25)
                        .arg(phone, -12)
                        .arg(blood, -3)
                        .arg(organs, -10)
                        .arg(hospital, -2)
                        .arg(gender, -6)
                        .arg(password, -15);
    } else {
        qDebug() << "Empty.....................";
    }

    // Clean up database connection
    db.close();
}
void MainWindow::storeDonorData(QLineEdit* lname, QLineEdit* lemail, QLineEdit* lphonenum,
                                QComboBox* lblood, QComboBox* lorgans, QComboBox* hospital,
                                QRadioButton* male) {
    // Check for null pointers
    if (!lname || !lemail || !lphonenum || !lblood || !lorgans || !hospital || !male) {
        qDebug() << "Error: One or more input pointers are null!";
        return;
    }

    // Use existing database connection or create a new one
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("Database.db");
    }
    if (!db.open()) {
        qDebug() << "Database Error:" << db.lastError().text();
        return;
    }

    // Create a table to store the data
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS donors ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT, "
               "email TEXT, "
               "phone TEXT, "
               "blood TEXT, "
               "organs TEXT, "
               "hospital TEXT, "
               "gender TEXT)");

    QString name = lname->text();
    QString email = lemail->text();
    QString phone = lphonenum->text();
    QString blood = lblood->currentText();
    QString organs = lorgans->currentText();
    QString hosp = hospital->currentText();
    QString gender = male->isChecked() ? "Male" : "Female";
    hospital_info=hosp;
    // Validate input fields
    if (name.isEmpty() || email.isEmpty() || phone.isEmpty() || blood.isEmpty() || organs.isEmpty() || hosp.isEmpty()) {
        qDebug() << "Error: One or more fields are empty!";
        db.close();
        return;
    }

    query.prepare("INSERT INTO donors (name, email, phone, blood, organs, hospital, gender) "
                  "VALUES (:name, :email, :phone, :blood, :organs, :hospital, :gender)");
    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);
    query.bindValue(":blood", blood);
    query.bindValue(":organs", organs);
    query.bindValue(":hospital", hosp);
    query.bindValue(":gender", gender);

    if (!query.exec()) {
        qDebug() << "Insert Error:" << query.lastError().text();
        db.close();
        return;
    } else {
        qDebug() << "Data inserted successfully!";
    }

    // Clean up database connection
    db.close();
    if_registered = true;
    go_to_donorp();
}

void MainWindow::storeReceiverData(QLineEdit* lname, QLineEdit* lemail, QLineEdit* lphonenum, QComboBox* lblood, QComboBox* lorgans, QComboBox* hospital, QRadioButton* male, QLineEdit* pass, QLineEdit* repass) {
    // Check for null pointers
    if (!lname || !lemail || !lphonenum || !lorgans || !male || !pass || !repass) {
        qDebug() << "Error: One or more input pointers are null!";
        return;
    }

    // Use existing database connection or create a new one
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("Database.db");
    }
    if (!db.open()) {
        qDebug() << "Database Error:" << db.lastError().text();
        return;
    }

    // Create a table to store the data
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS recipients ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT, "
               "email TEXT, "
               "phone TEXT, "
               "blood TEXT, "
               "organs TEXT, "
               "hospital TEXT,"
               "gender TEXT, "
               "password TEXT)");

    QString name = lname->text();
    QString email = lemail->text();
    QString phone = lphonenum->text();
    QString blood = lblood->currentText();
    QString organs = lorgans->currentText();
    QString hosp = hospital->currentText();
    QString gender = male->isChecked() ? "Male" : "Female";
    QString password = pass->text();
    QString rePassword = repass->text();

    // Basic validation (e.g., password match)
    if (password != rePassword) {
        qDebug() << "Passwords do not match!";
        db.close();
        return;
    }

    query.prepare("INSERT INTO recipients (name, email, phone, blood, organs, hospital, gender, password) "
                  "VALUES (:name, :email, :phone, :blood, :organs, :hospital, :gender, :password)");
    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);
    query.bindValue(":blood", blood);
    query.bindValue(":organs", organs);
    query.bindValue(":hospital",hosp);
    query.bindValue(":gender", gender);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Insert Error:" << query.lastError().text();
    } else {
        qDebug() << "Donor Data inserted successfully!";

    }
    db.close();
    go_to_main();
    // Clean up database connection

}

// Find index of hospital in the array
int getHospitalIndex(const QString& hospital) {
    for (int i = 0; i < NUM_HOSPITALS; ++i) {
        if (hospitals[i] == hospital) return i;
    }
    return -1;
}

void MainWindow::matchDonorsForReceiver(QLineEdit* nameEdit, QLineEdit* passEdit) {
    if (!nameEdit || !passEdit) {
        qDebug() << "Error: Input pointers are null!";
        return;
    }

    QString uname = nameEdit->text();
    QString password = passEdit->text();
    if (uname.isEmpty() || password.isEmpty()) {
        qDebug() << "Error: Username or password is empty!";
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("Database.db");
    }
    if (!db.open()) {
        qDebug() << "Database Error:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.clear();
    query.prepare("SELECT * FROM recipients WHERE name = :name AND password = :password");
    query.bindValue(":name", uname);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Query Error:" << query.lastError().text();
        db.close();
        return;
    }

    if (!query.next()) {
        qDebug() << "No matching receiver found!";
        db.close();
        return;
    }

    QString recBlood = query.value("blood").toString(); // Kept for potential future use
    QString recOrgans = query.value("organs").toString();
    QString recHospital = query.value("hospital").toString();
    int recHospitalIndex = getHospitalIndex(recHospital);
    if (recHospitalIndex == -1) {
        qDebug() << "Invalid receiver hospital:" << recHospital;
        db.close();
        return;
    }

    query.clear();
    query.prepare("SELECT * FROM donors");
    if (!query.exec()) {
        qDebug() << "Donor Query Error:" << query.lastError().text();
        db.close();
        return;
    }

    PriorityQueue priorityQueue;
    QVector<DonorMatch> matches;

    while (query.next()) {
        QString donName = query.value("name").toString();
        QString donEmail = query.value("email").toString();
        QString donPhonenum = query.value("phone").toString();
        QString donBlood = query.value("blood").toString();
        QString donOrgans = query.value("organs").toString();
        QString donHospital = query.value("hospital").toString();
        QString donGender = query.value("gender").toString();

        int donHospitalIndex = getHospitalIndex(donHospital);
        if (donHospitalIndex == -1) {
            qDebug() << "Invalid donor hospital:" << donHospital;
            continue;
        }

        // Filter: Only include donors with the same organs
        if (donOrgans != recOrgans) {
            continue; // Skip if organs don't match
        }

        // Calculate match score (only organ match matters now)
        int matchScore = 0;
        if (donOrgans == recOrgans) {
            matchScore += 100; // Full match on organs
        }
        if(recBlood==donBlood){
            matchScore+=75;
        }

        // Distance from receiver's hospital
        int distance = distanceMatrix[recHospitalIndex][donHospitalIndex];

        if (matchScore > 0) {
            // Total priority: Higher match score minus distance (lower distance = higher priority)
            int totalPriority = matchScore - distance;
            DonorMatch match = {donName, donEmail, donPhonenum, donBlood, donOrgans, donHospital, donGender, matchScore, distance, totalPriority};
            priorityQueue.push(match);
        }
    }

    // Transfer from priority queue to vector in order
    while (!priorityQueue.isEmpty()) {
        matches.append(priorityQueue.pop());
    }

    // Open donor match window
    if (!matches.isEmpty()) {
        DonorMatchWindow *donorWindow = new DonorMatchWindow(this);
        donorWindow->setDonorMatches(matches);
        donorWindow->exec();
    } else {
        qDebug() << "No suitable donors found with matching organs!";
    }

    db.close();
}

QString MainWindow::select_hospital_info(QString hos){
    QString fulldetail;
    if(hos=="City Hospital")
        return "🩺 Assigned Hospital\nName: City Hospital\nAddress: 45 Residency Road, Downtown Sector, Metro City\nContact: +91 98765 43210\n\n👨‍⚕️ Consulting Doctor\nName: Dr. Meena Arvind\nSpecialization: General Physician\nExperience: 10+ years in preventive health and internal medicine";
    if(hos=="General Medical Center"){
        return "🩺 Assigned Hospital\n\
               Name: General Medical Center\n\
                          Address: 102 Wellness Avenue, Central District, Newtown\n\
                                  Contact: +91 90909 12345\n\
                \n👨‍⚕️ Consulting Doctor\n\
                Name: Dr. Rahul Verma\n\
                Specialization: Internal Medicine\n\
                   Experience: 15+ years in patient care and diagnostics";}

    if(hos=="St. Mary’s Hospital"){
        return "🩺 Assigned Hospital\n\
               Name: St. Mary’s Hospital\n\
                          Address: Church Street, Block B, Oldtown\n\
                                    Contact: +91 91234 56789\n\
                                    \n👩‍⚕️ Consulting Doctor\n\
                                                  Name: Dr. Rebecca Fernandes\n\
                                                             Specialization: Cardiologist\n\
                                                                                  Experience: 18+ years in cardiac care and donor evaluations"
            ;}
    if(hos== "Riverside Clinic"){
        return "🩺 Assigned Hospital\n\
               Name: Riverside Clinic\n\
                          Address: 7 River Lane, Lakeside Area, Green City\n\
                                  Contact: +91 99887 65432\n\
                                    \n👨‍⚕️ Consulting Doctor\n\
                                                Name: Dr. Karan Mehta\n\
                                                           Specialization: Family Medicine\n\
                   Experience: 12+ years in community health and screening";
    }
    if(hos=="Northside Health"){
        return " 🩺 Assigned Hospital\n\
               Name: Northside Health\n\
                          Address: Plot 21, Medical Zone, North Sector\n\
                                                Contact: +91 90001 22334\n\
                                                \n👨‍⚕️ Consulting Doctor\n\
                                                              Name: Dr. Nidhi Sharma\n\
                                                                         Specialization: Transfusion Medicine\n\
                                                                                              Experience: 9+ years in donor evaluation and blood banking";
    }
    if(hos=="Southend Medical"){
        return "🩺 Assigned Hospital\n\
               Name: Southend Medical\n\
                          Address: South Ring Road, Sector 10, Urban Hub\n\
                                                Contact: +91 98000 55443\n\
                                                          \n👩‍⚕️ Consulting Doctor\n\
                                                              Name: Dr. Ananya Raj\n\
                                                                         Specialization: Preventive Healthcare\n\
                                                                                              Experience: 14+ years in routine screenings and donor wellness";
    }
    if(hos== "Eastview Hospital"){
        return "🩺 Assigned Hospital\n\
               Name: Eastview Hospital\n\
                          Address: 88 East End Road, Tech Park District\n\
                                  Contact: +91 98770 33221\n\
                                    \n👨‍⚕️ Consulting Doctor\n\
                                                Name: Dr. Vikram Das\n\
                                                           Specialization: Gastroenterologist\n\
                                                                                Experience: 11+ years in diagnostic medicine and health exams";
    }
    if(hos=="Westgate Center"){
        return " 🩺 Assigned Hospital\n\
               Name: Westgate Center\n\
                          Address: 3 West Avenue, Civic Center Zone\n\
                                  Contact: +91 93333 12345\n\
                                    \n👨‍⚕️ Consulting Doctor\n\
                                                Name: Dr. Priya Balan\n\
                                                           Specialization: Pulmonologist\n\
                                                                                Experience: 13+ years in donor screening and respiratory diagnostics";
    }
    return "";
}
