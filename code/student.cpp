#include "student.h"

student::student()
	:name(""),id(""),className(""),major("")
{
}

student::student(const student& other)
    : name(other.name), id(other.id), className(other.className), major(other.major),taking(other.taking)
{
    int d=0;
}

student::student(const string& Name, const string& ID, const string& classname, const string& _major)
	:name(Name), id(ID),className(classname),major(_major)
{
}

//文件读入时用
void student::addCourse(const string& crsName, const double& _score)
{
    taking.push_back(crs_score(crsName,_score));
}

void student::cancelCourse(const string &coursName)
{
    for(auto i=taking.begin();i!=taking.end();i++)
        if((*i).name==coursName)
        {
            taking.erase(i);
            break;
        }
}

void student::cancelCourse(const int &index)
{
    taking.erase(taking.begin()+index);
}

double & student::getScore(const std::string &crs)
{
    for(auto i=0;i<taking.size();i++)
        if(taking[i].name==crs)
            return (taking[i].score);
}

bool student::isTaking(const std::string &crs)
{
    for(auto i=taking.begin();i!=taking.end();i++)
        if((*i).name==crs)
            return true;
    return false;
}

void student::change(const std::string &_id, const std::string &_name, const std::string &_classname, const std::string &_major)
{
    name=_name;
    id=_id;
    className=_classname;
    major=_major;
}

bool student::isInRange(const std::string &courseName, const double &min, const double &max)
{
    for(auto i=0;i!=taking.size();i++)
    {
        if(taking[i].name==courseName)
        {
            if(taking[i].score>=min&&taking[i].score<=max)
                return true;
            else
                return false;
        }
    }
}

void student::write(std::ofstream &out)
{
    out<<id<<'\t'<<name<<'\t'<<className<<'\t'<<major<<'\n';
}

void student::writeScore(std::ofstream &out)
{
    for(auto i=0;i<taking.size();i++)
        out<<id<<'\t'<<name<<'\t'<<taking[i].name<<'\t'<<taking[i].score<<'\n';
}


student::student(const string& line)
{
	std::istringstream in(line);
    in >> id >> name >> className >> major;
    int d=0;
}
