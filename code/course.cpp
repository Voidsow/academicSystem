#include "course.h"

course::course()
	:id(""), name(""), credit(0), hour(0), isObligatory(true)
{
	
}

course::course(const course& crs)
    : id(crs.id), name(crs.name), credit(crs.credit), hour(crs.hour), isObligatory(crs.isObligatory),stuSet(crs.stuSet)
{
}

course::course(string _id, string _name, double _credit, int _hour, bool _isOblig)
	:id(_id),name(_name),credit(_credit),hour(_hour),isObligatory(_isOblig)
{
}

void course::addStu(student *stu)
{
    stuSet.push_back(stu);
}

void course::deleteStu(student *stu)
{
    for(auto i=stuSet.begin();i!=stuSet.end();i++)
        if(*i==stu)
        {
            stuSet.erase(i);
            break;
        }
}

void course::deleteStu(const int &index)
{
    stuSet.erase(stuSet.begin()+index);
}

course::course(const string& line)
{
	std::istringstream in(line);
	in >> id >> name >> credit >> hour;
	string s;
	in >> s;
    QString qs=QString::fromLocal8Bit("必修");
    if (s==qs.toStdString())
		isObligatory = true;
	else
        isObligatory = false;
}

void course::change(const std::string &_id, const std::string &_name, const double &_credit, const int &_hour, bool _isOblig)
{
    id=_id;
    name=_name;
    credit=_credit;
    hour=_hour;
    isObligatory=_isOblig;
}

double course::getAverage()
{
    double sum=0;
    for(auto i=0;i!=stuSet.size();i++)
    {
        sum+=stuSet[i]->getScore(name);
    }
    return sum/stuSet.size();
}

double course::getStandardDeviation()
{
    double sum=0;
    for(auto i=0;i!=stuSet.size();i++)
    {
        sum+=pow(stuSet[i]->getScore(name),2.0);
    }
    return sqrt(sum/stuSet.size());
}

double course::getPassingRate()
{
    double sum=0;
    for(auto i=0;i!=stuSet.size();i++)
    {
        double score=stuSet[i]->getScore(name);
        if(score>=60.0)
            sum+=score;
    }
    return sum/stuSet.size();
}

//排序范围内最后一个下标：lastIndex
void course::sort(const int &lastIndex)
{
    for(auto i=0;i!=lastIndex+1;i++)
    {
        for(auto j=i+1;j!=lastIndex+1;j++)
        {
            if(stuSet[j]->getScore(name)>stuSet[i]->getScore(name))
            {
                student *temp=stuSet[j];
                stuSet[j]=stuSet[i];
                stuSet[i]=temp;
            }
        }
    }
}

int course::sortByRange(const double &min,const double &max)
{
    //分类存放
    vector<student *> in,out;
    vector<bool> inB,outB;
    for(auto i=0;i!=stuSet.size();i++)
    {
        if(stuSet[i]->isInRange(name,min,max))
        {
            in.push_back(stuSet[i]);
            inB.push_back(true);
        }
        else
        {
            out.push_back(stuSet[i]);
            outB.push_back(false);
        }
    }

    stuSet.clear();

    //范围内在前面，范围外在后面
    for(auto i=0;i!=in.size();i++)
    {
        stuSet.push_back(in[i]);
    }

    for(auto i=0;i!=out.size();i++)
    {
        stuSet.push_back(out[i]);
    }

    return in.size()-1;
    for(auto i=0;i!=stuSet.size();i++)
    {
        if(stuSet[i]->isInRange(name,min,max))
            qDebug("true");
        else
            qDebug("false");
        if(!stuSet[i]->isInRange(name,min,max))
            return i;
    }
}

int course::searchByRange(const string &stu, const int &lastIndex)
{
    for(auto i=0;i!=lastIndex+1;i++)
    {
        if(stuSet[i]->id==stu||stuSet[i]->name==stu)
            return i;
    }
    return -1;
}

bool course::operator==(const course &other)
{
    if(other.id==id&&other.name==name)
        return true;
    else
        return false;
}

void course::write(std::ofstream &out)
{
    out<<id<<'\t'<<name<<'\t'<<credit<<'\t'<<hour<<'\t';
    if(isObligatory)
        out<<"必修"<<'\n';
    else
        out<<"选修"<<'\n';
}
