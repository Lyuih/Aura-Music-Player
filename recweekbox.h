#ifndef RECWEEKBOX_H
#define RECWEEKBOX_H

#include <QWidget>

namespace Ui {
class recWeekBox;
}

class recWeekBox : public QWidget
{
    Q_OBJECT

public:
    explicit recWeekBox(QWidget *parent = nullptr);
    ~recWeekBox();

private:
    Ui::recWeekBox *ui;
};

#endif // RECWEEKBOX_H
