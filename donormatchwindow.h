#ifndef DONORMATCHWINDOW_H
#define DONORMATCHWINDOW_H

#include "mainwindow.h"
#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>

class DonorMatchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DonorMatchWindow(QWidget *parent = nullptr);
    ~DonorMatchWindow();

    // Function to set and display donor matches
    void setDonorMatches(const QVector<DonorMatch>& matches);

private:
    QTableWidget *tableWidget;
    QPushButton *closeButton;
    QVBoxLayout *layout;
};

#endif // DONORMATCHWINDOW_H
