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

    #include "dialog.h"


	std::string botonesBusqueda[CANT_BOTONES] = {"From", "To", "Date", "Reply-To", "Content"};
	using namespace std;
    Dialog::Dialog()
    {


    	createMenu();
        createLoginGroupBox();
        createOperationGroupBox();
        createClassificationGroupBox();
        createSelectionGroupBox();
        createSearchGroupBox();
        createDeleteGroupBox();

        bigEditor = new QTextEdit;
        bigEditor->setPlainText(tr("This widget takes up all the remaining space "
                                   "in the top-level layout."));
	bigEditor->setReadOnly(true);
        

        okButton = new QPushButton(tr("OK"));
        cancelButton = new QPushButton(tr("Cancel"));
        okButton->setDefault(true);

        connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()) );
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
        
        connect(buttons[0], SIGNAL(clicked()), this, SLOT(resguardarClick()));
        connect(buttons[1], SIGNAL(clicked()), this, SLOT(configurarClick()));
        connect(buttons[2], SIGNAL(clicked()), this, SLOT(buscarClick()));
	connect(buttons[3], SIGNAL(clicked()), this, SLOT(verClick()));
	connect(buttons[4], SIGNAL(clicked()), this, SLOT(borrarClick()));

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addStretch(1);
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
		
        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->setMenuBar(menuBar);
        mainLayout->addWidget(loginGroupBox);
        mainLayout->addWidget(operationGroupBox);
        mainLayout->addWidget(classificationGroupBox);
	mainLayout->addWidget(selectionGroupBox);
        mainLayout->addWidget(searchGroupBox);
	mainLayout->addWidget(deleteGroupBox);
        mainLayout->addWidget(bigEditor);
        mainLayout->addLayout(buttonLayout);
        setLayout(mainLayout);

        setWindowTitle(tr("Basic Layouts"));
    }

    void Dialog::createMenu()
    {
        menuBar = new QMenuBar;

        fileMenu = new QMenu(tr("&File"), this);
        exitAction = fileMenu->addAction(tr("E&xit"));
        menuBar->addMenu(fileMenu);

        connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
    }

    void Dialog::createOperationGroupBox()
    {
        operationGroupBox = new QGroupBox(tr("Comunicaci�n"));
        QHBoxLayout *layout = new QHBoxLayout;

		buttons[0] = new QPushButton(tr("Resguardar"));
		layout->addWidget(buttons[0]);
		buttons[1] = new QPushButton(tr("Configurar"));
		layout->addWidget(buttons[1]);

        operationGroupBox->setLayout(layout);
    }

    void Dialog::createLoginGroupBox()
    {
        loginGroupBox = new QGroupBox(tr("Acceso"));
        QHBoxLayout *layout = new QHBoxLayout;

        labels[0] = new QLabel(tr("Usuario:"));
        lineEdits[0] = new QLineEdit;
        layout->addWidget(labels[0]);
        layout->addWidget(lineEdits[0]);
        
        labels[1] = new QLabel(tr("Clave:"));
        lineEdits[1] = new QLineEdit;
        lineEdits[1]->setEchoMode( QLineEdit::Password );
        layout->addWidget(labels[1]);
        layout->addWidget(lineEdits[1]);

        loginGroupBox->setLayout(layout);
    }
    
    void Dialog::createSearchGroupBox()
    {
        searchGroupBox = new QGroupBox(tr("Buscar"));
        QHBoxLayout *layout = new QHBoxLayout;

		buttons[2] = new QPushButton(tr("Buscar"));
		layout->addWidget(buttons[2]);
        lineEdits[2] = new QLineEdit;
        layout->addWidget(lineEdits[2]);

        searchGroupBox->setLayout(layout);
    
    }

    void Dialog::createDeleteGroupBox()
    {
        deleteGroupBox = new QGroupBox(tr("Ver/Borrar (ingresar lista de UIDs separados por espacio)"));
        QHBoxLayout *layout = new QHBoxLayout;

	buttons[3] = new QPushButton(tr("Ver"));
	layout->addWidget(buttons[3]);
	buttons[4] = new QPushButton(tr("Borrar"));
	layout->addWidget(buttons[4]);
        lineEdits[3] = new QLineEdit;
        layout->addWidget(lineEdits[3]);

        deleteGroupBox->setLayout(layout);
    
    }

    void Dialog::createClassificationGroupBox()
    {
        classificationGroupBox = new QGroupBox(tr("Clasificaciones"));
        QHBoxLayout *layout = new QHBoxLayout;
        
        QSignalMapper *signalMapper = new QSignalMapper(this);
        

		QString mensaje;
        for (int i = 0; i < CANT_BOTONES; ++i) {
            buttons[i+10] = new QPushButton(tr(botonesBusqueda[i].c_str()));
            layout->addWidget(buttons[i+10]);
            mensaje.clear();
            mensaje.append("Clasificaci�n ");
            connect(buttons[i+10], SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(buttons[i+10], buttons[i+10]->text());
        }
        connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(clasificarClick(QString)));
        
        classificationGroupBox->setLayout(layout);
    }

    void Dialog::createSelectionGroupBox()
    {
	
        selectionGroupBox = new QGroupBox(tr("Selecciones"));
        QHBoxLayout *layout = new QHBoxLayout;
        
        QSignalMapper *signalMapper = new QSignalMapper(this);
        

		QString mensaje;
        for (int i = 0; i < CANT_BOTONES-1; ++i) {
            buttons[i+10] = new QPushButton(tr(botonesBusqueda[i].c_str()));
            layout->addWidget(buttons[i+10]);
            mensaje.clear();
            mensaje.append("Selecci�n ");
            connect(buttons[i+10], SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(buttons[i+10], buttons[i+10]->text());
        }
        connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(seleccionarClick(QString)));
        
        selectionGroupBox->setLayout(layout);
    }
    
    /**
    * M�todos para ejecutar con cada click
    */
    void Dialog::okClick()
    {
    	bigEditor->setText("ok");
    }

    void Dialog::cancelClick()
    {
    	printf("exit\n");
//    	exit;
    };
    void Dialog::buscarClick()
    {
    	QString textoBuscado;
    	textoBuscado.append("Busco el texto: ");
    	textoBuscado.append(lineEdits[2]->text());
    	
    	bigEditor->setText(textoBuscado);
    };
    void Dialog::borrarClick()
    {
    	QString listaUID;
    	listaUID.append("Mails a borrar (UIDs): ");
    	listaUID.append(lineEdits[3]->text());
    	
    	bigEditor->setText(listaUID);
    };
    void Dialog::verClick()
    {
    	Controller* control = new Controller(lineEdits[0]->text().toStdString());

//    	std::string strUser = "[Primario";
//		strUser += lineEdits[0]->text().toStdString();
//		strUser += "=";
//		std::string strSearch = lineEdits[3]->text().toStdString();
//    	strSearch += "]";
//
//    	cout<<strUser<<endl;
//    	cout<<strSearch<<endl;
//    	strUser+=strSearch;
//    	control->searchMails(strUser);
//
//    	control->getListOfMails();
//
//
//
//
//    	QString lineSearch((const char*)strUser.c_str());
    	string result = control->getMails(lineEdits[3]->text().toStdString());
    	QString resultQ ((const char*)result.c_str());
    	cout<<result <<endl;
    	DialogMail dialogMail(resultQ);
        dialogMail.exec();
        delete control;

    };
    void Dialog::resguardarClick()
    {
	QString mensajeUsuario;
    	mensajeUsuario.append("Descargando mails de: ");

    	Controller* control = new Controller(lineEdits[0]->text().toStdString());
    	control->addPass(lineEdits[1]->text().toStdString());
    	mensajeUsuario.append(lineEdits[0]->text());
    	bigEditor->setText(mensajeUsuario);
    	if (!control->createPrimaryIndex()){
    		mensajeUsuario.clear();
    		mensajeUsuario.append("Descarga Finalizada");
    	}
    	else{
    		mensajeUsuario.clear();
    		mensajeUsuario.append("No se pudo realizar la descarga");
    	}
    	delete control;
	bigEditor->setText(mensajeUsuario);
    };
    void Dialog::configurarClick()
    {
	QString config;
    	config.append("Configuracion ingresada: ");
	config.append(lineEdits[2]->text());

	Controller* control= new Controller(lineEdits[0]->text().toStdString());
	IndexConfig indexConfig;/////debo setear con los parametros que tiene lineEdits[2]
				indexConfig.setUserName(lineEdits[0]->text().toStdString());
				indexConfig.setTypeIndex("Secundario");
				indexConfig.setTypeSecundaryIndex("Seleccion");
				indexConfig.setCondition(1);
				indexConfig.setValue("michael.richters@gmail.com");
				indexConfig.setFilterName("SEL_TEST");
	control->addSecondIndex(&indexConfig);

	bigEditor->setText(config);
    };
	void Dialog::clasificarClick(QString texto)
    {
    	QString tag;
    	tag.append(lineEdits[2]->text());
    	tag.append("[");
    	tag.append(texto);
    	tag.append("='']");
    	lineEdits[2]->setText(tag);
    };

	void Dialog::seleccionarClick(QString texto)
    {
    	QString tag;
    	tag.append(lineEdits[2]->text());
    	tag.append("[");
    	tag.append(texto);
    	tag.append("]");
    	lineEdits[2]->setText(tag);
    };
    
