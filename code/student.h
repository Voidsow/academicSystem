#ifndef STUDENT_H
#define STUDENT_H

#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include"crs_score.h"

#define CREDIT 50

using std::string;
using std::vector;

class student
{
public:
	string name;
	string id;
	string className;
	string major;
    vector<crs_score> taking;

    student();
	student(const student& other);
	student(const string &Name,const string &ID, const string &classname, const string &major);
    student(const string& line);
    void addCourse(const string& crsName, const double& _score);
	void cancelCourse(const string &coursName);
    void cancelCourse(const int &index);
    double& getScore(const string &crs);
    bool isTaking(const string &crs);
    void change(const string & _id,const string & _name,const string & _classname,const string & major);
    bool isInRange(const string &courseName,const double &min, const double &max);
    void write(std::ofstream &out);
    void writeScore(std::ofstream &out);
};

#endif //STUDENT_H

