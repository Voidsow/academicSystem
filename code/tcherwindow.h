#ifndef TCHERWINDOW_H
#define TCHERWINDOW_H

#include <QMainWindow>
#include<QStandardItemModel>
#include<QString>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QDebug>
#include<QItemSelection>
#include<QInputDialog>
#include"system.h"
#include"input.h"

namespace Ui {
class tcherWindow;
}

class tcherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit tcherWindow(const QString &_id,QWidget *parent = nullptr);
    void showCourse(course *crs);
    ~tcherWindow();

private slots:
    void on_action_altering_triggered();

    void on_action_statics_triggered();

    void on_action_sorting_triggered();

    void on_btn_change_clicked();

    void selectedChange(const QItemSelection &selected, const QItemSelection &deselected);

    void on_btn_search_clicked();

    void on_btn_filter_clicked();

    void on_action_reset_triggered();

private:
    Ui::tcherWindow *ui;
    QStandardItemModel *model;
    class system sys;
    course *crs;
    teacher *tcher;
    int selectedRow=-1;
    //显示范围内最后一个的下标
    int showIndex;
};

#endif // TCHERWINDOW_H
