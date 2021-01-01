#ifndef CRS_SCORE_H
#define CRS_SCORE_H
#include<string>

//名字_成绩复合体
class crs_score
{
public:
    std::string name;
    double score;
    crs_score(const std::string &name,const double &score);
};

#endif // CRS_SCORE_H
