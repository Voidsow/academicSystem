#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include<QStringList>

namespace Ui {
class Input;
}

class Input : public QDialog
{
    Q_OBJECT

public:
    enum Type{Student,Teacher,Course,ScoreRange};
    explicit Input(int mode,QWidget *parent = nullptr);
    QStringList returns(int mode);
    ~Input();

private:
    Ui::Input *ui;


};

#endif // INPUT_H
