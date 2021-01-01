#include "stuwidget.h"
#include "ui_stuwidget.h"

stuWidget::stuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stuWidget)
{
    ui->setupUi(this);
}

stuWidget::~stuWidget()
{
    delete ui;
}
