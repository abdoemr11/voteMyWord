#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include "wordwidget.h"
WordWidget::WordWidget(QString str,QWidget *parent)
	:QWidget(parent)
{
	wordLabel = new QLabel("electronics go"+str);
	upvoteButton = new QPushButton("upvote");
	downvoteButton = new QPushButton("downvote");
	showWhoButton = new QPushButton("Who voted?");
	countLabel = new QLabel(str);
	widgetLayout = new QGridLayout();
	setLayout(widgetLayout);
	widgetLayout->addWidget(wordLabel, 0, 0);
	widgetLayout->addWidget(countLabel, 0, 1);
	widgetLayout->addWidget(upvoteButton, 0, 2);
	widgetLayout->addWidget(downvoteButton, 0, 3);
	widgetLayout->addWidget(showWhoButton, 0, 4);
	connect(upvoteButton, SIGNAL(clicked()), 
			this, SLOT(upvote()));
}
void WordWidget::upvote()
{
	//QDebug
	qDebug() << "vote the word"	<< wordLabel->text();
	//increment the data base variable 	
	//retrieve the data from the database
}
void WordWidget::downvote()
{
	
	//increment the data base variable 	
	//retrieve the data from the database
}
void WordWidget::showWho()
{
	//retrive the data from the database	
}

