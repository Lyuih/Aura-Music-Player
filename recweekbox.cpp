#include "recweekbox.h"
#include "ui_recweekbox.h"

recWeekBox::recWeekBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recWeekBox)
{
    ui->setupUi(this);
}

recWeekBox::~recWeekBox()
{
    delete ui;
}
