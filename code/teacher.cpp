#include "teacher.h"

teacher::teacher()
    :name(""),id("")
{
}

teacher::teacher(const string& _name, const string& _id)
	:name(_name),id(_id)
{
}

teacher::teacher(const teacher& tcher)
    :name(tcher.name),id(tcher.id),teaching(tcher.teaching)
{
}

void teacher::addCourse(course* crs)
{
    teaching.push_back(crs);
}

void teacher::deleteCourse(course *crs)
{
    for(auto i=teaching.begin();i!=teaching.end();i++)
    {
        if(*i!=nullptr)
            if(*i==crs)
            {
                *i=nullptr;
                break;
            }
    }
}

void teacher::deleteCourse(const int &index)
{
    teaching.erase(teaching.begin()+index);
}

void teacher::change(const std::string &_id, const std::string &_name)
{
    id=_id;
    name=_name;
}

void teacher::write(std::ofstream &out)
{
    out<<id<<'\t'<<name;
    for(auto i=0;i<teaching.size();i++)
        out<<'\t'<<teaching[i]->name;
    out<<'\n';
}
