#ifndef MUSICSLIDER_H
#define MUSICSLIDER_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class musicSlider;
}

class musicSlider : public QWidget
{
    Q_OBJECT

public:
    explicit musicSlider(QWidget *parent = nullptr);
    ~musicSlider();
    void setTotleDuration(const QString& time);
    void setCurDuration(const QString& time);
    void setStep(float f);
    void moveSlider();

    //重写鼠标按下，松开，按下移动的函数
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
signals:
    void setMusicSilderPosition(float);

private:
    Ui::musicSlider *ui;
    int currentPos;
};

#endif // MUSICSLIDER_H
