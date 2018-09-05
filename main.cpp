#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w[2];
    w[0].show();
    //w[1].show();

    return a.exec();
}
