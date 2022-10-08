#include "activation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Activation w;
    w.show();
    w.autosystem();
    return a.exec();
}
