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

    static QSqlQuery q;

    static bool dbOpen;

public:

    static void setupDB();

    static void closeDB();

    static QList<QMap<QString, QString>> query (QString query);

    static void insert(QString query);

    static QList<QMap<QString, QString>> queryWIthDatabase(QString query);

    static QList<QMap<QString, QString>> queryInAFile(const QString& query);

    static void insertInAFile(QString table, QString data);

    static void insertWithDatabase(QString query);

};


#endif //CPP_QT_TPMINIPROJET_DATABASE_H
