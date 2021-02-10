#include "voteapp.h"
#include "wordwidget.h"
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QSqlQuery>
#include <QDebug>
#define NO_MEMBER 1000
VoteApp::VoteApp(QWidget *parent)
	:QDialog(parent)
{
	//member_id = NO_MEMBER;
	initLayout();
	populateLayout();
	initWords();
	connect(loginButton, SIGNAL(clicked()),
			this, SLOT(login()));
	connect(logoutButton, SIGNAL(clicked()),
			this, SLOT(logout()));
	connect(addNewButton, SIGNAL(clicked()),
			this, SLOT(addNewWord()));
}
int VoteApp::member_id = NO_MEMBER ;
bool VoteApp::canVote = false;
void VoteApp::initWords()
{
	QSqlQuery query;
	query.exec("SELECT * FROM word;");
	while(query.next())	
	{
		int word_id = query.value(0).toInt();
		QString word_text = query.value(1).toString();
		wordWidget = new WordWidget(word_id);
        middleLayout->addWidget( wordWidget );
	}
}
void VoteApp::initLayout()
{
	mainLayout = new QVBoxLayout(this);
	setLayout(mainLayout);
	topLayout = new QFormLayout();
	topLogOutLayout = new QFormLayout();
	middleLayout = new QVBoxLayout();
	bottomLayout = new QFormLayout();
	mainLayout->addLayout(topLayout);
	////////////////////////////
    scrollArea = new QScrollArea( );
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollArea->setWidgetResizable( true );
    scrollArea->setGeometry( 10, 10, 200, 200 );
	middleWidget = new QWidget();
	mainLayout->addWidget(scrollArea);
	scrollArea->setWidget(middleWidget);
	middleWidget->setLayout(middleLayout);
	////////////////////////
	mainLayout->addLayout(bottomLayout);
}
void VoteApp::populateLayout()
{
	//add widgets to layout
	//first define these widgets
	//topLayout widgets
	loginButton = new QPushButton("login");		
	logoutButton = new QPushButton("logout");
	logoutButton->setVisible(false);
	addNewButton = new QPushButton("add new word");
	loginLineEdit = new QLineEdit();
	newWordLineEdit = new QLineEdit();
//populate layouts
	topLayout->addRow(loginLineEdit, loginButton);
	
	topLayout->addRow( logoutButton);
	// this is for debugging purposes only
    for (int i = 0; i < 20; i++)
    {
	//	wordWidget = new WordWidget(QString("%1").arg(i) );
     //   middleLayout->addWidget( wordWidget );
	}
	bottomLayout->addRow(newWordLineEdit, addNewButton);

}
void VoteApp::login()
{
	qDebug() << "clicked login button "	;
	//Check if the user is in the database
	//if yes set the current user to it
	QSqlQuery query;
	query.exec("SELECT member_name, member_id FROM member;");
	QString input_member = loginLineEdit->text();
	while(query.next())
	{
		QString member = query.value(0).toString();	
		qDebug() << member;
		if(member == input_member)
		{
			member_id = query.value(1).toInt();
			qDebug() << "valid member";	
			loginButton->setVisible(false);
			loginLineEdit->setVisible(false);
			logoutButton->setVisible(true);
			canVote = true;
			return ;
		}
	}
			qDebug() <<"Not valid member" ;	
}
void VoteApp::logout()
{
	qDebug() << "clicked logout button "	;
	loginButton->setVisible(true);
	loginLineEdit->setVisible(true);
	logoutButton->setVisible(false);
	qDebug() << "member " << member_id << " is logging out";
	member_id = NO_MEMBER;
	canVote = false;
}
void VoteApp::addNewWord()
{
	QString newWord = newWordLineEdit->text();
	if (!VoteApp::canVote)
	{
		qDebug() << "please log in first to add words";
		return;
	}
	if(!newWord.isEmpty())
	{
		qDebug() << "The new Word is "	<< newWord ;
		QSqlQuery query;
		query.prepare("INSERT INTO word "
					"(word_text) "
					"VALUES(?) ;");
		query.bindValue(0, newWord);

		query.exec();
		qDeleteAll(middleWidget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
		initWords();

	}
	else 
		qDebug() << "Please enter a valid word";
}
