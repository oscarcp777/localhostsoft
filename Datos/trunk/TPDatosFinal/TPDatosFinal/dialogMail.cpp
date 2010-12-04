 /****************************************************************************
    **
    ** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
    **
    ** This file is part of the documentation of the Qt Toolkit.
    **
    ** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
    **
    ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
    ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
    **
    ****************************************************************************/

    #include <QtGui>

    #include "dialogMail.h"
	#include "src.datos.controller/Controller.h"

    DialogMail::DialogMail(QString emailUIDs)
    {

   // 	Controller* control = new Controller(lineEdits[0]->text().toStdString());
  //  	control->searchMails(emailUIDs.toStdString());

	this->setMinimumHeight(600);
	this->setMinimumWidth(600);
//        createMenu();
	QString mensaje;
	mensaje.append("Datos de los mails: ");
	mensaje.append(emailUIDs);

        bigEditor = new QTextEdit;
        bigEditor->setPlainText(mensaje);
	bigEditor->setReadOnly(true);

        okButton = new QPushButton(tr("OK"));
        
        connect(okButton, SIGNAL(clicked()), this, SLOT(reject()) );
        
        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addStretch(1);
        buttonLayout->addWidget(okButton);
		
        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(bigEditor);
        mainLayout->addLayout(buttonLayout);
        setLayout(mainLayout);

        setWindowTitle(tr("Mails"));
    }

    void DialogMail::createMenu()
    {
        menuBar = new QMenuBar;

        fileMenu = new QMenu(tr("&File"), this);
        exitAction = fileMenu->addAction(tr("E&xit"));
        menuBar->addMenu(fileMenu);

        connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
    }
    
    /**
    * M�todos para ejecutar con cada click
    */

    void DialogMail::okClick()
    {
    	printf("exit\n");
//    	exit;
    };
