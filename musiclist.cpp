#include "musiclist.h"

void musicList::addMusicByMusicUrl(const QList<QUrl> &musicUrls)
{
//    for(auto url:musicUrls)
//        {
//            //由于添加进来的文件不一定是歌曲文件，因此需要再次筛选出音乐文件
//            QMimeDatabase db;
//            QMimeType mime = db.mimeTypeForFile(url.toLocalFile());
//            //取到到了文件的mime类型
//            if(mime.name()=="audio/mpeg"||mime.name()=="audio/flac"||mime.name() == "audio/wav")
//            {
//                music music_item(url);
//                music_list.push_back(music_item);
//            }

//    }
    for(auto url:musicUrls)
       {
           QString musicPath = url.toLocalFile();
           if(musicPaths.contains(musicPath))
           {
               continue;//已经存在
           }
           musicPaths.insert(musicPath);

           //由于添加进来的文件不一定是歌曲文件，因此需要再次筛选出音乐文件
           QMimeDatabase db;
           QMimeType mime = db.mimeTypeForFile(url.toLocalFile());
           //取到到了文件的mime类型
           if(mime.name()=="audio/mpeg"||mime.name()=="audio/flac"||mime.name() == "audio/wav")
           {
               music music(url);
               music_list.push_back(music);
           }

       }
}

iterator musicList::findMusicByMusicId(const QString &musicId)
{
    for(auto it = music_list.begin();it!=music_list.end();++it){
        if(it->getMusicId() == musicId){
            return it;
        }
    }
    return end();
}

iterator musicList::begin()
{
    return music_list.begin();
}

iterator musicList::end()
{
    return music_list.end();
}

void musicList::writeToDB()
{
    for(auto music:music_list)
    {
        music.insetMusicToDB();
    }
}

void musicList::readFromDB()
{
    QSqlQuery query;
    query.prepare("SELECT musicId, musicName, musicSinger, albumName, musicUrl,\
                          duration, isLike, isHistory FROM MusicInfo");
    if(!query.exec())
    {
        qDebug()<<"数据库查询失败:"<<query.lastError().text();
        return;
    }

    while(query.next())
    {
        music music;
        music.setMusicId(query.value(0).toString());
        music.setMusicName(query.value(1).toString());
        music.setMusicSinger(query.value(2).toString());
        music.setMusicAlbum(query.value(3).toString());
        music.setMusicUrl(QUrl::fromLocalFile(query.value(4).toString()));
        music.setMusicDuration(query.value(5).toLongLong());
        music.setIsLike(query.value(6).toBool());
        music.setIsHistory(query.value(7).toBool());
        music_list.push_back(music);

        // 恢复musicPaths，目的防止相同目录下的歌曲被重复加载
        musicPaths.insert(music.getMusicUrl().toLocalFile());
    }
}

musicList::musicList()
{

}
