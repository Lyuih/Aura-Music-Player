#include "btform.h"
#include "ui_btform.h"

btForm::btForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::btForm)
{
    ui->setupUi(this);
}

btForm::~btForm()
{
    delete ui;
}

void btForm::setBticon(const QString &icon, const QString &title, const int id)
{
    ui->Bt_icon->setPixmap(QPixmap(icon));
    ui->Bt_text->setText(title);
    this->id_ = id;
}

void btForm::clearBg()
{

    ui->Bt_style->setStyleSheet("#Bt_style:hover{background:rgb(40, 40, 40);}");

}

int btForm::get_id()
{
    return id_;
}

void btForm::mousePressEvent(QMouseEvent *event)
{
    (void)event;//不用使用该变量
    ui->Bt_style->setStyleSheet("#Bt_style{background:rgb(40,40,40);}");
//                                 #Bt_style:hover{background:rgb(40, 40, 40);}");
    //发送鼠标点击信号
    emit clicked(this->id_);//清除其他按键的样式
}
