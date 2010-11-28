#ifndef TPDATOSFINAL_H
#define TPDATOSFINAL_H

#include <QtGui/QWidget>
#include "ui_tpdatosfinal.h"

class TPDatosFinal : public QWidget
{
    Q_OBJECT

public:
    TPDatosFinal(QWidget *parent = 0);
    ~TPDatosFinal();

private:
    Ui::TPDatosFinalClass ui;
};

#endif // TPDATOSFINAL_H
