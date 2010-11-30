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
#include "DialogHelp.h"

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

    	bigEditor = new QTextEdit();
//    	bigEditor->setReadOnly(true);
    	bigEditor->setPlainText(tr("Informacion sobre la confguracion de los filtros de la applicacion "));



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
    	connect(buttons[5], SIGNAL(clicked()), this, SLOT(cargarClick()));
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

    	setWindowTitle(tr("Almacenamiento de Correos Electronicos"));
    }
    void cargarClick(){

    }
    void Dialog::createMenu()
    {
    	 QPixmap newpix("image/Help-32.png");

    	 ayuda = new QAction(newpix, "&Manual de Usuario", this);

        menuBar = new QMenuBar;

        fileMenu = new QMenu(tr("&Ayuda"), this);
//        exitAction = fileMenu->addAction(tr("Manual de Usuario"));
        menuBar->addMenu(fileMenu);
        fileMenu->addSeparator();
        fileMenu->addAction(ayuda);
        connect(ayuda, SIGNAL(triggered()), this, SLOT(verManual()));

    }

    void Dialog::createOperationGroupBox()
    {
        operationGroupBox = new QGroupBox(tr("Comunicacion"));
        QHBoxLayout *layout = new QHBoxLayout;

		buttons[0] = new QPushButton(tr("Resguardar mails"));
		layout->addWidget(buttons[0]);
		buttons[1] = new QPushButton(tr("Configurar"));
		layout->addWidget(buttons[1]);
		buttons[5] = new QPushButton(tr("Resguardar filtros"));
		layout->addWidget(buttons[5]);
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
            mensaje.append("Clasificacion ");
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
            mensaje.append("Seleccion ");
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
    void Dialog::verManual(){
    	DialogHelp dialogHelp;
    	dialogHelp.exec();
       }
    void Dialog::cancelClick()
    {
    	cout<<"exit\n"<<endl;
//    	exit;
    };
    void Dialog::cargarClick()
        {
        	cout<<"cargarClick"<<endl;
    //    	exit;
        };
    void Dialog::buscarClick()
    {
    	QString textoBuscado;
    	textoBuscado.append("Busco el texto: ");
    	textoBuscado.append(lineEdits[2]->text());
    	Controller* control= new Controller(lineEdits[0]->text().toStdString(),lineEdits[1]->text().toStdString());
    	if(control->getMailAndPass()){
    		if(lineEdits[2]->text().toStdString() == "indices"){
    			std::string aux = control->getListOfIndexes();
    			bigEditor->clear();
    			textoBuscado.clear();
    			textoBuscado.append(aux.c_str());
    			bigEditor->setText(textoBuscado);
    		}else{
    			control->searchMails(lineEdits[2]->text().toStdString());
    			string strResult;
    			list<int>::iterator it;
    			unsigned int numSearchs = control->getSearch()->getNumOfIndex();
    			if (numSearchs > 1)
    				control->calculateIntersection(numSearchs, control->getListOfIucs());
    			//cout<< "RESULTADO "<<endl;

    			for(it= control->iteratorBeginListOfIucs(); it != control->iteratorEndListOfIucs(); it++){
    				cout<<"IUC: "<<*it<<endl;
    				strResult += StringUtils::convertirAString(*it) + " ";
    			}

    			textoBuscado.append(strResult.c_str());
    			bigEditor->setText(textoBuscado);
    		}
    	}else{
    		bigEditor->clear();
    		bigEditor->append("...\nUSUARIO Y/O PASSWORD INVALIDOS");
    	}
         delete control;
    };
    void Dialog::borrarClick()
    {
    	QString listaUID;
    	listaUID.append("Mails a borrar (UIDs): ");
    	listaUID.append(lineEdits[3]->text());

    	////
    	Controller* control= new Controller(lineEdits[0]->text().toStdString(),lineEdits[1]->text().toStdString());
    	if(control->getMailAndPass()){
    		control->deleteIucs(lineEdits[3]->text().toStdString());
    		bigEditor->setText(listaUID);
    	}else{
    		bigEditor->clear();
    		bigEditor->append("...\nUSUARIO Y/O PASSWORD INVALIDOS");
    	}
    	////

    };
    void Dialog::verClick()
    {

    	//
    	Controller* control= new Controller(lineEdits[0]->text().toStdString(),lineEdits[1]->text().toStdString());
    	if(control->getMailAndPass()){
        	string result = control->getMails(lineEdits[3]->text().toStdString());
        	QString resultQ ((const char*)result.c_str());
        	cout<<result <<endl;
        	DialogMail dialogMail(resultQ);
            dialogMail.exec();
    	}else{
    		bigEditor->clear();
    		bigEditor->append("...\nUSUARIO Y/O PASSWORD INVALIDOS");
    	}
    	//
        delete control;

    };
    void Dialog::resguardarClick()
    {
    	QString mensajeUsuario;
    	/////
    	Controller* control= new Controller(lineEdits[0]->text().toStdString(),lineEdits[1]->text().toStdString());
//    	if(control->getMailAndPass()){
    		mensajeUsuario.append("Descargando mails de: ");


    		mensajeUsuario.append(lineEdits[0]->text());
    		bigEditor->setText(mensajeUsuario);
    		int flag =control->createPrimaryIndex();
    		if (flag > 0){
    			mensajeUsuario.clear();
    			mensajeUsuario.append("Descarga Finalizada");
    		}
    		else{
    			mensajeUsuario.clear();
    			mensajeUsuario.append("No se pudo realizar la descarga");
    		}

//    			std::string auxIndex;
//    			IndexConfig* configOne;
//    			list<IndexConfig*>::iterator current = control->iteratorBeginListOfIndexes();
//    			while((current != control->iteratorEndListOfIndexes())){//recorro la lista de todos lo indices que tiene el programa
//    				if(!((*current)->isLoaded())){
//    				auxIndex = (*current)->getFilterName();
//    				configOne = control->loadIndexConfig(auxIndex);
//    				control->loadSecondIndex(configOne);
//    				current++;
//    					}
//    				}


    		bigEditor->append("BAjando mails");
    	//	bigEditor->setText(mensajeUsuario);
//    	}else{
//    		bigEditor->clear();
//    		bigEditor->append("...\nUSUARIO Y/O PASSWORD INVALIDOS");
//    	}

    	delete control;

    };
    void Dialog::configurarClick()
    {
	QString config;
    	config.append("Configuracion ingresada: ");
	config.append(lineEdits[2]->text());



	Controller* control= new Controller(lineEdits[0]->text().toStdString(),lineEdits[1]->text().toStdString());
	if(control->getMailAndPass()){
		IndexConfig* indexConfig = control->createIndexConfig2(lineEdits[2]->text().toStdString());
			indexConfig->setUserName(lineEdits[0]->text().toStdString());
			control->addSecondIndex(indexConfig);
			control->loadSecondIndex(indexConfig);
			bigEditor->setText(config);
	}else{
		bigEditor->clear();
			bigEditor->append("...\nUSUARIO Y/O PASSWORD INVALIDOS");
	}

    };
	void Dialog::clasificarClick(QString texto)
    {
    	QString tag;
    	tag.append(lineEdits[2]->text());
    	tag.append("[");
    	tag.append(texto);
    	tag.append("='']");//tag.append("='']"   le saque las comillas
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
    
