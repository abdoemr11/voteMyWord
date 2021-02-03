#include "voteapp.h"
#include <QApplication>
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	VoteApp *voteApp = new VoteApp();
	voteApp->show();
	return app.exec();
}
