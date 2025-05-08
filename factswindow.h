#ifndef FACTSWINDOW_H
#define FACTSWINDOW_H

#include <QWidget>

namespace Ui {
class Factswindow;
}

class Factswindow : public QWidget
{
    Q_OBJECT

public:
    explicit Factswindow(QWidget *parent = nullptr);
    ~Factswindow();

private:
    Ui::Factswindow *ui;

signals:
    void button_clicked();
};

#endif // FACTSWINDOW_H
