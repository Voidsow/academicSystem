#include "widget.h"
#include"login.h"
#include<QMainWindow>
#include<QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login login;
    QMainWindow *w;
    if(login.exec()==QDialog::Accepted)
    {
        w=login.call();
        w->setWindowModality(Qt::WindowModality::ApplicationModal);
        w->show();
        return a.exec();
    }
}
