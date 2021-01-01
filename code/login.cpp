#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

QMainWindow *Login::call()
{
    if(ui->comboBox->currentText()==QString::fromLocal8Bit("ѧ��"))
    {
        stuWindow* w=new stuWindow(ui->lineEdit_id->text(),this);
        return w;
    }
    else if(ui->comboBox->currentText()==QString::fromLocal8Bit("��ʦ"))
        {
        tcherWindow *w=new tcherWindow(ui->lineEdit_id->text(),this);
        return w;
    }
    else
        {
        sysWindow *w=new sysWindow(ui->lineEdit_id->text(),this);
        return w;
    }
}

