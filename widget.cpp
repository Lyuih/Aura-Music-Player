#include "widget.h"
#include "ui_widget.h"

//界面的移动
/*
为了实现界面的移动，需要计算相对位置和绝对位置。
当鼠标点击时，获取鼠标到界面窗口左上角的相对距离、以及鼠标到电脑屏幕左上角的距离
当鼠标移动时，鼠标到电脑左上角的距离是会发送改变的，为了保持鼠标到界面窗口左上角的距离是不会变，
移动窗口。
需要捕捉鼠标的点击事件和鼠标的移动事件，记录相对距离
*/
void Widget::mousePressEvent(QMouseEvent *event)
{
    //捕捉鼠标点击
    if(event->button() == Qt::LeftButton){
        isDrag = true;
        drag_position = event->globalPos() - frameGeometry().topLeft();//得到相对坐标
        return;
    }
    QWidget::mousePressEvent(event);//其他事件交给qt自己处理
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton&&isDrag){
        move(event->globalPos()-drag_position);//根据鼠标位置移动窗口位置
        event->accept();
        return;
    }
    QWidget::mouseMoveEvent(event);
}

void Widget::initUI()
{
    //取消边框可以让界面看起来更美观，有整体感。
    //缺点就是要重写界面的移动和最小化以及关闭窗口
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);//取消边框

    //添加阴影效果
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    setWindowIcon(QIcon(":images/yui.jpg"));
    //给窗口设置阴影效果
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0,0); //设置阴影偏移
    shadow_effect->setColor("#000000"); //设置黑子阴影
    shadow_effect->setBlurRadius(10); //设置阴影的模糊半径
    this->setGraphicsEffect(shadow_effect);

    //添加系统托盘
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/images/yui.jpg"));
    //创建托盘菜单
    QMenu* trayMenu = new QMenu(this);
    trayMenu->addAction("还原",this,&QWidget::showNormal);
    trayMenu->addSeparator();
    trayMenu->addAction("退出",this,&Widget::quitMusic);

    trayIcon->setContextMenu(trayMenu);
    //显示托盘
    trayIcon->show();

    //设置左侧栏的图标和文本
    ui->Find_music->setBticon(":/images/find.png","发现音乐",1);
    ui->Like_music->setBticon(":/images/like_3.png","我喜欢",2);
    ui->Local_music->setBticon(":/images/music.png","本地音乐",3);
    ui->Recent_music->setBticon(":/images/recent.png","历史播放",4);

//    ui->Like_page->setMusicListType(LIKE_PAGE);
    ui->Like_page->setCommonUI("我喜欢","收藏音乐数量:");
//    ui->Local_page->setMusicListType(LOCAL_PAGE);
    ui->Local_page->setCommonUI("本地音乐","下载音乐数量:");
//    ui->Recent_page->setMusicListType(HISTORY_PAGE);
    ui->Recent_page->setCommonUI("历史播放","最近播放音乐数量:");



}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initUI();

    //初始化播放器
    initPlayer();

    initSQLite();

    initMusicList();

    //关联所有信号和槽
    connectSignalAndSlot();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::connectSignalAndSlot()
{
    connect(ui->Find_music,&btForm::clicked,this,&Widget::onBtFormClick);
    connect(ui->Like_music,&btForm::clicked,this,&Widget::onBtFormClick);
    connect(ui->Local_music,&btForm::clicked,this,&Widget::onBtFormClick);
    connect(ui->Recent_music,&btForm::clicked,this,&Widget::onBtFormClick);


    connect(ui->Like_page,&commonPage::updateLikeMusic,this,&Widget::onUpdateLikeMusic);
    connect(ui->Local_page,&commonPage::updateLikeMusic,this,&Widget::onUpdateLikeMusic);
    connect(ui->Recent_page,&commonPage::updateLikeMusic,this,&Widget::onUpdateLikeMusic);

    connect(ui->Like_page,&commonPage::playMusicByIndex,this,&Widget::playMusicByIndex);
    connect(ui->Local_page,&commonPage::playMusicByIndex,this,&Widget::playMusicByIndex);
    connect(ui->Recent_page,&commonPage::playMusicByIndex,this,&Widget::playMusicByIndex);

    // 设置静⾳
    connect(ui->Play_3, &volumeTool::setSilence, this,
    &Widget::setMusicSilence);
}

void Widget::onPlayStateChanged()
{
    qDebug()<<"播放状态改变";
    if(player->state() == QMediaPlayer::PlayingState){
        ui->Play->setStyleSheet("background-image:url(:/images/pause_30.png);");
    }else{

        ui->Play->setStyleSheet("background-image:url(:/images/play.png);");
    }
}

void Widget::initPlayer()
{
    //创建音乐播放器
       player = new QMediaPlayer(this);
       //创建播放列表
       playList = new QMediaPlaylist(this);

       //设置播放模式，默认为顺序播放
       playList->setPlaybackMode(QMediaPlaylist::Loop);

       //将播放列表设置给播放器
       player->setPlaylist(playList);
       //设置默认音量为20
       player->setVolume(20);
       connect(player, &QMediaPlayer::stateChanged, this,&Widget::onPlayStateChanged);
       connect(playList, &QMediaPlaylist::playbackModeChanged, this,
       &Widget::onPlaybackModeChanged);

       // 播放列表项发⽣改变，此时将播放⾳乐收藏到历史记录中
       connect(playList, &QMediaPlaylist::currentIndexChanged, this,
       &Widget::onCurrentIndexChanged);

       connect(ui->Play_3,&volumeTool::setMusicVolume,this,&Widget::setMusicVolume);

       // 媒体持续时⻓更新，即：⾳乐切换，时⻓更新，界⾯上时间也要更新
       connect(player, &QMediaPlayer::durationChanged, this,
       &Widget::onDurationChanged);

       connect(player, &QMediaPlayer::positionChanged, this,
       &Widget::positionChanged);

       connect(ui->Slider_bar,&musicSlider::setMusicSilderPosition,this,&Widget::onMusicSliderChanged);

       connect(player,&QMediaPlayer::metaDataAvailableChanged,this,&Widget::onMetaDataAvailableChanged);
//       connect(player,&QMediaPlayer::stateChanged,this,&Widget::onPlayStateChanged);
//       connect(playList,&QMediaPlaylist::playbackModeChanged,this,&Widget::onPlaybackModeChanged);
//       //播放列表发射改变，奖播放音乐收藏到历史记录
//       connect(playList,&QMediaPlaylist::currentIndexChanged,this,&Widget::onCurrentIndexChanged);

//       connect(volumeTool,&VolumeTool::setMusicVolume,this,&Widget::setMusicVolume);

//       connect(player,&QMediaPlayer::durationChanged,this,&Widget::onDurationChanged);

//       connect(player,&QMediaPlayer::positionChanged,this,&Widget::onPositionChanged);

       //       connect(player,&QMediaPlayer::metaDataAvailableChanged,this,&Widget::onMetaDataAvailableChanged);
}

void Widget::onPlaybackModeChanged(QMediaPlaylist::PlaybackMode playbackMode)
{
    if(QMediaPlaylist::Loop == playbackMode)
    {
        qDebug()<<"顺序播放";
//        ui->Play_mode->setIcon(QIcon(":/images/list_play.png"));
        ui->Play_mode->setStyleSheet("background-image:url(:/images/order.png)");
    }
    else if(QMediaPlaylist::Random == playbackMode)
    {
        qDebug()<<"循环播放";
//        ui->Play_mode->setIcon(QIcon(":/images/shuffle_2.png"));
        ui->Play_mode->setStyleSheet("background-image:url(:/images/order_3.png)");
    }
    else if(QMediaPlaylist::CurrentItemInLoop == playbackMode)
    {
        qDebug()<<"单曲循环播放";
//        ui->Play_mode->setIcon(QIcon(":/images/single_play.png"));
        ui->Play_mode->setStyleSheet("background-image:url(:/images/order_2.png)");
    }
    else
    {
        qDebug()<<"不支持~";
    }

}

void Widget::playAllMusicOfCommonPage(commonPage *page, int index)
{
    currentPage = page;
//    updateBtformAnima();
    //清空之前playlist的歌曲
    playList->clear();
    //添加当前要播放的page页面的所有歌曲
    currentPage->addMusicToPlayer(music_list,playList);
    playList->setCurrentIndex(index);
    player->play();
}

void Widget::initSQLite()
{
    //创建数据库连接
    sqlite = QSqlDatabase::addDatabase("QSQLITE");

    //设置数据库名称
    sqlite.setDatabaseName("YuiMusic.db");
    if(!sqlite.open()){
        QMessageBox::critical(this,"YuiMusic","数据库打开失败！");
        //打印详细错误
        qDebug() << "Database Error:" << sqlite.lastError().text();

        return;
    }
    qDebug()<<"SQLite连接成功";

    QString sql = "CREATE TABLE IF NOT EXISTS MusicInfo(\
                              id INTEGER PRIMARY KEY AUTOINCREMENT,\
                              musicId varchar(50) UNIQUE,\
                              musicName varchar(50),\
                              musicSinger varchar(50), \
                              albumName varchar(50),\
                              musicUrl varchar(256),\
                              duration BIGINT,\
                              isLike INTEGER,\
                              isHistory INTEGER)";
        QSqlQuery query;
        if(!query.exec(sql))
        {
            QMessageBox::critical(this,"Music","初始化失败！！");
            return;
        }

        qDebug()<<"Music表创建成功！";
}

void Widget::initMusicList()
{
    //从数据库读取歌曲信息
    music_list.readFromDB();
    //更新commonPage页面
    ui->Like_page->setMusicListType(PageType::LIKE_PAGE);
    ui->Like_page->reFresh(music_list);

    ui->Local_page->setMusicListType(PageType::LOCAL_PAGE);
    ui->Local_page->reFresh(music_list);

    ui->Recent_page->setMusicListType(PageType::HISTORY_PAGE);
    ui->Recent_page->reFresh(music_list);
}




void Widget::on_Quit_clicked()
{

    this->hide();
}

void Widget::onBtFormClick(const int id)
{
    //获取当前页面所有btForm按钮类型的对象
    QList<btForm*> buttonList = this->findChildren<btForm*>();
    //遍历当前所有对象，如果不是当前id的按钮，清除样式
    foreach(btForm* item,buttonList){
//        item->/
        if(item->get_id() != id){
            item->clearBg();
        }
    }
    ui->stackedWidget->setCurrentIndex(id-1);

    isDrag = false;
}

void Widget::on_music_add_clicked()
{
    //添加音乐的槽函数
       QFileDialog fileDialog(this);//绑定当前窗口
       //设置当前窗口标题
       fileDialog.setWindowTitle("添加本地下载音乐");

       //设置文件对话框默认的打开路径
       QDir dir(QDir::currentPath()); //设置当前路径
       dir.cdUp();//返回上级路径
       QString projectPath = dir.path();//获取路径
       projectPath+="/Aura_music_player/musics";

       fileDialog.setDirectory(projectPath);//打开窗口的路径

       //一次性选中多个
       fileDialog.setFileMode(QFileDialog::ExistingFiles);

       //利用MIME来过滤，不过此处没有限制，真正的限制在MusicList内部
       QStringList mimeTypeFilters;
       mimeTypeFilters<<"application/octet-stream";
       fileDialog.setMimeTypeFilters(mimeTypeFilters);

       if(QDialog::Accepted == fileDialog.exec())
       {
           //获取选中的文件
           QList<QUrl> fileUrls = fileDialog.selectedUrls();
           music_list.addMusicByMusicUrl(fileUrls);
           //onBtFromClicked(4);
           ui->stackedWidget->setCurrentIndex(2);//因为添加到本地音乐
           ui->Local_page->reFresh(music_list);//刷新本地音乐列表

           //将localpage中的歌曲添加到媒体播放列表中

           ui->Local_page->addMusicToPlayer(music_list,playList);
//           ui->Local_page->add
       }

}

void Widget::onUpdateLikeMusic(bool isLike, QString musicId)
{
    auto it = music_list.findMusicByMusicId(musicId);
    if(it!=music_list.end())
    {
        it->setIsLike(isLike);
    }

    ui->Like_page->reFresh(music_list);
    ui->Local_page->reFresh(music_list);
    ui->Recent_page->reFresh(music_list);
}

void Widget::on_Play_clicked()
{
    qDebug()<<"Play被点击";
    if(player->state() == QMediaPlayer::PlayingState){
        player->pause();
    }else if(player->state() == QMediaPlayer::PausedState){
        player->play();
    }else if(player->state() == QMediaPlayer::StoppedState){
        player->play();
    }
}

void Widget::on_Play_prev_clicked()
{
    qDebug()<<"切换上一曲";
    playList->previous();
}

void Widget::on_Play_next_clicked()
{
    qDebug()<<"切换下一曲";
    playList->next();
}








void Widget::on_Play_mode_clicked()
{
    qDebug()<<"改变模式";
    //顺序->循环->单曲->循环
    if(QMediaPlaylist::Loop == playList->playbackMode())
    {
        ui->Play_mode->setToolTip("随机播放");
        playList->setPlaybackMode(QMediaPlaylist::Random);
    }
    else if(QMediaPlaylist::Random == playList->playbackMode())
    {
        ui->Play_mode->setToolTip("单曲循环");
        playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }
    else if(QMediaPlaylist::CurrentItemInLoop == playList->playbackMode())
    {
        ui->Play_mode->setToolTip("顺序播放");
        playList->setPlaybackMode(QMediaPlaylist::Loop);
    }
    else
    {
        qDebug()<<"不支持~";
    }
}

void Widget::playMusicByIndex(commonPage *page, int index)
{
    qDebug()<<"准备播放音乐";
    playAllMusicOfCommonPage(page,index);
}

void Widget::onCurrentIndexChanged(int index)
{
    currentIndex = index;
    const QString& musicId = currentPage->getMusicIdByIndex(index);
    auto it = music_list.findMusicByMusicId(musicId);
    if(it != music_list.end())
    {
        it->setIsHistory(true);
    }
    ui->Recent_page->reFresh(music_list);
}

void Widget::setMusicSilence(bool isMuted)
{
    player->setMuted(isMuted);
}

void Widget::setMusicVolume(int volume)
{
    player->setVolume(volume);
}

void Widget::onDurationChanged(qint64 duration)
{
    ui->Slider_bar->setTotleDuration(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));
//    ui->Slider_bar->setTotleDuration;
    totalDuration = duration;
}

void Widget::positionChanged(qint64 duration)
{
    ui->Slider_bar->setCurDuration(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));
    ui->Slider_bar->setStep(duration/(float)totalDuration);
}

void Widget::onMusicSliderChanged(float value)
{
    qint64 duration = (qint64)(totalDuration*value);
    ui->Slider_bar->setCurDuration(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));

    player->setPosition(duration);

}

void Widget::onMetaDataAvailableChanged(bool available)
{
    if(available)
       {
           QString musicId = currentPage->getMusicIdByIndex(currentIndex);
           auto it = music_list.findMusicByMusicId(musicId);
           QString musicName = "未知歌曲";
           QString musicSinger = "未知歌手";
           if(it != music_list.end())
           {
               musicName = it->getMusicName();
               musicSinger = it->getMusicSinger();
           }
           //将数据设置到下方
           ui->Music_name->setText(musicName);
           ui->Music_singer->setText(musicSinger);

           //获取音乐封面
           QVariant coverimage = player->metaData("ThumbnailImage");
           if(coverimage.isValid())
           {
               QImage image = coverimage.value<QImage>();
               ui->Music_cover->setPixmap(QPixmap::fromImage(image));
//               currentPage->setMusicImage(QPixmap::fromImage(image));
           }
           else
           {
               qDebug()<<"歌曲没有封面图";
               QString path = ":/images/rec/001.png";
               ui->Music_cover->setPixmap(path);
//               currentPage->setMusicImage(path);
           }
           ui->Music_cover->setScaledContents(true);
       }
       else
       {
           qDebug()<<"数据不可用";
           ui->Music_name->setText("未知歌曲");
           ui->Music_singer->setText("未知歌手");
       }
}

void Widget::on_Min_clicked()
{
    showMinimized();//最小化
}

void Widget::on_Skin_clicked()
{
    QMessageBox::information(this,"温馨提示","这里什么也没有哦~");
}

void Widget::quitMusic()
{
    music_list.writeToDB();//更新数据库
    sqlite.close();//关闭数据库
    this->close();
}
