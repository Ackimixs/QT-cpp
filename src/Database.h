#ifndef CPP_QT_TPMINIPROJET_DATABASE_H
#define CPP_QT_TPMINIPROJET_DATABASE_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFile>
#include <QDir>
#include <QDate>

#include "EnvFile.h"

#include "Logger.h"

class Database {
private:
    QSqlDatabase db;
    QSqlQuery q;

    bool dbOpen;

    bool dbHaveAccess;

public:
    Database();
    ~Database();

    QList<QMap<QString, QString>> query (QString query);

    void insert(QString query);

    QList<QMap<QString, QString>> queryWIthDatabase(QString query);

    QList<QMap<QString, QString>> queryInAFile(QString dataToSelect, QString table, QString orderBy = nullptr, QString columnToSort = "");

    void insertInAFile(QString table, QString data);

    void insertWithDatabase(QString query);

    void printList(QList<QMap<QString, QString>> listOfString);
};


#endif //CPP_QT_TPMINIPROJET_DATABASE_H
