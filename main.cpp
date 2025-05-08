#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>

// Function to display all details of donors and recipients
void displayAllData() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::currentPath() + "/Database.db");

    if (!db.open()) {
        qDebug() << "Database Error:" << db.lastError().text();
        return;
    }

    QSqlQuery query;

    // Display all recipients
    qDebug() << "=== Recipients Data ===";
    query.prepare("SELECT * FROM recipients");
    if (!query.exec()) {
        qDebug() << "Recipients Query Error:" << query.lastError().text();
        db.close();
        return;
    }

    qDebug() << "ID | Name | Email | Phone | Blood | Organs | Hospital | Gender | Password";
    qDebug() << "-----------------------------------------------------------------------";
    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString email = query.value("email").toString();
        QString phonenum = query.value("phone").toString();
        QString blood = query.value("blood").toString();
        QString organs = query.value("organs").toString();
        QString hospital = query.value("hospital").toString();
        QString gender = query.value("gender").toString();
        QString password = query.value("password").toString();

        qDebug() << QString("%1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9")
                        .arg(id, 2)
                        .arg(name, -15)
                        .arg(email, -25)
                        .arg(phonenum, -12)
                        .arg(blood, -6)
                        .arg(organs, -10)
                        .arg(hospital, -15)
                        .arg(gender, -6)
                        .arg(password, -15);
    }

    // Display all donors
    query.clear();
    qDebug() << "\n=== Donors Data ===";
    query.prepare("SELECT * FROM donors");
    if (!query.exec()) {
        qDebug() << "Donors Query Error:" << query.lastError().text();
        db.close();
        return;
    }

    qDebug() << "ID | Name | Email | Phone | Blood | Organs | Hospital | Gender";
    qDebug() << "------------------------------------------------------------";
    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString email = query.value("email").toString();
        QString phonenum = query.value("phone").toString();
        QString blood = query.value("blood").toString();
        QString organs = query.value("organs").toString();
        QString hospital = query.value("hospital").toString();
        QString gender = query.value("gender").toString();

        qDebug() << QString("%1 | %2 | %3 | %4 | %5 | %6 | %7 | %8")
                        .arg(id, 2)
                        .arg(name, -15)
                        .arg(email, -25)
                        .arg(phonenum, -12)
                        .arg(blood, -6)
                        .arg(organs, -10)
                        .arg(hospital, -15)
                        .arg(gender, -6);
    }

    db.close();
}

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void clearTable(const QString& tableName) {
    if (tableName.isEmpty()) {
        qDebug() << "Error: Table name is empty!";
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
    query.prepare(QString("DELETE FROM %1").arg(tableName)); // Delete all rows

    if (!query.exec()) {
        qDebug() << "Clear Table Error:" << query.lastError().text() << "for table:" << tableName;
    } else {
        qDebug() << "Table" << tableName << "cleared successfully. Rows affected:" << query.numRowsAffected();
    }

    db.close();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "LifeSync_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    displayAllData();
    return a.exec();
}
