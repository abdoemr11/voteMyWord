#ifndef WORD_WIDGET_H 
#define WORD_WIDGET_H 
#include <QWidget>
#include <QString>
class QLabel;
class QPushButton;
class QGridLayout;
class WordWidget: public QWidget
{
	Q_OBJECT 
public:
	WordWidget(int id,QWidget *parent=0);
private slots:
	void upvote();
	void downvote();
    void showWho();
private:
	void getWord();
	void getVoteCounter();
    void voteWord(QString);

	QGridLayout *widgetLayout;
	QLabel *wordLabel;
	QLabel *countLabel;
	QPushButton *upvoteButton;
	QPushButton *downvoteButton;
	QPushButton *showWhoButton;
	int word_id;
	int voteCounter;
	QString word_text;
	QString upvoter;
	QString downvoter;


};
#endif
