#include "Database.h"

bool Database::dbOpen = false;

QSqlQuery Database::q = QSqlQuery();

void Database::setupDB() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    auto envData = EnvFile::readFile(".env");

    db.setHostName(envData.value("DB_HOSTNAME"));
    db.setDatabaseName(envData.value("DB_DBNAME"));
    db.setUserName(envData.value("DB_USERNAME"));
    db.setPassword(envData.value("DB_PASSWORD"));

    if (db.open()) {
        Database::dbOpen = true;
        Logger::log({"Database"}, Logger::Success, "Connection succesfull");
    } else {
        Database::dbOpen = false;
        Logger::log({"Database"}, Logger::Error, "Connection failed, switch to file system");
    }
}

void Database::closeDB() {
    Logger::log({"Database"}, Logger::Delete, "Database disconnected", true);
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
}

QList<QMap<QString, QString>> Database::query(QString query) {
    if (Database::dbOpen) {
        return Database::queryWIthDatabase(query);
    } else {
        return Database::queryInAFile(query);
    }
}

QList<QMap<QString, QString>> Database::queryWIthDatabase(QString query) {
    QSqlDatabase db = QSqlDatabase::database();
    Database::q = db.exec(query);

    QList<QMap<QString, QString>> res;
    while (Database::q.next()) {
        QMap<QString, QString> rowRes;

        QSqlRecord record = q.record();
        int columnCount = record.count();

        for (int j = 0; j < columnCount; j++) {
            QString col = record.fieldName(j);
            rowRes.insert(col, Database::q.value(j).toString());
        }
        res.append(rowRes);
    }

    Logger::log({"Database", "Query"}, Logger::Success, query, true);

    return res;
}


QList<QMap<QString, QString>> Database::queryInAFile(const QString& query) {
    QString trimmedQuery = query.trimmed();
    if (trimmedQuery.endsWith(';')) {
        trimmedQuery.chop(1); // Remove the last character, i.e., the semicolon
    }

    QStringList queryParts = trimmedQuery.split(" ");    QString table = queryParts[queryParts.indexOf("FROM") + 1];
    QString orderBy;
    QString columnToSort;
    QString whereColumn;
    QString whereValue;

    // Extract ORDER BY clause if present
    int orderByIndex = queryParts.indexOf("ORDER");
    if (orderByIndex != -1) {
        orderBy = queryParts[orderByIndex + 3];
        columnToSort = queryParts[orderByIndex + 2];
    }

    // Extract WHERE clause if present
    int whereIndex = queryParts.indexOf("WHERE");
    if (whereIndex != -1) {
        whereColumn = queryParts[whereIndex + 1];
        whereValue = queryParts[whereIndex + 3];
    }

    QFile file(table + ".csv");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString fileContents = in.readAll();
        file.close();
        QStringList everyRow = fileContents.split("\n");

        QStringList column = everyRow[0].split(';');

        QList<QMap<QString, QString>> res;

        for (int i = 1; i < everyRow.count() - 1; i++) {
            QMap<QString, QString> rowRes;
            QStringList data = everyRow[i].split(";");
            for (int j = 0; j < column.count(); j++) {
                rowRes.insert(column[j], data[j]);
            }


            // Apply WHERE condition if provided
            if (whereColumn.isEmpty() || whereValue.isEmpty() || rowRes.value(whereColumn) == whereValue) {
                res.append(rowRes);
            }
        }

        if ((orderBy == "ASC" || orderBy == "DESC") && !columnToSort.isEmpty()) {
            std::sort(res.begin(), res.end(), [&](const QMap<QString, QString>& map1, const QMap<QString, QString>& map2) {
                return Utils::compareMaps(map1, map2, columnToSort, orderBy);
            });
        }


        Logger::log({"Database", "File system", "Query"}, Logger::Success, table, true);

        return res;
    }
    else {
        Logger::log({"Database", "File system"}, Logger::Error, "Failed to open file for reading : " + table + ".csv");
        return {};
    }
}


void Database::insert(QString query) {
    if (Database::dbOpen) {
        Database::insertWithDatabase(query);
    } else {
        QList<QString> newQuery = Utils::parseInsertQuery(query);
        Database::insertInAFile(newQuery[0], newQuery[1]+ "," + QDate::currentDate().toString("dd-MM-yyyy"));
    }
}

void Database::insertWithDatabase(QString query) {
    QSqlDatabase db = QSqlDatabase::database();
    db.exec(query);
}

void Database::insertInAFile(QString table, QString data) {
    QFile file(table + ".csv");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        data = (data.remove(" ").split(',').join(";")) + "\n";
        out << data;
        file.close();
        Logger::log({"Database", "File system"}, Logger::Success, "Writing data in file : " + table + ".csv");
    }
    else {
        Logger::log({"Database", "File system"}, Logger::Error, "Failed to open file for writing : " + table + ".csv");
    }
}