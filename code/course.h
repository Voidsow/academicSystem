#ifndef COURSE_H
#define COURSE_H

#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include<cmath>
#include<qstring.h>
#include"student.h"

using std::string;
using std::vector;

class course
{
public:
	string id;
	string name;
	double credit;
	int hour;
	bool isObligatory;
    vector<student *> stuSet;

    course();
	course(const course& crs);
	course(string _id, string _name, double _credit, int _hour, bool _isOblig);
	course* getCourse();
    void addStu(student *stu);
    void deleteStu(student *stu);
    void deleteStu(const int &index);
	double getCredit();
	course(const string& line);
    void change(const string & _id,const string & _name,const double & _credit,const int & _hour, bool _isOblig);
    double getAverage();
    double getStandardDeviation();
    double getPassingRate();
    void sort(const int &lastIndex);
    int sortByRange(const double &min,const double &max);
    int searchByRange(const string &st,const int &lastIndex);
    bool operator==(const course &other);
    void write(std::ofstream &out);
};

#endif // COURSE_H
