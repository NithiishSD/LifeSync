#include "donormatchwindow.h"
#include <QHeaderView>

DonorMatchWindow::DonorMatchWindow(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Eligible Donors");
    setMinimumSize(800, 400);

    // Initialize UI elements
    tableWidget = new QTableWidget(this);
    closeButton = new QPushButton("Close", this);

    // Set up table columns
    QStringList headers = {"Score", "Distance", "Name", "Email", "Phone", "Blood", "Organs", "Hospital", "Gender"};
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Connect close button
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

    // Layout
    layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);
    layout->addWidget(closeButton);
    setLayout(layout);
}

DonorMatchWindow::~DonorMatchWindow()
{
}

void DonorMatchWindow::setDonorMatches(const QVector<DonorMatch>& matches) {
    tableWidget->setRowCount(matches.size());

    for (int i = 0; i < matches.size(); ++i) {
        const DonorMatch& match = matches[i];
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(match.matchScore)));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(match.distance)));
        tableWidget->setItem(i, 2, new QTableWidgetItem(match.name));
        tableWidget->setItem(i, 3, new QTableWidgetItem(match.email));
        tableWidget->setItem(i, 4, new QTableWidgetItem(match.phonenum));
        tableWidget->setItem(i, 5, new QTableWidgetItem(match.blood));
        tableWidget->setItem(i, 6, new QTableWidgetItem(match.organs));
        tableWidget->setItem(i, 7, new QTableWidgetItem(match.hospital));
        tableWidget->setItem(i, 8, new QTableWidgetItem(match.gender));
    }
}
