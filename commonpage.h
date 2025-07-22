#ifndef COMMONPAGE_H
#define COMMONPAGE_H

#include <QWidget>
#include <QString>
#include "listitembox.h"
#include <QListWidgetItem>
#include "musiclist.h"
#include "music.h"
#include "listitembox.h"
#include <QMediaPlaylist>

namespace Ui {
class commonPage;
}

enum PageType{
    LIKE_PAGE, //我喜欢
    LOCAL_PAGE, //本地音乐
    HISTORY_PAGE //最近播放
};


class commonPage : public QWidget
{
    Q_OBJECT

public:
    void setCommonUI(const QString& title,const QString& message);
    explicit commonPage(QWidget *parent = nullptr);
    ~commonPage();
    void setMusicListType(PageType pageType);
    void addMusicToMusicPage(musicList& musiclist);
    void addMusicToPlayer(musicList&musiclist,QMediaPlaylist*playList);
    void reFresh(musicList&musiclist);
    const QString getMusicIdByIndex(int index)const;

    void setMusicNum(int num);
signals:
    void updateLikeMusic(bool isLike,QString musicId);
    //我们需要得知哪首歌被收藏了，然后将喜欢的歌刷新的我喜欢页面，发射信号让widget捕捉
    void playMusicByIndex(commonPage* page,int index);
private:
    Ui::commonPage *ui;
    //歌单列表
    QVector<QString> musicListOfPage;
    PageType pageType;
};

#endif // COMMONPAGE_H
