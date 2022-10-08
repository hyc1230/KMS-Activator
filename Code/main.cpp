#include "activation.h"

#include <QApplication>

#include <string>

std::string path;

int main(int argc, char *argv[])
{
    std::string s = argv[0];
    path = s.erase(s.find("\\") + 1);
    QApplication a(argc, argv);
    Activation w;
    w.show();
    w.autosystem();
    return a.exec();
}
