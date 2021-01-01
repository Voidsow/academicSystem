#include "system.h"

void system::read()
{
    qDebug()<<QDir::currentPath();
    ifstream in("student.txt");
    if(!in.is_open())
        qDebug()<<"failed";
    string line;
    string fromQline;
    getline(in,line);
    while (getline(in,line)&&line != "#END")
    {
        student stu1(line);
        stuArray.push_back(stu1);
    }
    int l=0;
    in.close();

    in.open("module.txt");
	getline(in, line);
	while (getline(in, line) && line != "#END")
	{
		crsArray.push_back(course(line));
	}
    int d=0;
	in.close();


    in.open("score.txt");
	getline(in, line);
	while (getline(in, line) && line != "#END")
	{
		string id;
		string name, crs;
		double score;
		istringstream input(line);
		input >> id >> name >> crs >> score;
        student* p=searchStu(id);
        p->addCourse(crs,score);
        searchCourse(crs)->addStu(p);
	}
    int f=0;
	in.close();


    in.open("staff.txt");
	getline(in, line);
	while (getline(in, line) && line != "#END")
	{
		string s, s1;
		istringstream input(line);
		input >> s >> s1;
		teacherArray.push_back(teacher(s1, s));
		while (input >> s)
		{
            teacherArray.back().addCourse(searchCourse(s));
		}
	}
    int g=0;
    in.close();
}

void system::write()
{
    QFile file("student.txt");
    if(!file.open(QFile::WriteOnly | QIODevice::Truncate))
        qDebug()<<"failedf";
    else
    {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out<<QString::fromLocal8Bit("#学号(ID)\t姓名\t班级\t专业\n");
        for(auto i=0;i<stuArray.size();i++)
            if(stuArray[i].name!="")
            {
                out<<QString::fromStdString(stuArray[i].id)<<'\t'
                  <<QString::fromStdString(stuArray[i].name)<<'\t'
                 <<QString::fromStdString(stuArray[i].className)<<'\t'
                <<QString::fromStdString(stuArray[i].major)<<'\n';
            }
        out<<"#END";
        file.close();

        file.setFileName("module.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#课程编号\t课程名称\t学分\t学时\t课程类别\n");
        for(auto i=0;i<crsArray.size();i++)
        {
            if(!(crsArray[i].name==""))
            {
                out<<QString::fromStdString(crsArray[i].id)<<'\t'
                  <<QString::fromStdString(crsArray[i].name)<<'\t'
                 <<QString::number(crsArray[i].credit)<<'\t'
                <<QString::number(crsArray[i].hour)<<'\t';
                if(crsArray[i].isObligatory)
                    out<<QString::fromLocal8Bit("必修")<<'\n';
                else
                    out<<QString::fromLocal8Bit("选修")<<'\n';
            }
        }
        out<<"#END";
        file.close();

        file.setFileName("score.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#学号\t姓名\t课程名称\t成绩\n");
        for(auto i=0;i<stuArray.size();i++)
            if(stuArray[i].name!="")
                for(auto j=0;j<stuArray[i].taking.size();j++)
                {
                    out<<QString::fromStdString(stuArray[i].id)<<'\t'
                      <<QString::fromStdString(stuArray[i].name)<<'\t'
                     <<QString::fromStdString(stuArray[i].taking[j].name)<<'\t'
                    <<QString::number(stuArray[i].taking[j].score)<<'\n';
                }
        out<<"#END";
        file.close();

        file.setFileName("staff.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#工号（ID）\t姓名\t授课\n");
        for(auto i=0;i<teacherArray.size();i++)
        {
            if(teacherArray[i].name!="")
            {
                out<<QString::fromStdString(teacherArray[i].id)<<'\t'
                  <<QString::fromStdString(teacherArray[i].name);
                for(auto j=0;j<teacherArray[i].teaching.size();j++)
                    if(teacherArray[i].teaching[j]!=nullptr)
                        out<<'\t'<<QString::fromStdString(teacherArray[i].teaching[j]->name);
            }
            out<<'\n';
        }
        out<<"#END";
        file.close();
    }
}


course* system::searchCourse(const string & crs)
{
	for (int i = 0; i != crsArray.size(); i++)
        if (crsArray[i].name== crs||crsArray[i].id==crs)
            return &crsArray[i];
	return nullptr;
}


student* system::searchStu(const string& stu)
{
    if(stuArray.size()!=0)
    {
        for (int i = 0; i != stuArray.size(); i++)
            if (stuArray[i].id == stu||stuArray[i].name==stu)
                return &(stuArray[i]);
    }
    return nullptr;
}

teacher *system::searchTcher(const std::string &tcher)
{
    for (int i = 0; i != teacherArray.size(); i++)
        if (teacherArray[i].id == tcher||teacherArray[i].name==tcher)
            return &(teacherArray[i]);
    return nullptr;
}

void system::deleteStu(const std::string &stu)
{
    if(crsArray.size()!=0)
        for(auto i=0;i!=crsArray.size();i++)
        {
            if(crsArray[i].name!="")
                if(crsArray[i].stuSet.size()!=0)
                {
                    for(int j=0;j!=crsArray[i].stuSet.size();j++)
                        if(crsArray[i].stuSet[j]!=nullptr)
                            if(crsArray[i].stuSet[j]->id==stu)
                            {
                                crsArray[i].stuSet[j]=nullptr;
                                break;
                            }
                }
        }
    if(stuArray.size()!=0)
    {
        for(int i=0;i!=stuArray.size();i++)
            if(stuArray[i].name!="")
                if(stuArray[i].id==stu)
                {
                    stuArray[i].name="";
                    break;
                }
        int d=0;
    }

    QFile file("student.txt");
    if(!file.open(QFile::WriteOnly | QIODevice::Truncate))
        qDebug()<<"failedf";
    else
    {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out<<QString::fromLocal8Bit("#学号(ID)\t姓名\t班级\t专业\n");
        for(auto i=0;i<stuArray.size();i++)
            if(stuArray[i].name!="")
            {
                out<<QString::fromStdString(stuArray[i].id)<<'\t'
                  <<QString::fromStdString(stuArray[i].name)<<'\t'
                 <<QString::fromStdString(stuArray[i].className)<<'\t'
                <<QString::fromStdString(stuArray[i].major)<<'\n';
            }
        out<<"#END";
        file.close();

        file.setFileName("module.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#课程编号\t课程名称\t学分\t学时\t课程类别\n");
        for(auto i=0;i<crsArray.size();i++)
        {
            if(!(crsArray[i].name==""))
            {
                out<<QString::fromStdString(crsArray[i].id)<<'\t'
                  <<QString::fromStdString(crsArray[i].name)<<'\t'
                 <<QString::number(crsArray[i].credit)<<'\t'
                <<QString::number(crsArray[i].hour)<<'\t';
                if(crsArray[i].isObligatory)
                    out<<QString::fromLocal8Bit("必修")<<'\n';
                else
                    out<<QString::fromLocal8Bit("选修")<<'\n';
            }
        }
        out<<"#END";
        file.close();

        file.setFileName("score.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#学号\t姓名\t课程名称\t成绩\n");
        for(auto i=0;i<stuArray.size();i++)
            if(stuArray[i].name!="")
                for(auto j=0;j<stuArray[i].taking.size();j++)
                {
                    out<<QString::fromStdString(stuArray[i].id)<<'\t'
                      <<QString::fromStdString(stuArray[i].name)<<'\t'
                     <<QString::fromStdString(stuArray[i].taking[j].name)<<'\t'
                    <<QString::number(stuArray[i].taking[j].score)<<'\n';
                }
        out<<"#END";
        file.close();

        file.setFileName("staff.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#工号（ID）\t姓名\t授课\n");
        for(auto i=0;i<teacherArray.size();i++)
        {
            if(teacherArray[i].name!="")
            {
                out<<QString::fromStdString(teacherArray[i].id)<<'\t'
                  <<QString::fromStdString(teacherArray[i].name);
                for(auto j=0;j<teacherArray[i].teaching.size();j++)
                    if(teacherArray[i].teaching[j]!=nullptr)
                        out<<'\t'<<QString::fromStdString(teacherArray[i].teaching[j]->name);
            }
            out<<'\n';
        }
        out<<"#END";
        file.close();
    }
}

void system::deleteTcher(const string &tcher)
{
    if(teacherArray.size()!=0)
    {
        for(auto i=0;i<teacherArray.size();i++)
        {
            if(teacherArray[i].name!=""&&teacherArray[i].id==tcher)
            {
                if(teacherArray[i].teaching.size()!=0)
                {
                    for(auto j=0;j<teacherArray[i].teaching.size();j++)
                        if(teacherArray[i].teaching[j]!=nullptr)
                        {
                            for(auto k=0;k<teacherArray[i].teaching[j]->stuSet.size();k++)
                                if((teacherArray[i].teaching[j]->stuSet[k]!=nullptr)&&teacherArray[i].teaching[j]->stuSet[k]->name!="")
                                {
                                    teacherArray[i].teaching[j]->stuSet[k]->cancelCourse(teacherArray[i].teaching[j]->name);
                                }
                            teacherArray[i].teaching[j]->name="";
                            teacherArray[i].teaching[j]=nullptr;
                        }
                }
                teacherArray[i].name="";
            }
        }
    }

    QFile file("student.txt");
    if(!file.open(QFile::WriteOnly | QIODevice::Truncate))
            qDebug()<<"open failed";
    else
    {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out<<QString::fromLocal8Bit("#学号(ID)\t姓名\t班级\t专业\n");
        for(auto i=0;i<stuArray.size();i++)
            if(stuArray[i].name!="")
            {
                out<<QString::fromStdString(stuArray[i].id)<<'\t'
                  <<QString::fromStdString(stuArray[i].name)<<'\t'
                 <<QString::fromStdString(stuArray[i].className)<<'\t'
                <<QString::fromStdString(stuArray[i].major)<<'\n';
            }
        out<<"#END";
        file.close();

        file.setFileName("module.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#课程编号\t课程名称\t学分\t学时\t课程类别\n");
        for(auto i=0;i<crsArray.size();i++)
        {
            if(!(crsArray[i].name==""))
            {
                out<<QString::fromStdString(crsArray[i].id)<<'\t'
                  <<QString::fromStdString(crsArray[i].name)<<'\t'
                 <<QString::number(crsArray[i].credit)<<'\t'
                <<QString::number(crsArray[i].hour)<<'\t';
                if(crsArray[i].isObligatory)
                    out<<QString::fromLocal8Bit("必修")<<'\n';
                else
                    out<<QString::fromLocal8Bit("选修")<<'\n';
            }
        }
        out<<"#END";
        file.close();

        file.setFileName("score.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#学号\t姓名\t课程名称\t成绩\n");
        for(auto i=0;i<stuArray.size();i++)
            if(stuArray[i].name!="")
                for(auto j=0;j<stuArray[i].taking.size();j++)
                {
                    out<<QString::fromStdString(stuArray[i].id)<<'\t'
                      <<QString::fromStdString(stuArray[i].name)<<'\t'
                     <<QString::fromStdString(stuArray[i].taking[j].name)<<'\t'
                    <<QString::number(stuArray[i].taking[j].score)<<'\n';
                }
        out<<"#END";
        file.close();

        file.setFileName("staff.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#工号（ID）\t姓名\t授课\n");
        for(auto i=0;i<teacherArray.size();i++)
        {
            if(teacherArray[i].name!="")
            {
                out<<QString::fromStdString(teacherArray[i].id)<<'\t'
                  <<QString::fromStdString(teacherArray[i].name);
                for(auto j=0;j<teacherArray[i].teaching.size();j++)
                    if(teacherArray[i].teaching[j]!=nullptr)
                        out<<'\t'<<QString::fromStdString(teacherArray[i].teaching[j]->name);
                out<<'\n';
            }
        }
        out<<"#END";
        file.close();
    }

}

void system::deleteCrs(const string &crs)
{
    if(crsArray.size()!=0)
    {
        for(auto i=0;i<crsArray.size();i++)
        {
            if(crsArray[i].name != ""&&crsArray[i].id==crs)
                {
                    for(auto j=0;j<teacherArray.size();j++)
                        if(teacherArray[j].name!="")
                        {
                            if(teacherArray[j].teaching.size()!=0)
                                for(auto k=0;k<teacherArray[j].teaching.size();k++)
                                {
                                    if(teacherArray[j].teaching[k]!=nullptr&&teacherArray[j].teaching[k]->id==crs)
                                        teacherArray[j].teaching[k]=nullptr;
                                }
                        }
                    if(crsArray[i].stuSet.size()!=0)
                        for(auto j=0;j<crsArray[i].stuSet.size();j++)
                        {
                            if(crsArray[i].stuSet[j]!=nullptr)
                            {
                                crsArray[i].stuSet[j]->cancelCourse(crsArray[i].name);
                            }
                        }
                    crsArray[i].name="";
                    break;
                }
        }
    }

    QFile file("student.txt");
    if(!file.open(QFile::WriteOnly | QIODevice::Truncate))
        qDebug()<<"failedf";
    else
    {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out<<QString::fromLocal8Bit("#学号(ID)\t姓名\t班级\t专业\n");
        for(auto i=0;i<stuArray.size();i++)
            if(stuArray[i].name!="")
            {
                out<<QString::fromStdString(stuArray[i].id)<<'\t'
                  <<QString::fromStdString(stuArray[i].name)<<'\t'
                 <<QString::fromStdString(stuArray[i].className)<<'\t'
                <<QString::fromStdString(stuArray[i].major)<<'\n';
            }
        out<<"#END";
        file.close();

        file.setFileName("module.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#课程编号\t课程名称\t学分\t学时\t课程类别\n");
        for(auto i=0;i<crsArray.size();i++)
        {
            if(!(crsArray[i].name==""))
            {
                out<<QString::fromStdString(crsArray[i].id)<<'\t'
                  <<QString::fromStdString(crsArray[i].name)<<'\t'
                 <<QString::number(crsArray[i].credit)<<'\t'
                <<QString::number(crsArray[i].hour)<<'\t';
                if(crsArray[i].isObligatory)
                    out<<QString::fromLocal8Bit("必修")<<'\n';
                else
                    out<<QString::fromLocal8Bit("选修")<<'\n';
            }
        }
        out<<"#END";
        file.close();

        file.setFileName("score.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#学号\t姓名\t课程名称\t成绩\n");
        for(auto i=0;i<stuArray.size();i++)
            if(stuArray[i].name!="")
                for(auto j=0;j<stuArray[i].taking.size();j++)
                {
                    out<<QString::fromStdString(stuArray[i].id)<<'\t'
                      <<QString::fromStdString(stuArray[i].name)<<'\t'
                     <<QString::fromStdString(stuArray[i].taking[j].name)<<'\t'
                    <<QString::number(stuArray[i].taking[j].score)<<'\n';
                }
        out<<"#END";
        file.close();

        file.setFileName("staff.txt");
        file.open(QFile::WriteOnly | QIODevice::Truncate);
        out<<QString::fromLocal8Bit("#工号（ID）\t姓名\t授课\n");
        for(auto i=0;i<teacherArray.size();i++)
        {
            if(teacherArray[i].name!="")
            {
                out<<QString::fromStdString(teacherArray[i].id)<<'\t'
                  <<QString::fromStdString(teacherArray[i].name);
                for(auto j=0;j<teacherArray[i].teaching.size();j++)
                    if(teacherArray[i].teaching[j]!=nullptr)
                        out<<'\t'<<QString::fromStdString(teacherArray[i].teaching[j]->name);
            }
            out<<'\n';
        }
        out<<"#END";
        file.close();
    }
}

teacher *system::hasCrs(const std::string &crs)
{
    if(teacherArray.size()!=0)
    {
        for(int i=0;i<teacherArray.size();i++)
        {
            int f=0;
            for(int j=0;j<teacherArray[i].teaching.size();j++)
            {
                if(teacherArray[i].teaching[j]!=nullptr)
                {
                    if(teacherArray[i].teaching[j]->name==crs||teacherArray[i].teaching[j]->id==crs)
                    {
                        int b=0;
                        return &(teacherArray[i]);
                    }

                }
            }
        }
    return  nullptr;
    }
}

double system::creditGetted(const std::string &stu)
{
    double sum=0.0;
    student *s=searchStu(stu);
  for(auto i=s->taking.begin();i!=s->taking.end();i++)
    {
        sum+=searchCourse(i->name)->credit;
    }
    return sum;
}

