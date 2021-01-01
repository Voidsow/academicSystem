#include "syswindow.h"
#include "ui_syswindow.h"

sysWindow::sysWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sysWindow),
    model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

sysWindow::sysWindow(const QString &id, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::sysWindow),
    model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();
    sys.read();
    sys.write();
    loadStu();
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,&sysWindow::change);
    connect(ui->tableView->selectionModel(),&QItemSelectionModel::selectionChanged,this,&sysWindow::select);
}

sysWindow::~sysWindow()
{
    delete ui;
}

void sysWindow::loadStu()
{
    model->clear();
    model->setHorizontalHeaderLabels(QStringList()<<"学号"<<"姓名"<<"专业"<<"班级");
    model->setColumnCount(4);
    if(sys.stuArray.size()!=0)
    {
        for (auto i=0;i!=sys.stuArray.size();i++)
        {
            model->setItem(i,0,new QStandardItem(QString::fromStdString(sys.stuArray[i].id)));
            model->setItem(i,1,new QStandardItem(QString::fromStdString(sys.stuArray[i].name)));
            model->setItem(i,2,new QStandardItem(QString::fromStdString(sys.stuArray[i].className)));
            model->setItem(i,3,new QStandardItem(QString::fromStdString(sys.stuArray[i].major)));
            if(sys.stuArray[i].name=="")
                ui->tableView->hideRow(i);
        }
    }
}

void sysWindow::loadTcher()
{
    model->clear();
    model->setHorizontalHeaderLabels(QStringList()<<"工号"<<"姓名");
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    model->setColumnCount(2);
    for (auto i=0;i!=sys.teacherArray.size();i++)
    {
        model->setItem(i,0,new QStandardItem(QString::fromStdString(sys.teacherArray[i].id)));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(sys.teacherArray[i].name)));
        if(sys.teacherArray[i].name=="")
            ui->tableView->hideRow(i);
    }
}

void sysWindow::loadCrs()
{
    model->clear();
    model->setHorizontalHeaderLabels(QStringList()<<"课程编号"<<"名称"<<"学分"<<"学时"<<"性质");
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    model->setColumnCount(5);
    for (auto i=0;i!=sys.crsArray.size();i++)
    {
        model->setItem(i,0,new QStandardItem(QString::fromStdString(sys.crsArray[i].id)));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(sys.crsArray[i].name)));
        model->setItem(i,2,new QStandardItem(QString::number(sys.crsArray[i].credit)));
        model->setItem(i,3,new QStandardItem(QString::number(sys.crsArray[i].hour)));
        if(sys.crsArray[i].isObligatory)
            model->setItem(i,4,new QStandardItem("必修"));
        else
            model->setItem(i,4,new QStandardItem("选修"));
        if(sys.crsArray[i].name=="")
            ui->tableView->hideRow(i);
    }
}

void sysWindow::change(const QString &combox)
{
    if(combox=="学生")
        loadStu();
    else if(combox=="教师")
        loadTcher();
    else
        loadCrs();
    choosing.clear();
}

void sysWindow::select(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndex index;
    foreach(index,selected.indexes())
    {
        if(index.column()==0)
        {
            if(ui->comboBox->currentText()=="学生")
                 choosing.push_back(sys.stuArray[index.row()].id);
            else if(ui->comboBox->currentText()=="教师")
                choosing.push_back(sys.teacherArray[index.row()].id);
            else
                choosing.push_back(sys.crsArray[index.row()].id);
            choosingRow.push_back(index.row());
        }
    }
    foreach(index,deselected.indexes())
    {
        if(index.column()==0)
        {
            if(ui->comboBox->currentText()=="学生")
                choosing.erase(qFind(choosing.begin(),choosing.end(),sys.stuArray[index.row()].id));
            else if(ui->comboBox->currentText()=="教师")
                choosing.erase(qFind(choosing.begin(),choosing.end(),sys.teacherArray[index.row()].id));
            else
                choosing.erase(qFind(choosing.begin(),choosing.end(),sys.crsArray[index.row()].id));
            for (auto i=choosingRow.begin();i!=choosingRow.end();i++)
            {
                if(*i==index.row())
                {
                    choosingRow.erase(i);
                    break;
                }
            }
        }
    }
}

void sysWindow::on_action_adding_triggered()
{
    Input * in;
    if(ui->comboBox->currentText()=="学生")
         in=new Input(Input::Student,this);
    else if(ui->comboBox->currentText()=="教师")
        in=new Input(Input::Teacher,this);
    else
        in=new Input(Input::Course,this);
    if(in->exec()==QDialog::Accepted)
    {
        QStringList stringList;
        if(ui->comboBox->currentText()=="学生")
        {
            stringList=in->returns(Input::Student);
            sys.stuArray.push_back(student(stringList.at(1).toStdString(),
                                           stringList.at(0).toStdString(),
                                           stringList.at(2).toStdString(),
                                           stringList.at(3).toStdString()));
            int row=model->rowCount();
            model->setItem(row,0,new QStandardItem(stringList.at(0)));
            model->setItem(row,1,new QStandardItem(stringList.at(1)));
            model->setItem(row,2,new QStandardItem(stringList.at(2)));
            model->setItem(row,3,new QStandardItem(stringList.at(3)));
            ui->tableView->setCurrentIndex(model->index(row,0));
        }
        else if(ui->comboBox->currentText()=="教师")
        {
            stringList=in->returns(Input::Teacher);
            sys.teacherArray.push_back(teacher(stringList.at(1).toStdString(),
                                           stringList.at(0).toStdString()));
            int row=model->rowCount();
            model->setItem(row,0,new QStandardItem(stringList.at(0)));
            model->setItem(row,1,new QStandardItem(stringList.at(1)));
            ui->tableView->setCurrentIndex(model->index(row,0));
        }
        else
        {
            stringList=in->returns(Input::Course);
            bool oblig=false;
            if(stringList.at(5)=="必修")
                oblig=true;
            sys.crsArray.push_back(course(stringList.at(0).toStdString(),
                                           stringList.at(1).toStdString(),
                                           stringList.at(2).toDouble(),
                                           stringList.at(3).toInt(),
                                            oblig));
            string s=stringList.at(4).toStdString();
            sys.searchTcher(stringList.at(4).toStdString())->addCourse(&sys.crsArray.back());
            int row=model->rowCount();
            model->setItem(row,0,new QStandardItem(stringList.at(0)));
            model->setItem(row,1,new QStandardItem(stringList.at(1)));
            model->setItem(row,2,new QStandardItem(stringList.at(2)));
            model->setItem(row,3,new QStandardItem(stringList.at(3)));
            model->setItem(row,4,new QStandardItem(stringList.at(5)));
            ui->tableView->setCurrentIndex(model->index(row,0));
        }
    }
    sys.write();
}

void sysWindow::on_action_altering_triggered()
{
    int mode;
    if(ui->comboBox->currentText()=="学生")
        mode=Input::Student;
    else if(ui->comboBox->currentText()=="教师")
        mode=Input::Teacher;
    else
        mode=Input::Course;
    for (int i=0;i<choosing.size();i++)
    {
        Input * in;
            in=new Input(mode,this);
        in->setWindowTitle(QString("输入第%1项信息").arg(i+1));
        if(in->exec()==QDialog::Accepted)
        {
            QStringList stringList;
            switch (mode)
            {
            case Input::Student:
                {
                stringList=in->returns(Input::Student);
                sys.stuArray[choosingRow[i]].change(stringList.at(1).toStdString(),
                                                    stringList.at(0).toStdString(),
                                                    stringList.at(2).toStdString(),
                                                    stringList.at(3).toStdString());
                choosing[i]=(stringList.at(0)).toStdString();
                qDebug()<<QString::fromStdString(choosing[i]);
                }
                break;
            case Input::Teacher:
            {
                stringList=in->returns(Input::Teacher);
                sys.teacherArray[choosingRow[i]].change(stringList.at(1).toStdString(),
                                               stringList.at(0).toStdString());
                choosing[i]=stringList.at(0).toStdString();
            }
                break;
            case Input::Course:
            {
                stringList=in->returns(Input::Course);
                bool oblig=false;
                if(stringList.at(5)=="必修")
                    oblig=true;
                string crsName=sys.crsArray[choosingRow[i]].name;
                sys.hasCrs(crsName)->deleteCourse(&sys.crsArray[choosingRow[i]]);
                sys.crsArray[choosingRow[i]].change(stringList.at(0).toStdString(),
                                               stringList.at(1).toStdString(),
                                               stringList.at(2).toDouble(),
                                               stringList.at(3).toInt(),
                                                oblig);
                sys.searchTcher(stringList.at(4).toStdString())->addCourse(&sys.crsArray[choosingRow[i]]);
                choosing[i]=stringList.at(0).toStdString();
            }
                break;
            default:
                break;
            }
        }
    }
    ui->tableView->clearSelection();
    switch (mode)
    {
    case Input::Student:
        loadStu();
        break;
    case Input::Teacher:
        loadTcher();
        break;
    case Input::Course:
        loadCrs();
        break;
    }
    sys.write();
}

void sysWindow::on_action_deleting_triggered()
{
    if(QMessageBox::Yes==QMessageBox::warning(this, tr("删除"),
                                              tr("是否删除信息?"),
                                              QMessageBox::Yes
                                              | QMessageBox::Cancel,
                                              QMessageBox::Yes))
    {
        //choosing中存放的是id
        if(choosing.size()!=0)
        {
            for(auto i=0;i<choosing.size();i++)
            {
                if(ui->comboBox->currentText()=="学生")
                {
                    sys.deleteStu(choosing[i]);
                    ui->tableView->hideRow(choosingRow[i]);
                }
                else if(ui->comboBox->currentText()=="教师")
                {
                    sys.deleteTcher(choosing[i]);
                    ui->tableView->hideRow(choosingRow[i]);
                }
                else
                {
                    sys.deleteCrs(choosing[i]);
                    ui->tableView->hideRow(choosingRow[i]);
                }
            }
        }
        ui->tableView->clearSelection();
    }
}
