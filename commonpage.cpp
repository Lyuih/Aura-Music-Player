#include "commonpage.h"
#include "ui_commonpage.h"

void commonPage::setCommonUI(const QString &title, const QString &message)
{
    ui->Title->setText(title);
    ui->Message->setText(message);

//    //测试
//    listItemBox* listItem = new listItemBox(this);
//    QListWidgetItem* listWidgetItem = new QListWidgetItem(ui->PageMusic_list);
//    listWidgetItem->setSizeHint(QSize(ui->PageMusic_list->width(),45));
//    ui->PageMusic_list->setItemWidget(listWidgetItem,listItem);


}

commonPage::commonPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::commonPage)
{
    ui->setupUi(this);
    connect(ui->PageMusic_list,&QListWidget::doubleClicked,this,[=](const QModelIndex& index){
        qDebug()<<"发射播放信号";
        emit playMusicByIndex(this,index.row());
    });
}

commonPage::~commonPage()
{
    delete ui;
}

void commonPage::setMusicListType(PageType pageType)
{
    this->pageType = pageType;
}

void commonPage::addMusicToMusicPage(musicList &musiclist)
{
    musicListOfPage.clear();
    for(auto&item:musiclist){
        switch (pageType) {
            case LIKE_PAGE:
                if(item.getIsLike()){
                    musicListOfPage.push_back(item.getMusicId());
                }
            break;
        case LOCAL_PAGE:
            musicListOfPage.push_back(item.getMusicId());
            break;
        case HISTORY_PAGE:
            if(item.getIsHistory()){
                musicListOfPage.push_back(item.getMusicId());
            }
            break;
        default:
            qDebug()<<"没有喵~";
            break;
        }
    }
}

void commonPage::addMusicToPlayer(musicList &musiclist, QMediaPlaylist *playList)
{
    for(auto music:musiclist)
        {
            switch(pageType)
            {
                case LOCAL_PAGE:
                    playList->addMedia(music.getMusicUrl());
                break;
                case LIKE_PAGE:
                    if(music.getIsLike())
                    {
                        playList->addMedia(music.getMusicUrl());
                    }
                break;
            case HISTORY_PAGE:
                    if(music.getIsHistory())
                    {
                        playList->addMedia(music.getMusicUrl());
                    }
                break;
            default:
                qDebug()<<"不支持喵~";
                break;
            }

        }
}

void commonPage::reFresh(musicList &musiclist)
{
    ui->PageMusic_list->clear();

    //从musicList中分离当前页面的所有音乐
    addMusicToMusicPage(musiclist);

    //遍历歌单，将歌单中的所有歌曲显示到界面
    for(auto musicId:musicListOfPage){
        auto it = musiclist.findMusicByMusicId(musicId);
        if(it == musiclist.end()){
            continue;
        }
        listItemBox* listitembox = new listItemBox();
        //设置列表音乐的歌曲名、歌手、专辑
        listitembox->setMusicName(it->getMusicName());
        listitembox->setMusicSinger(it->getMusicSinger());
        listitembox->setMusicAlbum(it->getMusicAlbum());
        listitembox->setLikeMusic(it->getIsLike());

        QListWidgetItem* item = new QListWidgetItem(ui->PageMusic_list);
        item->setSizeHint(QSize(listitembox->width(),listitembox->height()));
        ui->PageMusic_list->setItemWidget(item,listitembox);
        setMusicNum(musicListOfPage.size());
        //接受listItemBox发射的信号
//        connect(listitembox,&listItemBox::setIsLike,this,[=](bool isLike){
//           emit updateLikeMusic(isLike,it->getMusicId());
//        });
        // 捕获 musicId 而不是迭代器 it
        connect(listitembox, &listItemBox::setIsLike, this, [this, musicId, &musiclist](bool isLike){
            // 在槽函数内部重新查找，确保数据有效性
            auto current_it = musiclist.findMusicByMusicId(musicId);
            if (current_it != musiclist.end()) {
                current_it->setIsLike(isLike);
                // 这里可以直接发射信号，但最好还是先修改数据模型，再由模型通知刷新
                emit updateLikeMusic(isLike, musicId);
            }
        });
    }
    repaint();

}

const QString commonPage::getMusicIdByIndex(int index) const
{
    if(index>=musicListOfPage.size())
    {
        qDebug()<<"无此歌~";
        return "";
    }
    return musicListOfPage[index];
}

void commonPage::setMusicNum(int num)
{
    ui->Music_num->setText(QString::number(num));
}







