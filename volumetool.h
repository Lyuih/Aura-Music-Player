#ifndef VOLUMETOOL_H
#define VOLUMETOOL_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class volumeTool;
}

class volumeTool : public QWidget
{
    Q_OBJECT

public:
    explicit volumeTool(QWidget *parent = nullptr);
    ~volumeTool();
    bool eventFilter(QObject* object,QEvent* event);//事件过滤器
    void setVolume();
public slots:
    void onSilenceBtnClicked();//静音按钮槽函数

signals:
    void setSilence(bool);
    void setMusicVolume(int);

private:
    Ui::volumeTool *ui;
    bool isMuted;
    int volumeRatio;
};

#endif // VOLUMETOOL_H
