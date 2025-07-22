#ifndef BTFORM_H
#define BTFORM_H
/*
btform
为了区别左侧栏按钮的图标和文字，需要让btForm类具有这两个属性 可以直接设置，这两属性可以去掉
同时为了让按钮在点击后，切换右侧的page，还需要类似下标的属性，这里用id，同时id也可以标识左侧的按钮
*/
#include <QMouseEvent>
#include <QWidget>
#include <QString>
#include <QDebug>

namespace Ui {
class btForm;
}

class btForm : public QWidget
{
    Q_OBJECT

public:
    explicit btForm(QWidget *parent = nullptr);
    ~btForm();

    void setBticon(const QString&icon,const QString& title,const int id);
    void clearBg();
    int get_id();
protected:
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent* event);
signals://定义一个点击信号
    void clicked(int id);

private:
    Ui::btForm *ui;
    int id_;

};

#endif // BTFORM_H
