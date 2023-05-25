#ifndef CPP_QT_TPMINIPROJET_DATABASE_H
#define CPP_QT_TPMINIPROJET_DATABASE_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>

#include "EnvFile.h"

#include "Logger.h"

class Database {
private:
    QSqlDatabase db;
    QSqlQuery* q;

    bool dbOpen;
public:
    Database();
    ~Database();

    QList<QMap<QString, QString>> query (QString query);

    void printList(QList<QMap<QString, QString>> listOfString);
};


#endif //CPP_QT_TPMINIPROJET_DATABASE_H
