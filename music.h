#ifndef MUSIC_H
#define MUSIC_H
#include <QUrl>
#include <QString>
#include <QUuid>
#include <QMediaPlayer>
#include <QDebug>
#include <QCoreApplication>
#include <QSqlQuery>
#include <QSqlError>
class music
{
public:
    music();
    music(const QUrl url);
    void setMusicId(const QString& musicId);
    void setMusicName(const QString& musicName);
    void setMusicSinger(const QString& musicSinger);
    void setMusicAlbum(const QString& musicAlbumn);
    void setMusicDuration(qint64 duration);
    void setIsLike(bool isLike);
    void setIsHistory(bool isHistory);
    void setMusicUrl(QUrl musicUrl);

    QString getMusicName()const;
    QString getMusicSinger()const;
    QString getMusicAlbum()const;
    qint64 getMusicDuration()const;
    bool getIsLike()const;
    bool getIsHistory()const;
    QUrl getMusicUrl()const;
    QString getMusicId()const;

    //解析歌曲信息
    void parseMediaMetaData();

    //将信息添加到数据库中
    void insetMusicToDB();


private:
    QString musicId;//确保歌曲的唯一性
    QString musicName;//歌曲名
    QString musicSinger;//歌手名
    QString musicAlbumn;//所属专辑
    qint64 duration;//时长 按毫秒计算
    bool isLike;//是否喜欢
    bool isHistory;//是否为历史播放
    QUrl musicUrl;//音乐QUrl
};

#endif // MUSIC_H
