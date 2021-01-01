#ifndef SYSWINDOW_H
#define SYSWINDOW_H

#include <QMainWindow>
#include<QStandardItemModel>
#include<QItemSelectionModel>
#include<QVector>
#include<QDebug>
#include<QMessageBox>
#include"system.h"
#include"input.h"

namespace Ui {
class sysWindow;
}

class sysWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit sysWindow(QWidget *parent = nullptr);
    sysWindow(const QString &id,QWidget *parent = nullptr);
    ~sysWindow();

    void loadStu();
    void loadTcher();
    void loadCrs();
    void showTcher();

public slots:
    void change(const QString &combox);
    void select(const QItemSelection &selected, const QItemSelection &deselected);

private slots:
    void on_action_adding_triggered();

    void on_action_altering_triggered();

    void on_action_deleting_triggered();

private:
    Ui::sysWindow *ui;
    QStandardItemModel *model;
    class system sys;
    vector<string> choosing;
    QVector<int>choosingRow;
};

#endif // SYSWINDOW_H
