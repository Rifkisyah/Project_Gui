#include "welcome_user.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Welcome_User w;
    w.show();
    return a.exec();
}
