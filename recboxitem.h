#ifndef RECBOXITEM_H
#define RECBOXITEM_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class recBoxItem;
}

class recBoxItem : public QWidget
{
    Q_OBJECT

protected:
    //实现一些类似于伪类的效果
//    void enterEvent(QEvent*event) override;
//    void leaveEvent(QEvent *event) override;
//    void paintEvent(QPaintEvent *event) override;

public:
    explicit recBoxItem(QWidget *parent = nullptr);
    ~recBoxItem();

private:
    Ui::recBoxItem *ui;
//    bool m_isHovered;
//    QPushButton* m_playButton;
};

#endif // RECBOXITEM_H
