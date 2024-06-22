#include <QApplication>
#include <guicreator.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    guiCreator v;

    v.show();
    v.showFullScreen();

    return a.exec();
}
