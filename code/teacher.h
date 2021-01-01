#ifndef TEACHER_H
#define TEACHER_H

#include"course.h"
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include<map>

using std::string;
using std::vector;
using std::istringstream;
using std::map;

class teacher
{
public:
	string name;
	string id;
    vector<course*> teaching;

	teacher();
	teacher(const teacher& tcher);
	teacher(const string& _name, const string& _id);
    void addCourse( course* crs);
    void deleteCourse(course* crs);
    void deleteCourse(const int &index);
    void change(const string & _id,const string & _name);
    void write(std::ofstream &out);
};


#endif // !TEACHER_H
