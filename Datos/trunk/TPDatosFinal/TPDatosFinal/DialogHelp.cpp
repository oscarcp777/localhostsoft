/*
 * DialogHelp.cpp
 *
 *  Created on: 29/11/2010
 *      Author: oscar
 */
 #include <QtGui>
#include "DialogHelp.h"

DialogHelp::DialogHelp(){

	this->setMinimumHeight(600);
	this->setMinimumWidth(550);
	QString mensaje;
	mensaje.append("<table width=\"100%\" border=1 cellspacing=0>\n");
    mensaje.append("<tr><td align=\"center\" bgcolor=\"#E0E0E0\"><font size=\"+3\">");
	mensaje.append("\n<br>\n<i>     Manual  de usuario Arquitect Mail Application</i></b></font>\n</td></tr>");
    mensaje.append("<tr><td bgcolor=\"#E0E0E0\"><font size=\"+1\"><ul type=\"circle\">");
    mensaje.append("\n<br>\n<li>Importante: Recuerde que para poder visualizar el mail completo debera ingresar en numero de Iuc en area de Buscar y luego hacer clic en Ver</li></b>");
	mensaje.append("<li>Si desea bajar los mails del servidor debera hacer click en Resguardar mails</li></b>");
	mensaje.append("<li>Para poder crear filtros debera hacer click en los diferentes filtros From,To,Subject,Date tanto en clasification como seleccion y luego hacer click en Configuracion y en el panel de abajo le aparecera los filtros que ud creo</li></b>");
	mensaje.append("<li>Una vez que Uds. configuro los filtros que deseaba, podra guardarlos haciendo click en Resguardar Filtros</li></b>");
	mensaje.append("<li>Para crear un filtro por contenido de los mails debera hacer click en content , configuracion y luego resguardar filtros, una vez hecho esto puede hacer busquedas por contenido haciendo click en buscar </li></b>");
	mensaje.append("<li>Tambien puede hacer busquedas de los mails por los filtros que creo: Para ello debera seleccionar From,To,Subject,Date tanto en clasification como seleccion y hace click en buscar y le apareran los Iuc de los Mail que Uds. busco</li></b>");
    mensaje.append(	"\n</ul></td></tr>");
    mensaje.append(	"\n<br></table>");
    qthtml= new QTextDocument;
    qthtml->setHtml(mensaje);
	bigEditor = new QTextEdit;
	bigEditor->setReadOnly(true);
	bigEditor->setDocument(qthtml);
	okButton = new QPushButton(tr("OK"));

	connect(okButton, SIGNAL(clicked()), this, SLOT(reject()) );

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(okButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(bigEditor);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);

	setWindowTitle(tr("Manual de usuario "));

}


