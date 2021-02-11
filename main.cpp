#include "voteapp.h"
#include <QApplication>
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
QString pack(QStringList const& list)
{
    return list.join(" ");
}
bool createConnection()
{ 
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("123123123");
    qDebug() << QSqlDatabase::drivers();
    if(!db.open())
    { 

        qDebug() << QSqlDatabase::drivers();
      //  QMessageBox::critical(0, QObject::tr("Database Error"),
          //                      pack(QSqlDatabase::drivers()));
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
