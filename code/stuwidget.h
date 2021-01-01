#ifndef STUWIDGET_H
#define STUWIDGET_H

#include <QWidget>

namespace Ui {
class stuWidget;
}

class stuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit stuWidget(QWidget *parent = nullptr);
    ~stuWidget();

private:
    Ui::stuWidget *ui;
};

#endif // STUWIDGET_H
