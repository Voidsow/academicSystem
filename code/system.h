#ifndef SYSTEM_H
#define SYSTEM_H

#include<string>
#include<fstream>
#include<sstream>
#include<QDebug>
#include<QString>
#include<QDir>
#include<QTextStream>
#include<dir.h>
#include"student.h"
#include"teacher.h"
#include"course.h"
#include"myvector.h"

using std::ifstream;

class system
{
public:
    MyVector<teacher> teacherArray;
    MyVector<course> crsArray;
    MyVector<student> stuArray;

	void read();
    void write();
    course* searchCourse(const string& crs);
    student* searchStu(const string& stu);
    teacher* searchTcher(const string& tcher);

    void deleteStu(const string& stu);
    void deleteTcher(const string& tcher);
    void deleteCrs(const string& crs);
    teacher * hasCrs(const string &courseName);
    double creditGetted(const string &stu);
};

#endif //SYSTEM_H
