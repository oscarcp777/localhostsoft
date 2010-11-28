#include <QtGui>
#include <QApplication>
#include "dialog.h"
#include <iostream>
int main(int argc, char *argv[])
{
	std::cout<<"hola mundo "<<std::endl;
    QApplication a(argc, argv);
    Dialog dialog;
    return dialog.exec();
}
