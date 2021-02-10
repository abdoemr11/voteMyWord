#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "voteapp.h"
#include "wordwidget.h"
#define UPVOTED 1
#define DOWNVOTED 0
WordWidget::WordWidget(int id,QWidget *parent)
	:QWidget(parent)
{
	word_id = id;
	getWord();
	//canVote = false;
	wordLabel = new QLabel(word_text);
	upvoteButton = new QPushButton("upvote");
	downvoteButton = new QPushButton("downvote");
	showWhoButton = new QPushButton("Who voted?");
	countLabel = new QLabel(QString::number(voteCounter));
	widgetLayout = new QGridLayout();
	setLayout(widgetLayout);
	widgetLayout->addWidget(wordLabel, 0, 0);
	widgetLayout->addWidget(countLabel, 0, 1);
	widgetLayout->addWidget(upvoteButton, 0, 2);
	widgetLayout->addWidget(downvoteButton, 0, 3);
	widgetLayout->addWidget(showWhoButton, 0, 4);
	//connect PushButtons with slots
	connect(upvoteButton, SIGNAL(clicked()), 
			this, SLOT(upvote()));
	connect(downvoteButton, SIGNAL(clicked()), 
			this, SLOT(downvote()));
	connect(showWhoButton, SIGNAL(clicked()), 
			this, SLOT(showWho()));
	//constraint the pushbutton size
	upvoteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}
void WordWidget::getWord()
{
	QSqlQuery query;
	query.prepare("SELECT word_text FROM word WHERE word_id = :id;");
	query.bindValue(":id", word_id);
	query.exec();
	while(query.next())
	{
		word_text = query.value(0).toString();			
	}
	getVoteCounter();
}
void WordWidget::upvote()
{
	//QDebug
	qDebug() << " try to upvote the word"	<< wordLabel->text();
	if(VoteApp::canVote)	
		voteWord(UPVOTED);
	else 
	{
		qDebug() << "Can't vote please login first";
		return;
	}
	//check if the user had voted this word previously	
	getWord();
	countLabel->setText(QString::number(voteCounter));
}
void WordWidget::downvote()
{
	
	qDebug() << " try to downvote the word"	<< wordLabel->text();
	if(VoteApp::canVote)	
		voteWord(DOWNVOTED);
	else 
	{
		qDebug() << "Can't vote please login first";
		return;
	}
	//retrieve the data from the database
	getWord();
	countLabel->setText(QString::number(voteCounter));
}
void WordWidget::voteWord(int vote_type)
{
	
	QSqlQuery query;
	if(!query.prepare("SELECT 1 FROM vote "
					"WHERE member_id = ? "
					"AND word_id = ? ;"))
		qDebug() << query.lastError().text();		
	//qDebug() << VoteApp::member_id;
	query.bindValue(0, VoteApp::member_id);
	query.bindValue(1, word_id);
	if(!query.exec())
	{
		qDebug() << query.lastError().text();		
	}
	int exist = 0;
	if(query.next())		
	{
		exist = query.value(0).toInt();
		qDebug() << " 1 if exist >>>  " << exist;
	}
	//if exist update 
	if(exist)
	{
			
		if(!query.prepare("UPDATE vote  "
						" SET vote_type = ? "
						"WHERE member_id = ? "
						"AND word_id = ? ;"))
			qDebug() << query.lastError().text();		
		query.bindValue(0, vote_type);
		query.bindValue(1, VoteApp::member_id);
		query.bindValue(2, word_id);
		query.exec();
	}
	else
	{
		if(!query.prepare("INSERT INTO vote "		
						"(member_id, vote_type, word_id) "
						"VALUES(?, ?, ?) ;"))
			qDebug() << query.lastError().text();
		query.bindValue(0, VoteApp::member_id);
		query.bindValue(1, vote_type );
		query.bindValue(2, word_id );
		query.exec();
	}
}
void WordWidget::showWho()
{
	//retrive the data from the database	
	QSqlQuery query;	
	query.prepare("SELECT member_name FROM member WHERE member_id IN (SELECT member_id FROM vote WHERE vote_type = ? "
	"AND word_id = ?)");
	query.bindValue(0, UPVOTED);
	query.bindValue(1, word_id);
	if(!query.exec())
		qDebug()<< query.lastError().text();
	upvoter =  "";
	downvoter = "";
	while(query.next())	
	{
		upvoter += query.value(0).toString();			
		//if(!query.last)
			upvoter += ",  ";
		qDebug() << query.value(0).toString();
	//	qDebug() << "I am writing from query.next()";
	}
	qDebug() << "The person who upvoted" << upvoter;
	qDebug() << "The person who downvoted is" << downvoter;
}

void WordWidget::getVoteCounter()
{
	QSqlQuery query;	
	//get the votes counter = upvoted - downvoted
	int upcount = 0;
	int downcount = 0;
//	query.prepare("SELECT COUNT(*) FROM word WHERE word_id = :id OR vote_type = :VOTE_TYPE;");
	query.prepare("SELECT COUNT(*) FROM vote WHERE word_id =:id  AND vote_type = :VOTE_TYPE;");

	query.bindValue(":id", word_id);
	query.bindValue(":VOTE_TYPE", UPVOTED);
	query.exec();
	if(query.next())
		upcount = query.value(0).toInt();
	qDebug() << word_id << " upcounted =    <<" << upcount;	

	query.prepare("SELECT COUNT(*) FROM vote WHERE word_id =:id  AND vote_type = :VOTE_TYPE;");
	query.bindValue(":id", word_id);
	query.bindValue(":VOTE_TYPE", DOWNVOTED);
	query.exec();
	if(query.next())
		downcount = query.value(0).toInt();
	qDebug() << word_id << " downcounted =    <<" << downcount;	
	voteCounter = upcount - downcount;

}
