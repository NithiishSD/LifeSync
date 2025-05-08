#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "donor_page.h"
#include "factswindow.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <qscrollarea.h>
#include <QStackedWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVector>

// Struct to hold donor data and priority (distance + match score)
struct DonorMatch {
    QString name;
    QString email;
    QString phonenum;
    QString blood;
    QString organs;
    QString hospital;
    QString gender;
    int matchScore;    // Score from blood and organ match
    int distance;      // Shortest path distance from receiver's hospital
    int totalPriority; // matchScore - distance (higher is better)

    bool operator>(const DonorMatch& other) const {
        return totalPriority > other.totalPriority; // Max-heap for higher priority
    }
};

class PriorityQueue {
private:
    QVector<DonorMatch> heap;

    // Heapify up
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] > heap[index]) {
                std::swap(heap[parent], heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Heapify down
    void heapifyDown(int index) {
        int minIndex = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap.size() && heap[minIndex] > heap[left]) {
            minIndex = left;
        }
        if (right < heap.size() && heap[right] > heap[minIndex]) {
            minIndex = right;
        }

        if (minIndex != index) {
            std::swap(heap[index], heap[minIndex]);
            heapifyDown(minIndex);
        }
    }

public:
    void push(const DonorMatch& match) {
        heap.append(match);
        heapifyUp(heap.size() - 1);
    }

    DonorMatch pop() {
        if (heap.isEmpty()) {
            qDebug() << "Priority queue is empty!";
            return DonorMatch(); // Return default if empty
        }
        DonorMatch result = heap[0];
        heap[0] = heap.last();
        heap.pop_back();
        if (!heap.isEmpty()) {
            heapifyDown(0);
        }
        return result;
    }

    bool isEmpty() const {
        return heap.isEmpty();
    }

    int size() const {
        return heap.size();
    }
};

// Weighted graph as adjacency matrix
const int NUM_HOSPITALS = 8;
const QString hospitals[NUM_HOSPITALS] = {
    "City Hospital", "General Medical Center", "St. Mary’s Hospital",
    "Riverside Clinic", "Northside Health", "Southend Medical",
    "Eastview Hospital", "Westgate Center"
};
const int distanceMatrix[NUM_HOSPITALS][NUM_HOSPITALS] = {
    {0, 5, 10, 15, 20, 25, 30, 35},
    {5, 0, 7, 12, 17, 22, 27, 32},
    {10, 7, 0, 8, 13, 18, 23, 28},
    {15, 12, 8, 0, 10, 15, 20, 25},
    {20, 17, 13, 10, 0, 12, 17, 22},
    {25, 22, 18, 15, 12, 0, 10, 15},
    {30, 27, 23, 20, 17, 10, 0, 12},
    {35, 32, 28, 25, 22, 15, 12, 0}
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSize sizeHint() const override ;
    QLineEdit* email;
    QLineEdit* phonenum;
protected:
    void resizeEvent(QResizeEvent* ev) override;
protected slots:
    void etch(const QString&);
    void ptch(const QString&);

    void storeReceiverData(QLineEdit* lname, QLineEdit* lemail, QLineEdit* lphonenum, QComboBox* lblood, QComboBox* lorgans, QComboBox*hospital, QRadioButton* male, QLineEdit* pass, QLineEdit* repass);
    void storeDonorData(QLineEdit* lname, QLineEdit* lemail, QLineEdit* lphonenum, QComboBox* lblood, QComboBox* lorgans, QComboBox* hospital, QRadioButton* male);
    void open_donor_window();
    void open_donor_register();
    void open_login_window();

    void checkUser(const QString&, const QString&);
    void matchDonorsForReceiver(QLineEdit* nameEdit, QLineEdit* passEdit);
    void go_to_main();
    void go_to_donorp();
    void go_to_health_check();
    void open_receiver_window();
    void go_to_factsw();
    QString select_hospital_info(QString );
private:
    QLabel* background;
    QFrame *top_frame = nullptr;
    QFrame *ogd_popframe=nullptr;// declaring for resizing
    QFrame *rgd_popframe=nullptr;
    QLabel *donorf_image=nullptr;
    QScrollArea *donor_page=nullptr;
    QPushButton * register_do=nullptr;
    QWidget * donor=nullptr;
    Ui::MainWindow *ui;
    Donor_page *donorp=nullptr;
    Factswindow *factsw=nullptr;
    QPushButton *donorb=nullptr;
    QStackedWidget *stack=nullptr;
    QStackedWidget *rgstack=nullptr;//for register site stack
    QWidget *receiverReg =nullptr;
    QWidget *book_checkup=nullptr;
    QWidget *health_check=nullptr;
    QString hospital_info="";
    QLabel * hosinfo=nullptr;
    QPushButton *proceedButton=nullptr;
    bool if_registered=false;
    bool if_health_check=false;
};
#endif // MAINWINDOW_H
