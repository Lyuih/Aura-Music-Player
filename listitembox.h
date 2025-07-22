#ifndef LISTITEMBOX_H
#define LISTITEMBOX_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class listItemBox;
}

class listItemBox : public QWidget
{
    Q_OBJECT

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

public:
    void setMusicName(QString MusicName);
    void setMusicSinger(QString MusicSinger);
    void setMusicAlbum(QString MusicAlbum);
    void setLikeMusic(bool Like);

    explicit listItemBox(QWidget *parent = nullptr);
    ~listItemBox();
signals:
    void setIsLike(bool);//发射信号通知commonpage更新数据信息
private slots:
//    void on_like_clicked();

    void on_like_bt_clicked();

private:
    Ui::listItemBox *ui;
    bool isLike;
};

#endif // LISTITEMBOX_H
