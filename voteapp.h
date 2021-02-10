#ifndef VOTE_APP_H
#define VOTE_APP_H
#include <QDialog>
class QPushButton;
class QLineEdit;
class QVBoxLayout;
class QFormLayout;
class WordWidget;
class QWidget;
class QScrollArea;
class VoteApp:public QDialog
{
	Q_OBJECT
public:
	VoteApp(QWidget *parent=0);
	static int member_id;
	static bool canVote;	
private slots:
	void login();
	void logout();
	void addNewWord();
private:
	void initWords();
	void initLayout();
	void populateLayout();

	QPushButton *loginButton;
	QPushButton *logoutButton;
	QPushButton *addNewButton;
	QLineEdit *loginLineEdit;
	QLineEdit *newWordLineEdit;
	WordWidget *wordWidget;
	QWidget *middleWidget;		
	QScrollArea *scrollArea;	

	QVBoxLayout *mainLayout;
	QFormLayout *topLayout ; 
	QFormLayout *topLogOutLayout;
	QVBoxLayout *middleLayout;
	QFormLayout *bottomLayout;
	//********************************
};
#endif

