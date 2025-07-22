#ifndef WIDGET_H
#define WIDGET_H
/*
yui的音乐播放器重写，此次的音乐播放器意为Aura，
会在原有的基础上进行升级，无论是界面还是功能都会有所升级。
*/
#include <QDebug>
#include <QWidget>
#include <QMouseEventTransition>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsDropShadowEffect>
#include <QRect>
#include <QCoreApplication>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <cstdlib>
#include <ctime>
#include <QFileDialog>
#include <QImage>
#include "btform.h"
#include "musiclist.h"
#include <commonpage.h>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSystemTrayIcon>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
protected:
    //重写鼠标点击和鼠标移动
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
public:
    void initUI();//初始化ui函数，后续随着控件的增加，这些控件也是要初始化的，写个单独的函数在初始化这是控件
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void connectSignalAndSlot();//存储信号和槽函数的地方
    void onPlayStateChanged();//捕捉音乐播放变化的信号
    void initPlayer();//初始化媒体对象
    void onPlaybackModeChanged(QMediaPlaylist::PlaybackMode playbackMode);//模式切换槽函数
    void playAllMusicOfCommonPage(commonPage*page,int index);
    void initSQLite();
    void initMusicList();
private slots:
    void on_Quit_clicked();
    void onBtFormClick(const int id);//新增点击槽函数

    void on_music_add_clicked();
    void onUpdateLikeMusic(bool isLike, QString musicId);

    void on_Play_clicked();

    void on_Play_prev_clicked();

    void on_Play_next_clicked();

    void on_Play_mode_clicked();

    //捕获commonPage发射的信号，播放音乐
    void playMusicByIndex(commonPage* page,int index);

    //捕获音乐切换的信息
    void onCurrentIndexChanged(int index);

    void setMusicSilence(bool isMuted);

    //捕捉音量改变的信号
    void setMusicVolume(int volume);

    // 歌曲持续时⻓改变时[歌曲切换]
    void onDurationChanged(qint64 duration);

    // position: 媒体持续播放时间
    void positionChanged(qint64 position);

    void onMusicSliderChanged(float value); // 进度条改变

    //捕捉歌曲改变的信息，然后更新下方信息
    void onMetaDataAvailableChanged(bool available);

    void on_Min_clicked();

    void on_Skin_clicked();
    void quitMusic();

private:
    QPoint drag_position;//计算鼠标相对与窗口标题栏的相对距离
    musicList music_list;
    QMediaPlayer* player;
    QMediaPlaylist* playList;

    commonPage* currentPage;//记录当前正在播放的commonpage页面
    int currentIndex;//记录正在播放的歌曲在媒体列表的索引

    qint64 totalDuration;
    QSqlDatabase sqlite;

    bool isDrag;//为true才能拖动
    Ui::Widget *ui;
};
#endif // WIDGET_H









