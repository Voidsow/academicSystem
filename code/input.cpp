#include "input.h"
#include "ui_input.h"

Input::Input(int mode, QWidget *parent)
    :QDialog(parent),
      ui(new Ui::Input)
{
    ui->setupUi(this);
    switch (mode)
    {
        case Input::Student:
            ui->label_5->hide();
            ui->label_6->hide();
            ui->lineEdit_5->hide();
            ui->comboBox->hide();
            show();
        break;
        case Input::Teacher:
            ui->label_3->hide();
            ui->label_4->hide();
            ui->label_5->hide();
            ui->label_6->hide();
            ui->lineEdit_3->hide();
            ui->lineEdit_4->hide();
            ui->lineEdit_5->hide();
            ui->comboBox->hide();
            show();
        break;
        case Input::Course:
        ui->label_2->setText("课程名称");
            ui->label_3->setText("学分：");
            ui->label_4->setText("学时");
            show();
        break;
    case Input::ScoreRange:
        ui->label->setText("最低分");
        ui->label_2->setText("最高分");
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();
        ui->label_6->hide();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();
        ui->comboBox->hide();
        show();
        default:
        break;
    }
}

//以QStringList形式返回输入的信息
QStringList Input::returns(int mode)
{
    switch (mode)
    {
        case Input::Student:
            return QStringList()<<ui->lineEdit->text()<<ui->lineEdit_2->text()<<ui->lineEdit_3->text()<<ui->lineEdit_4->text();
        case Input::Teacher:
            return QStringList()<<ui->lineEdit->text()<<ui->lineEdit_2->text();
        case Input::Course:
            return QStringList()<<ui->lineEdit->text()<<ui->lineEdit_2->text()<<ui->lineEdit_3->text()<<ui->lineEdit_4->text()
                               <<ui->lineEdit_5->text()<<ui->comboBox->currentText();
        case Input::ScoreRange:
            return QStringList()<<ui->lineEdit->text()<<ui->lineEdit_2->text();
        default:
            return QStringList();
    }
}

Input::~Input()
{
    delete ui;
}
