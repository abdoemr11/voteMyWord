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
	WordWidget(QString str,QWidget *parent=0);
private slots:
	void upvote();
	void downvote();
	void showWho();

private:
	QGridLayout *widgetLayout;
	QLabel *wordLabel;
	QLabel *countLabel;
	QPushButton *upvoteButton;
	QPushButton *downvoteButton;
	QPushButton *showWhoButton;
	int voteCounter;


};
#endif
