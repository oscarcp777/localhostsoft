/*
 * dialog.h
 *
 *  Created on: Aug 16, 2010
 *      Author: aleee
 */

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <iostream>
#include "dialogMail.h"
#include "src.datos.controller/Controller.h"
#define CANT_BOTONES 5
#define CANT_FILAS 4

class QAction;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
using namespace std;

class Dialog : public QDialog
{
	Q_OBJECT

public:
	Dialog();

private:
	void createMenu();
	void createLoginGroupBox();
	void createOperationGroupBox();
	void createClassificationGroupBox();
	void createSelectionGroupBox();
	void createSearchGroupBox();
	void createDeleteGroupBox();

	QMenuBar *menuBar;
	 QAction *ayuda;
	QGroupBox *loginGroupBox;
	QGroupBox *operationGroupBox;
	QGroupBox *classificationGroupBox;
	QGroupBox *selectionGroupBox;
	QGroupBox *searchGroupBox;
	QGroupBox *deleteGroupBox;
	QTextEdit *smallEditor;
	QTextEdit *bigEditor;
	QLabel *labels[CANT_FILAS];
	QLineEdit *lineEdits[CANT_FILAS];
	QPushButton *buttons[CANT_BOTONES+10];
	QPushButton *okButton;
	QPushButton *cancelButton;

	QMenu *fileMenu;
	QAction *exitAction;
	void setMessages(string message,bool clear);
public slots:
void okClick();
void cancelClick();
void buscarClick();
void borrarClick();
void verClick();
void resguardarClick();
void verManual();
void configurarClick();
void clasificarClick(QString texto);
void seleccionarClick(QString texto);
};


#endif /* DIALOG_H_ */
