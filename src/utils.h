#ifndef CPP_QT_TPMINIPROJET_UTILS_H
#define CPP_QT_TPMINIPROJET_UTILS_H

#include <QString>
#include <QDateTime>
#include <QRandomGenerator>
#include <QPixmap>
#include <QPainter>

namespace Utils {
    static QString getCurrentDateTime() {
        return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    }

    static int randInt(int low, int high) {
        return QRandomGenerator::global()->bounded(low, high);
    }

    static QPixmap addTransparencyToPixmap(const QPixmap& pixmap, qreal opacity = 0.5) {
        QPixmap resultPixmap(pixmap.size());
        resultPixmap.fill(Qt::transparent);

        QPainter painter(&resultPixmap);
        painter.setOpacity(opacity);
        painter.drawPixmap(0, 0, pixmap);
        painter.end();

        return resultPixmap;
    }

    static QPixmap addPixmapOnTop(const QPixmap& backgroundPixmap, const QPixmap& overlayPixmap) {
        QPixmap resultPixmap(backgroundPixmap.size());
        resultPixmap.fill(Qt::transparent);

        QPainter painter(&resultPixmap);
        painter.drawPixmap(0, 0, backgroundPixmap);
        painter.drawPixmap(0, 0, overlayPixmap);
        painter.end();

        return resultPixmap;
    }


    static QImage cutImage(const QString& imagePath, int finalHeight, int numCuts, int currentCut) {
        QImage baseImage(imagePath);

        int width = baseImage.width();
        int height = baseImage.height();

        int nbPart = int((height - 800) / numCuts);

        QImage cutImage = baseImage.copy(0, nbPart * (numCuts - currentCut), width, finalHeight);

        return cutImage;
    }

    static QList<QString> parseSqlQuery(const QString& sqlQuery) {
        QString trimmedQuery = sqlQuery.trimmed();

        int selectPos = trimmedQuery.indexOf("SELECT");
        int fromPos = trimmedQuery.indexOf("FROM");
        int orderPos = trimmedQuery.indexOf("ORDER BY");

        QString columns = trimmedQuery.mid(selectPos + 6, fromPos - selectPos - 6).trimmed();

        QString table = trimmedQuery.mid(fromPos + 4, orderPos - fromPos - 4).trimmed();

        QStringList sorting = trimmedQuery.mid(orderPos + 8).trimmed().split(" ");
        QString orderColumn = sorting[0];
        QString orderBy = sorting[1];

        QStringList columnList = columns.split(',');

        for (QString& column : columnList) {
            column = column.trimmed();
        }

        return {columns, table, orderColumn, orderBy.remove(";")};
    }

    static QList<QString> parseInsertQuery(const QString& insertQuery) {
        // Remove leading and trailing whitespaces from the query
        QString trimmedQuery = insertQuery.trimmed();

        // Find the position of keywords in the query
        int intoPos = trimmedQuery.indexOf("INTO");
        int valuesPos = trimmedQuery.indexOf("VALUES");

        // Extract the table name
        QString table = trimmedQuery.mid(intoPos + 4, valuesPos - intoPos - 4).trimmed();

        // Extract the column-value pairs
        QString values = trimmedQuery.mid(valuesPos + 6).trimmed();

        // Remove parentheses from the values part
        values.remove('(');
        values.remove(')');

        // Remove single quotes around each value
        values = values.simplified();
        values = values.replace('\'', "");

        return {table.split(' ')[0], values};
    }

    static bool compareMaps(const QMap<QString, QString>& map1, const QMap<QString, QString>& map2, QString columnToSort, QString orderBy) {
        QString score1 = map1.value(columnToSort);
        QString score2 = map2.value(columnToSort);

        if (orderBy == "DESC") {
            return score1.toInt() > score2.toInt();
        } else if (orderBy == "ASC") {
            return score1.toInt() < score2.toInt();
        } else {
            return false;
        }
    }
};

#endif //CPP_QT_TPMINIPROJET_UTILS_H
