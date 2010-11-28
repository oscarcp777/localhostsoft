

    #ifndef DIALOGMAIL_H
    #define DIALOGMAIL_H

    #include <QDialog>

    class QAction;
    class QGroupBox;
    class QLabel;
    class QLineEdit;
    class QMenu;
    class QMenuBar;
    class QPushButton;
    class QTextEdit;

    class DialogMail : public QDialog
    {
        Q_OBJECT

    public:
        DialogMail(QString emailUIDs);

    private:

	void createMenu();
    	void okClick();

	QMenuBar *menuBar;
        QTextEdit *bigEditor;
        QPushButton *okButton;

        QMenu *fileMenu;
        QAction *exitAction;

   
    };


#endif /* DIALOGMAIL_H_ */
