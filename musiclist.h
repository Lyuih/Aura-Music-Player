#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QVector>
#include <QList>
#include <QUrl>
#include <QMimeDatabase>
#include "music.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSet>
typedef QVector<music>::iterator iterator;
class musicList
{
public:
    void addMusicByMusicUrl(const QList<QUrl>&musicUrls);
    iterator findMusicByMusicId(const QString&musicId);
    iterator begin();
    iterator end();
    void writeToDB();//将所有歌曲更新到数据库
    void readFromDB();//从数据库读取数据
    musicList();
private:
    QVector<music> music_list;
    QSet<QString> musicPaths;
};

#endif // MUSICLIST_H
