/*
 * DialogHelp.h
 *
 *  Created on: 29/11/2010
 *      Author: oscar
 */

#ifndef DIALOGHELP_H_
#define DIALOGHELP_H_

 #include <QDialog>

    class QAction;
    class QGroupBox;
    class QLabel;
    class QLineEdit;
    class QMenu;
    class QMenuBar;
    class QPushButton;
    class QTextEdit;
    class QTextDocument;

class DialogHelp: public QDialog {
	Q_OBJECT
public:
	DialogHelp();
private:
	QMenuBar *menuBar;
	        QTextEdit *bigEditor;
	        QPushButton *okButton;
	        QTextDocument *qthtml;
	        QMenu *fileMenu;
	        QAction *exitAction;

};

#endif /* DIALOGHELP_H_ */
