#include "recbox.h"
#include "ui_recbox.h"

recBox::recBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recBox)
{
    ui->setupUi(this);
    recBoxItem* item = new recBoxItem();
    ui->Reclist_layout->addWidget(item);
}

recBox::~recBox()
{
    delete ui;
}
