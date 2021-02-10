#include "voteapp.h"
#include <QApplication>
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
bool createConnection()
{ 
    //db.setHostName("localhost");
    db.setDatabaseName("test.db");
    //db.setUserName("root");
    //db.setPassword("123123");
    if(!db.open())
    { 
        QMessageBox::critical(0, QObject::tr("Database Error"), 
                                db.lastError().text());
        return false;

    }
    return true;
}
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	if(!createConnection())
		return 1;
	VoteApp *voteApp = new VoteApp();
	voteApp->show();
	return app.exec();
}
