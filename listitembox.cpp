#include "listitembox.h"
#include "ui_listitembox.h"

void listItemBox::enterEvent(QEvent *event)
{
    (void) event;
    setStyleSheet("background-color:rgb(40,40,40);border-radius: 10px; ");

}

void listItemBox::leaveEvent(QEvent *event)
{
    (void)event;
    setStyleSheet("");
}

void listItemBox::setMusicName(QString MusicName)
{
    ui->Music_name->setText(MusicName);
}

void listItemBox::setMusicSinger(QString MusicSinger)
{
    ui->Music_singer->setText(MusicSinger);
}

void listItemBox::setMusicAlbum(QString MusicAlbum)
{
    ui->Music_album->setText(MusicAlbum);
}

void listItemBox::setLikeMusic(bool like)
{

    isLike = like;
    if(isLike)
    {
//        ui->like_bt->setIcon(QIcon(":/images/like_2.png"));
        ui->like_bt->setStyleSheet("background-image:url(:/images/like_3.png);");
        qDebug()<<"like_2";

    }
    else
    {
//        ui->like_bt->setIcon(QIcon(":/images/like_1.png"));
         ui->like_bt->setStyleSheet("background-image:url(:/images/like_1.png);");
        qDebug()<<"like_1";
    }
}

listItemBox::listItemBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listItemBox),
    isLike(false)
{
    ui->setupUi(this);
}

listItemBox::~listItemBox()
{
    delete ui;
}

//void listItemBox::on_like_clicked()
//{
//    isLike = !isLike;
//    setLikeMusic(isLike);
//    qDebug()<<"点击";
//}

void listItemBox::on_like_bt_clicked()
{
    isLike = !isLike;
    setLikeMusic(isLike);
    emit setIsLike(isLike);
    qDebug()<<"点击";
}
