#include "volumetool.h"
#include "ui_volumetool.h"

volumeTool::volumeTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::volumeTool),
    isMuted(false),
    volumeRatio(20)
{
    ui->setupUi(this);
    ui->Slider_box->installEventFilter(this);
    ui->Out_line->setGeometry(ui->In_line->x(),ui->In_line->y(),
                              ui->In_line->width()*0.2,ui->Out_line->height());

    connect(ui->Volume, &QPushButton::clicked, this,
    &volumeTool::onSilenceBtnClicked);
}

volumeTool::~volumeTool()
{
    delete ui;
}

bool volumeTool::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->Slider_box)
        {
            if(event->type() == QEvent::MouseButtonPress)
            {
                qDebug()<<"按下";
                //如果是鼠标按下事件，修改sliderBtn和outLine的位置，并计算volumeRation
                setVolume();
                //emit setMusicVolume(volumeRatio);
            }
            else if(event->type() == QEvent::MouseButtonRelease)
            {
                qDebug()<<"抬起";
                //鼠标抬起，直接释放
                emit setMusicVolume(volumeRatio);
            }
            else if(event->type() == QEvent::MouseMove)
            {
                //鼠标移动事件
                setVolume();
                emit setMusicVolume(volumeRatio);
            }
            return true;
        }
        return QObject::eventFilter(object, event);
}

void volumeTool::setVolume()
{
    int width = ui->Slider_box->mapFromGlobal(QCursor().pos()).x();//获取鼠标在Slider_box的相对坐标

        //将height限定在合法范围
        width = width<0?0:width;
        width = width>180?180:width;



        //重新计算outline的长度,x,y坐标不用改变
        ui->Out_line->setGeometry(ui->In_line->x(),ui->In_line->y(),
                                    width,ui->Out_line->height());

        //重新计算sliderBtn位置
//        ui->Slider_box->move(ui->Slider_box->x(),ui->Slider_box->y());

        //计算音量
        volumeRatio = (int)(width/(float)180*100);

        //更新下方的音量显示
//        ui->volumeRatio->setText(QString::number(volumeRatio)+"%");
}

void volumeTool::onSilenceBtnClicked()
{
    isMuted = !isMuted;
    if(isMuted){
        ui->Volume->setStyleSheet("background-image:url(:/images/volume_off.png);");
    }else{
        ui->Volume->setStyleSheet("background-image:url(:/images/volume_on.png);");
    }

    emit setSilence(isMuted);
}
