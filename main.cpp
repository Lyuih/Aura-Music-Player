#include "widget.h"

#include <QApplication>
#include <QMessageBox>
#include <QSharedMemory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //创建共享内存
    QSharedMemory shareMem("Music");

    //如果共享内存已经被占用，说明已经有实例在运行
    if(shareMem.attach())
    {
        QMessageBox::information(nullptr,"Music","Music已经在运行~");
        return 0;
    }
    shareMem.create(1);
    Widget w;
    w.show();
    return a.exec();
}
