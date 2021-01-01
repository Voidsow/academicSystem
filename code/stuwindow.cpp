#include "stuwindow.h"
#include "ui_stuwindow.h"

stuWindow::stuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::stuWindow),
    model(new QStandardItemModel(this))
{
    sys.read();
    ui->setupUi(this);
}

stuWindow::stuWindow(const QString &id,QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::stuWindow),
    model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    sys.read();
    stu=sys.searchStu(id.toStdString());
    showTaking();
    connect(ui->action_selecting,&QAction::triggered,this,&stuWindow::showChoosing);
    connect(ui->action_taking,&QAction::triggered,this,&stuWindow::showTaking);
    connect(ui->tableView->selectionModel(),&QItemSelectionModel::selectionChanged,this,&stuWindow::update);
    connect(ui->btn_adding,&QPushButton::clicked,this,&stuWindow::changingCourse);
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,&stuWindow::showChoosingAfter);
}

stuWindow::~stuWindow()
{
    delete ui;
    delete  model;
}

void stuWindow::showTaking()
{
    ui->comboBox->hide();
    if(state==1)
        choosingCrs.clear();
    ui->btn_adding->setText("退选课程");
    state=0;
    ui->label_l->setText("已修学分："+QString::number(sys.creditGetted(stu->name)));
    ui->label_r->hide();
    model->clear();
    model->setColumnCount(6);
    model->setRowCount(stu->taking.size());
    model->setHorizontalHeaderLabels(QStringList()<<"课程编号"<<"课程名称"<<"学分"<<"学时"<<"课程类别"<<"成绩");
    for(auto i=0;i!=model->rowCount();i++)
    {
        course *pc=sys.searchCourse(stu->taking[i].name);
        model->setItem(i,0,new QStandardItem(QString::fromStdString(pc->id)));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(pc->name)));
        model->setItem(i,2,new QStandardItem(QString::number(pc->credit)));
        model->setItem(i,3,new QStandardItem(QString::number(pc->hour)));
        if(pc->isObligatory==true)
            model->setItem(i,4,new QStandardItem("必修"));
        else
            model->setItem(i,4,new QStandardItem("选修"));
        ui->tableView->setColumnWidth(5,100);
        model->setItem(i,5,new QStandardItem(QString::number(stu->taking[i].score)));
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(0,150);
        ui->tableView->setColumnWidth(2,100);
        ui->tableView->setColumnWidth(3,100);
        ui->tableView->setColumnWidth(4,100);
    }
}

void stuWindow::showChoosing()
{
    ui->comboBox->show();
    if(state==0)
        choosingCrs.clear();
    ui->btn_adding->show();
    ui->btn_adding->setText("添加课程");
    state=1;
    ui->label_l->setText("已选学分：0");
    if(CREDIT-sys.creditGetted(stu->name)<0.0)
        ui->label_r->setText("仍需选学分:0");
    else
        ui->label_r->setText("仍需选学分"+QString::number(CREDIT-sys.creditGetted(stu->name)));
    ui->label_r->show();
    model->clear();
    model->setColumnCount(5);
    ui->tableView->setColumnWidth(0,150);
    ui->tableView->setColumnWidth(1,300);
    ui->tableView->setColumnWidth(2,100);
    ui->tableView->setColumnWidth(3,100);
    ui->tableView->setColumnWidth(4,100);
    model->setHorizontalHeaderLabels(QStringList()<<"课程编号"<<"课程名称"<<"学分"<<"学时"<<"课程类别");
    for(auto i=0;i!=sys.crsArray.size();i++)
    {
            model->setItem(i,0,new QStandardItem(QString::fromStdString(sys.crsArray[i].id)));
            model->setItem(i,1,new QStandardItem(QString::fromStdString(sys.crsArray[i].name)));
            model->setItem(i,2,new QStandardItem(QString::number(sys.crsArray[i].credit)));
            model->setItem(i,3,new QStandardItem(QString::number(sys.crsArray[i].hour)));
            if(sys.crsArray[i].isObligatory==true)
                model->setItem(i,4,new QStandardItem("必修"));
            else
                model->setItem(i,4,new QStandardItem("选修"));
        if(stu->isTaking(sys.crsArray[i].name))
            ui->tableView->hideRow(i);
        else
            ui->tableView->showRow(i);
        //ui->tableView->verticalHeader()->hide();
    }
    changingOblig(ui->comboBox->currentText());
}

void stuWindow::showChoosingAfter(const QString &combox)
{
    ui->comboBox->show();
    if(state==0)
        choosingCrs.clear();
    ui->btn_adding->setText("添加课程");
    ui->btn_adding->show();
    state=1;
    ui->label_l->setText("已选学分：0");
    if(CREDIT-sys.creditGetted(stu->name)<0.0)
        ui->label_r->setText("仍需选学分:0");
    else
        ui->label_r->setText("仍需选学分"+QString::number(CREDIT-sys.creditGetted(stu->name)));
    ui->label_r->show();
    model->clear();
    model->setColumnCount(5);
    ui->tableView->setColumnWidth(0,150);
    ui->tableView->setColumnWidth(1,300);
    ui->tableView->setColumnWidth(2,100);
    ui->tableView->setColumnWidth(3,100);
    ui->tableView->setColumnWidth(4,100);
    model->setHorizontalHeaderLabels(QStringList()<<"课程编号"<<"课程名称"<<"学分"<<"学时"<<"课程类别");
    for(auto i=0;i!=sys.crsArray.size();i++)
    {


            model->setItem(i,0,new QStandardItem(QString::fromStdString(sys.crsArray[i].id)));
            model->setItem(i,1,new QStandardItem(QString::fromStdString(sys.crsArray[i].name)));
            model->setItem(i,2,new QStandardItem(QString::number(sys.crsArray[i].credit)));
            model->setItem(i,3,new QStandardItem(QString::number(sys.crsArray[i].hour)));
            if(sys.crsArray[i].isObligatory==true)
                model->setItem(i,4,new QStandardItem("必修"));
            else
                model->setItem(i,4,new QStandardItem("选修"));
        if(stu->isTaking(sys.crsArray[i].name))
            ui->tableView->hideRow(i);
        else
            ui->tableView->showRow(i);
        ui->tableView->verticalHeader()->hide();
    }
    changingOblig(combox);
}

void stuWindow::update(const QItemSelection &selected, const QItemSelection &deselected)
{
    //添加课程
    if(state==1)
    {
        //获取选区课程
        QModelIndex index;
        QModelIndexList selectedItems = selected.indexes();
        foreach(index,selectedItems)
        {
            if(index.column()==1)
            {
                qDebug()<<index.row();
                qDebug()<<QString::fromStdString(sys.crsArray[index.row()].name);
                choosingCrs.push_back(sys.crsArray[index.row()].name);
            }
        }
        foreach(index,deselected.indexes())
        {
            if(index.column()==1)
            {
                //qDebug()<<index.row();
                //qDebug()<<QString::fromStdString(stu->taking[index.row()].name);
                choosingCrs.erase(qFind(choosingCrs.begin(),choosingCrs.end(),sys.crsArray[index.row()].name));
            }
        }
        QString crsName;
        double sumCredit=0.0,needing;
        for(auto i:choosingCrs)
        {
            sumCredit+=sys.searchCourse(i)->credit;
        }
        ui->label_l->setText("已选学分："+QString::number(sumCredit));
        //qDebug()<<sys.creditGetted(stu->name);
        needing=CREDIT-sys.creditGetted(stu->name)-sumCredit;
        if(needing<0.0)
            needing=0.0;
        ui->label_r->setText("仍需选学分："+QString::number(needing));

    }
    else
    {
        QModelIndex index;
        foreach(index,selected.indexes())
        {
            if(index.column()==1)
                choosingCrs.push_back(stu->taking[index.row()].name);
        }
        foreach(index,deselected.indexes())
        {
            if(index.column()==1)
                choosingCrs.erase(qFind(choosingCrs.begin(),choosingCrs.end(),stu->taking[index.row()].name));
        }
    }
}

void stuWindow::changingCourse()
{
    if(choosingCrs.length()!=0)
    {
        if(state==1)
        {
            if (QMessageBox::Yes == QMessageBox::question(this,
                                                      tr("添加课程"),
                                                      tr("是否添加选中课程?"),
                                                      QMessageBox::Yes | QMessageBox::No,
                                                      QMessageBox::Yes))
            {
                for (auto i=choosingCrs.begin();i<choosingCrs.end();i++)
                {
                    stu->addCourse(*i,0);
                    sys.searchCourse(*i)->addStu(stu);
                }
                sys.write();
            }
            choosingCrs.clear();
            showChoosing();
        }
        else
        {
            if (QMessageBox::Yes == QMessageBox::question(this,
                                                          tr("退选课程"),
                                                          tr("是否退选选中课程?"),
                                                          QMessageBox::Yes | QMessageBox::No,
                                                          QMessageBox::Yes))
            {
                for (int i=0;i!=choosingCrs.length();i++)
                {
                    stu->cancelCourse(choosingCrs[i]);
                    sys.searchCourse(choosingCrs[i])->deleteStu(stu);
                }
                sys.write();
            }
            choosingCrs.clear();
            showTaking();
        }

    }
}

void stuWindow::changingOblig(const QString &text)
{
    if(state==1)
        for(int i=0;i!=model->rowCount();i++)
        {
            if( (text=="必修"&&(!sys.crsArray[i].isObligatory)) || (text=="选修"&&sys.crsArray[i].isObligatory) )
                ui->tableView->hideRow(i);
        }
    else
        for(int i=0;i!=model->rowCount();i++)
        {
            if( ( (text=="必修")&&(!sys.searchCourse(stu->taking[i].name)->isObligatory) )
                    ||  ( (text=="选修")&&(sys.searchCourse(stu->taking[i].name)->isObligatory) ) )
                ui->tableView->hideRow(i);
        }
    choosingCrs.clear();
}
