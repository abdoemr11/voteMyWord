#include "voteapp.h"
#include "wordwidget.h"
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QDebug>
VoteApp::VoteApp(QWidget *parent)
	:QDialog(parent)
{
	initLayout();
	populateLayout();
	connect(loginButton, SIGNAL(clicked()),
			this, SLOT(login()));
	connect(logoutButton, SIGNAL(clicked()),
			this, SLOT(logout()));
	connect(addNewButton, SIGNAL(clicked()),
			this, SLOT(addNewWord()));
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
		wordWidget = new WordWidget(QString("%1").arg(i) );
        middleLayout->addWidget( wordWidget );
	}
	bottomLayout->addRow(newWordLineEdit, addNewButton);

}
void VoteApp::login()
{
	qDebug() << "clicked login button "	;
	loginButton->setVisible(false);
	loginLineEdit->setVisible(false);
	logoutButton->setVisible(true);
}
void VoteApp::logout()
{
	qDebug() << "clicked logout button "	;
	loginButton->setVisible(true);
	loginLineEdit->setVisible(true);
	logoutButton->setVisible(false);
}
void VoteApp::addNewWord()
{
	qDebug() << "The new Word is "	<< newWordLineEdit->text() ;
}
