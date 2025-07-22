#include "recboxitem.h"
#include "ui_recboxitem.h"

////当鼠标进入时
//void recBoxItem::enterEvent(QEvent *event)
//{

//    m_playButton->show();
//    QWidget::enterEvent(event);
//}

//void recBoxItem::leaveEvent(QEvent *event)
//{
//    m_playButton->hide();
//    QWidget::leaveEvent(event);
//}

//失败
//void recBoxItem::paintEvent(QPaintEvent *event)
//{
//    QWidget::paintEvent(event);
//    if(m_isHovered){
//        qDebug()<<"1";
//        QPainter painter(this);
//        //确定绘制范围
//        QRect imageRect = ui->Item_icon->geometry();
//        //设置为半透明黑色
//        painter.setBrush(QColor(40,40,40,100));
//        painter.setPen(Qt::NoPen);//取消边框

//        //绘制一个遮罩
//        painter.drawRoundedRect(imageRect,8,8);
//    }
//}

recBoxItem::recBoxItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recBoxItem)
{
    ui->setupUi(this);
//    m_playButton = new QPushButton();
//    m_playButton->setFixedSize(50,50);
//    m_playButton->setParent(ui->Item_icon);
//    m_playButton->move((ui->Item_icon->width()-m_playButton->width())/2,
//                       (ui->Item_icon->height()-m_playButton->height())/2);
//    m_playButton->hide();
}

recBoxItem::~recBoxItem()
{
    delete ui;
}
