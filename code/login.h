#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include"stuwindow.h"
#include"tcherwindow.h"
#include"syswindow.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QMainWindow* call();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
