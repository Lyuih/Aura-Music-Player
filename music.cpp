#include "music.h"

music::music()
    :isLike(false)
    ,isHistory(false)
{

}

music::music(const QUrl url)
    :isLike(false)
    ,isHistory(false)
    ,musicUrl(url)
{
    musicId = QUuid::createUuid().toString();//生成唯一标识码
    parseMediaMetaData();//解析
}

void music::setMusicId(const QString &musicId)
{
    this->musicId = musicId;
}

void music::setMusicName(const QString &musicName)
{
     this->musicName = musicName;
}

void music::setMusicSinger(const QString &musicSinger)
{
     this->musicSinger = musicSinger;
}

void music::setMusicAlbum(const QString &musicAlbumn)
{
     this->musicAlbumn = musicAlbumn;
}

void music::setMusicDuration(qint64 duration)
{
     this->duration = duration;
}

void music::setIsLike(bool isLike)
{
     this->isLike = isLike;
}

void music::setIsHistory(bool isHistory)
{
     this->isHistory = isHistory;
}

void music::setMusicUrl(QUrl musicUrl)
{
     this->musicUrl = musicUrl;
}

QString music::getMusicName() const
{
    return  musicName;
}

QString music::getMusicSinger() const
{
    return musicSinger;
}

QString music::getMusicAlbum() const
{
    return musicAlbumn;
}

qint64 music::getMusicDuration() const
{
    return duration;
}

bool music::getIsLike() const
{
    return isLike;
}

bool music::getIsHistory() const
{
    return isHistory;
}

QUrl music::getMusicUrl() const
{
    return musicUrl;
}

QString music::getMusicId() const
{
    return musicId;
}

void music::parseMediaMetaData()
{
       QMediaPlayer player;

       player.setMedia(musicUrl);//提供了一个Url的单参构造
       //媒体元数据解析需要时间，只有等待解析完成之后，才能提取音乐消息，此处循环等待
       while(!player.isMetaDataAvailable())
       {
           QCoreApplication::processEvents();//防止主界面消息循环导致其他事件无法被处理
       }

       if(player.isMetaDataAvailable())
       {
           musicName = player.metaData("Title").toString();
           musicSinger = player.metaData("Author").toString();
           musicAlbumn = player.metaData("AlbumTitle").toString();
           duration = player.duration();

           //为了防止可能有的歌曲并没有这些消息，我们还需要自己处理一下
           QString fileName = musicUrl.fileName();
           int index = fileName.indexOf('-');//Qt中使用indexOf寻找
           //一般歌曲的命名格式为：xxx - yyy.zzz  前面是歌曲名，后面为歌曲作者 最后为格式名
           //当然也有没有作者的 xxx.zzz
           //一般不会没有歌曲名，下载歌曲都是有目的，没有名字你都不知道这是什么歌
           if(musicName.isEmpty())
           {
               if(index != -1)
               {
                   //xxx - yyy.zzz
                   musicName = fileName.mid(index+1,fileName.indexOf('.')-index-1).trimmed();
                   //Qt中的substr trimmed的作用为去除前导和后导空格
               }
               else
               {
                   //xxx.zzz
                   musicName = fileName.mid(0,fileName.indexOf('.')).trimmed();
               }
           }

           if(musicSinger.isEmpty())
           {
               if(index!=-1)
               {
                   musicSinger = fileName.mid(0,index).trimmed();
               }
               else
               {
                   musicSinger = "未知歌手";
               }
           }
           if(musicAlbumn.isEmpty())
           {
               musicAlbumn = "未知专辑";
           }
           qDebug()<<fileName<<musicSinger<<":"<<musicAlbumn<<":"<<duration;
       }
}

void music::insetMusicToDB()
{
    //检测music是否已经在数据库了
    QSqlQuery query;

    query.prepare("SELECT EXISTS (SELECT 1 FROM MusicInfo WHERE musicId = ?)");
    query.addBindValue(musicId);
    if(!query.exec())
    {
        qDebug()<<"查询失败："<<query.lastError().text();
        return;
    }
    if(query.next())
    {
        bool isExists = query.value(0).toBool();
        if(isExists)
        {
            //music已经存在
            //对属性进行更新
            query.prepare("UPDATE MusicInfo SET isLike = ?,isHistory = ? WHERE musicID = ?");
            query.addBindValue(isLike?1:0);
            query.addBindValue(isHistory?1:0);
            query.addBindValue(musicId);
            if(!query.exec())
            {
                qDebug()<<"更新失败："<<query.lastError().text();
            }
            qDebug()<<"更新music信息"<<musicName<<" "<<musicId;
        }
        else
        {
            //不存在添加
            query.prepare("INSERT INTO MusicInfo(musicId, musicName, musicSinger, albumName, musicUrl,\
                          duration, isLike, isHistory)\
                    VALUES(?,?,?,?,?,?,?,?)");
                    query.addBindValue(musicId);
            query.addBindValue(musicName);
            query.addBindValue(musicSinger);
            query.addBindValue(musicAlbumn);
            query.addBindValue(musicUrl.toLocalFile());
            query.addBindValue(duration);
            query.addBindValue(isLike ? 1 : 0);
            query.addBindValue(isHistory? 1 : 0);

            if(!query.exec())
            {
                qDebug()<<"插入失败: "<<query.lastError().text();
                return;
            }

            qDebug()<<"插入music信息: "<<musicName<<" "<<musicId;
        }
    }
}
