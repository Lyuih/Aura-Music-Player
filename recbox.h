#ifndef RECBOX_H
#define RECBOX_H

#include <QWidget>
#include "recboxitem.h"


namespace Ui {
class recBox;
}

class recBox : public QWidget
{
    Q_OBJECT

public:
    explicit recBox(QWidget *parent = nullptr);
    ~recBox();

private:
    Ui::recBox *ui;
};

#endif // RECBOX_H
