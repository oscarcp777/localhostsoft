#include <QtGui>
#include <QApplication>
#include "dialog.h"
#include <iostream>
int main(int argc, char *argv[])
{
	 //-lspopc -lssl -lcrypto -lrt
    QApplication app(argc, argv);
    Dialog dialog;
    dialog.show();
    return app.exec();
}
