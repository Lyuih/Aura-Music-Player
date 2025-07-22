#include "musicslider.h"
#include "ui_musicslider.h"

musicSlider::musicSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::musicSlider),
    currentPos(0)
{
    ui->setupUi(this);
    moveSlider();
}

musicSlider::~musicSlider()
{
    delete ui;
}

void musicSlider::setTotleDuration(const QString& time)
{
    ui->End_time->setText(time);
}

void musicSlider::setCurDuration(const QString& time)
{
    ui->Cur_time->setText(time);
}

void musicSlider::setStep(float bf)
{
    currentPos = ui->In_line->width()*bf;
    moveSlider();
}

void musicSlider::moveSlider()
{
    ui->Out_line->setMaximumWidth(currentPos);
    ui->Out_line->setGeometry(QRect(ui->Out_line->geometry().x(),ui->Out_line->geometry().y(),currentPos,ui->Out_line->height()));
}


void musicSlider::mousePressEvent(QMouseEvent *event)
{
    currentPos = event->pos().x();
}

void musicSlider::mouseReleaseEvent(QMouseEvent *event)
{
    currentPos = event->pos().x()-55;
    moveSlider();
    emit setMusicSilderPosition(currentPos/(float)ui->In_line->width());
}

void musicSlider::mouseMoveEvent(QMouseEvent *event)
{
    //需要限制滑动的范围
        QRect rect = QRect(0,0,ui->Line_box->width(),ui->Line_box->height());
        QPoint pos = event->pos(); //鼠标的位置
//        pos.setX(pos.x()-55);
        if(!rect.contains(pos))
        {
            return;
        }

        if(event->buttons() == Qt::LeftButton)
        {
            currentPos = event->pos().x()-55;

            if(currentPos<0)
                currentPos = 0;
            else if(currentPos>ui->In_line->width())
                currentPos = ui->In_line->width();
            moveSlider();
        }
}
