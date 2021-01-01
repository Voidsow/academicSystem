#ifndef STUWINDOW_H
#define STUWINDOW_H

#include <QMainWindow>
#include<QStandardItemModel>
#include<QItemSelection>
#include<QString>
#include<QStringList>
#include<QTableView>
#include<QVector>
#include<QtAlgorithms>
#include<QMessageBox>
#include<QDebug>
#include<string>
#include"system.h"

namespace Ui {
class stuWindow;
}

class stuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit stuWindow(QWidget *parent = nullptr);
    stuWindow(const QString &id,QWidget *parent=nullptr);
    ~stuWindow();

    void showTaking();
    void showChoosing();
public slots:
    void update(const QItemSelection &selected, const QItemSelection &deselected);
    void changingCourse();
    void changingOblig(const QString &text);

    void showChoosingAfter(const QString &combox);
private:
    Ui::stuWindow *ui;

    class system sys;
    student *stu;
    QStandardItemModel *model;
    //��ǰ������ʾ�������ͣ�0Ϊ��ѡ�γ̣�1Ϊ��ѡ�γ�
    int state=0;
    QVector<string> choosingCrs;
};

#endif // STUWINDOW_H
