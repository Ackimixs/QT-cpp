
#include "Database.h"

Database::Database() {
    this->db = QSqlDatabase::addDatabase("QPSQL");

    auto envData = EnvFile::readFile(".env");

    db.setHostName(envData.value("DB_HOSTNAME"));
    db.setDatabaseName(envData.value("DB_DBNAME"));
    db.setUserName(envData.value("DB_USERNAME"));
    db.setPassword(envData.value("DB_PASSWORD"));

    if (db.open()) {
        this->dbOpen = true;
        // Connection successful
        Logger::log({"Database"}, Logger::Success, "Connection succesfull");

        QList<QMap<QString, QString>> res = this->query("SELECT * FROM LEADERBOARD");

    } else {
        this->dbOpen = false;
        // Connection failed
        Logger::log({"Database"}, Logger::Error, "Connection failed");
    }

}

Database::~Database() {
    Logger::log({"Database"}, Logger::Delete, "Database disconnected", true);
    db.close();
}

QList<QMap<QString, QString>> Database::query(QString query) {

    if (!this->dbOpen) {
        Logger::log({"Database", "Query"}, Logger::Error, "trying to query while database is not open");
        return {};
    }

    this->q = new QSqlQuery(query);

    QList<QMap<QString, QString>> res;
    while (this->q->next()) {
        QMap<QString, QString> rowRes;

        QSqlRecord record = q->record();
        int columnCount = record.count();

        for (int j = 0; j < columnCount; j++) {
            QString col = record.fieldName(j);
            rowRes.insert(col, this->q->value(j).toString());
        }
        res.append(rowRes);
    }

    Logger::log({"Database", "Query"}, Logger::Success, query, true);

    return res;
}

void Database::printList(QList<QMap<QString, QString>> listOfString) {
    for (int i = 0; i < listOfString.count(); i++) {
        QMapIterator<QString, QString> it(listOfString[i]);
        qInfo() << "------------";
        while (it.hasNext()) {
            it.next();
            qInfo() << it.key() << ": " << it.value();
        }
    }
}