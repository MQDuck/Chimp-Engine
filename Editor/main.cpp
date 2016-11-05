#include "ChimpEditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChimpEditor w;
    w.show();
    
    return a.exec();
}
