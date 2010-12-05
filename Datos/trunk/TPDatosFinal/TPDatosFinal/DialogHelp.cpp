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
	this->setMinimumWidth(800);
	QString mensaje;
	mensaje.append("<table width=\"100%\" border=1 cellspacing=0>\n");
    mensaje.append("<tr><td align=\"center\" bgcolor=\"#E2DFDA\"><font size=\"+3\">");
	mensaje.append("\n<br>\n<i> <STRONG>    Manual  de usuario Architect Mail Application</STRONG></i></b></font>\n</td></tr>");
    mensaje.append("<tr><td bgcolor=\"#E2DFDA\"><font size=\"+1\"><ul type=\"circle\">");
    mensaje.append("\n<br>\n<p><li><STRONG> Para realizar todas las operaciones se debe ingresar la cuenta de correo y la clave. La direccion de correo debe ingresarse de manera completa.</STRONG></li></p></b>");
	mensaje.append("<p><li><STRONG> Resguardar :</STRONG> Se conecta con el servidor y baja los mails nuevos. Crea el indice primario o lo actualiza, si ya existen los indices secundarios, estos son actualizados.</li</p></b>");
	mensaje.append("<p><li><STRONG>Configurar :</STRONG> Se encarga de crear los indices secundarios, esto se logra seteando en el textbox de la seccion \"Buscar\" la configuracion del indice deseada.</li></p><p><STRONG> Las configuraciones posibles se realizan de la siguiente manera: </STRONG></p>\n</b></b>");
	mensaje.append("<p><STRONG>Indices de seleccion: </STRONG>");
	mensaje.append("[From='parametro']</p></b>");
	mensaje.append("<p><STRONG>Indice de clasificacion :</STRONG>");
	mensaje.append("[From]</p></b>");
	mensaje.append("<p><STRONG>Indices invertidos :</STRONG>");
	mensaje.append("[Content]</p></b>");
	mensaje.append("<p><li><STRONG>Buscar :</STRONG> Escribiendo la palabra 'indices' dentro del textbox de busqueda, se muestra en el dialogBox inferior una lista de los indices que han sido creados y que se vinculan a la cuenta de usuario de la sesion.</li></p><p><STRONG> Para realizar busquedas sobre los indices secundarios se deben ingresar de la siguiente forma:</STRONG></p></b>");
	mensaje.append("<p><STRONG>Indice de seleccion :</STRONG>");
	mensaje.append("[FromParametro]</p></b>");
	mensaje.append("<p><STRONG>Indice de clasificacion :</STRONG>");
	mensaje.append("[From='parametro']</p></b>");
	mensaje.append("<p><li>Los nombres de los indices de seleccion estan formados por el filtro y la concatenacion del parametro, para ayudarse a buscar, se recomienda escribir 'indices' y presionar buscar, para saber los nombres de los indices.</li></p></b>");
	mensaje.append("<p><li>Tambien puede hacer busquedas de los mails por los filtros que creo: Para ello debera seleccionar From,To,Subject,Date tanto en clasification como seleccion y hace click en buscar y le apareran los Iuc de los Mail que Uds. busco</li></p></b>");
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


