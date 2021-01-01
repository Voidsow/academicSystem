#include "tcherwindow.h"
#include "ui_tcherwindow.h"

tcherWindow::tcherWindow(const QString &_id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tcherWindow),
    model(new QStandardItemModel (this))
{
    ui->setupUi(this);
    ui->tableView->setModel(model);
    model->setColumnCount(4);
    model->setHorizontalHeaderLabels(QStringList()<<"ID"<<"班级"<<"姓名"<<"成绩");
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,150);
    ui->tableView->setColumnWidth(3,150);
    sys.read();
    tcher=sys.searchTcher(_id.toStdString());
    crs=tcher->teaching[0];
    showIndex=crs->stuSet.size()-1;
    showCourse(crs);
    connect(ui->tableView->selectionModel(),&QItemSelectionModel::selectionChanged,this,&tcherWindow::selectedChange);
}

void tcherWindow::showCourse(course *crs)
{

    ui->label->setText(QString::fromStdString(crs->name));
    for (int i=0;i!=crs->stuSet.size();i++)
    {
        model->setItem(i,0,new QStandardItem(QString::fromStdString(crs->stuSet[i]->id)));
        model->setItem(i,1,new QStandardItem(QString::fromStdString(crs->stuSet[i]->className)));
        model->setItem(i,2,new QStandardItem(QString::fromStdString(crs->stuSet[i]->name)));
        model->setItem(i,3,new QStandardItem(QString::number(crs->stuSet[i]->getScore(crs->name))));
        if(i>showIndex)
            ui->tableView->hideRow(i);
    }
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,150);
    ui->tableView->setColumnWidth(3,150);
}

tcherWindow::~tcherWindow()
{
    delete ui;
}

void tcherWindow::on_action_altering_triggered()
{
    QStringList items;
    foreach(auto i,tcher->teaching)
    {
        items<<QString::fromStdString(i->name);
    }
    bool ok=false;
    QString text=QInputDialog::getItem(this,"切换课程","选择课程",items,0,false,&ok);
    if(ok)
        foreach(auto i,tcher->teaching)
        {
            if(i->name==text.toStdString())
            {
                showIndex=i->stuSet.size()-1;
                crs=i;
                showCourse(crs);
                break;
            }
        }
}

void tcherWindow::on_action_statics_triggered()
{
    QWidget *w=new QWidget(this,Qt::Window);
    w->resize(300,300);
    w->setWindowModality(Qt::ApplicationModal);
    w->setWindowTitle("统计信息");
    QLabel *average=new QLabel("平均分: "+QString::number(crs->getAverage()),w,Qt::Widget);
    average->show();
    QLabel *stdDeviation=new QLabel("标准差: "+QString::number(crs->getStandardDeviation()),w,Qt::Widget);
    stdDeviation->show();
    QLabel *passingRate=new QLabel("及格率: "+QString::number(crs->getPassingRate())+"%",w,Qt::Widget);
    passingRate->show();
    QPushButton *ok=new QPushButton("确定",w);
    ok->show();
    QVBoxLayout *layout=new QVBoxLayout(w);
    layout->addWidget(average,0,Qt::AlignHCenter);
    layout->addWidget(stdDeviation,0,Qt::AlignHCenter);
    layout->addWidget(passingRate,0,Qt::AlignHCenter);
    layout->addWidget(ok,0,Qt::AlignHCenter);
    w->setLayout(layout);
    w->show();
    connect(ok,&QPushButton::clicked,w,&QWidget::close);
}

void tcherWindow::on_action_sorting_triggered()
{
    crs->sort(showIndex);
    showCourse(crs);
}

void tcherWindow::on_btn_change_clicked()
{
    if(selectedRow!=-1)
    {
        bool ok;
        double score = QInputDialog::getDouble(this,"修改成绩",
                                           "输入"+QString::fromStdString(crs->stuSet[selectedRow]->name)+"的成绩",
                                           0.0,0.0,100.0,1,&ok);
        if (ok)
        {
            (crs->stuSet[selectedRow]->getScore(crs->name))=score;
            sys.write();
            qDebug()<<crs->stuSet[selectedRow]->getScore(crs->name)
                   <<QString::fromStdString(crs->stuSet[selectedRow]->name);
            model->setItem(selectedRow,0,new QStandardItem(QString::fromStdString(crs->stuSet[selectedRow]->id)));
            model->setItem(selectedRow,1,new QStandardItem(QString::fromStdString(crs->stuSet[selectedRow]->className)));
            model->setItem(selectedRow,2,new QStandardItem(QString::fromStdString(crs->stuSet[selectedRow]->name)));
            model->setItem(selectedRow,3,new QStandardItem(QString::number(score)));
            ui->tableView->setColumnWidth(0,200);
            ui->tableView->setColumnWidth(1,200);
            ui->tableView->setColumnWidth(2,150);
            ui->tableView->setColumnWidth(3,150);
        }
    }
}

void tcherWindow::selectedChange(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndex index;
    if(selected.indexes().size()==0)
        selectedRow=-1;
    else
        foreach(index,selected.indexes())
        {
            if(index.column()==0)
            {
                selectedRow=index.row();
            }
        }
}

void tcherWindow::on_btn_search_clicked()
{
   if(!ui->lineEdit->text().isEmpty())
   {
       int row=crs->searchByRange(ui->lineEdit->text().toStdString(),showIndex);
       qDebug()<<row;
        ui->tableView->scrollTo(model->index(row,0));
        ui->tableView->scrollTo(model->index(row,1));
        ui->tableView->scrollTo(model->index(row,2));
        ui->tableView->selectRow(row);
   }
}

void tcherWindow::on_btn_filter_clicked()
{
    Input *in=new Input(Input::ScoreRange,this);
    if(in->exec()==QDialog::Accepted)
    {
        QStringList stringlist;
        stringlist=in->returns(Input::Teacher);
        int maxIndex=crs->sortByRange(stringlist[0].toDouble(),stringlist[1].toDouble());
        for(auto i=0;i!=maxIndex+1;i++)
        {
            model->setItem(i,0,new QStandardItem(QString::fromStdString(crs->stuSet[i]->id)));
            model->setItem(i,1,new QStandardItem(QString::fromStdString(crs->stuSet[i]->className)));
            model->setItem(i,2,new QStandardItem(QString::fromStdString(crs->stuSet[i]->name)));
            model->setItem(i,3,new QStandardItem(QString::number(crs->stuSet[i]->getScore(crs->name))));
        }
        for(auto i=maxIndex+1;i!=crs->stuSet.size();i++)
        {
            model->setItem(i,0,new QStandardItem(QString::fromStdString(crs->stuSet[i]->id)));
            model->setItem(i,1,new QStandardItem(QString::fromStdString(crs->stuSet[i]->className)));
            model->setItem(i,2,new QStandardItem(QString::fromStdString(crs->stuSet[i]->name)));
            model->setItem(i,3,new QStandardItem(QString::number(crs->stuSet[i]->getScore(crs->name))));
            ui->tableView->hideRow(i);
        }
        ui->tableView->setColumnWidth(0,200);
        ui->tableView->setColumnWidth(1,200);
        ui->tableView->setColumnWidth(2,150);
        ui->tableView->setColumnWidth(3,150);
        showIndex=maxIndex;
    }
}

void tcherWindow::on_action_reset_triggered()
{
    showIndex=crs->stuSet.size()-1;
    showCourse(crs);
}
