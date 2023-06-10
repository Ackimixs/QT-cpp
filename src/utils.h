#ifndef CPP_QT_TPMINIPROJET_UTILS_H
#define CPP_QT_TPMINIPROJET_UTILS_H

#include <QString>
#include <QDateTime>
#include <QRandomGenerator>
#include <QPixmap>
#include <QPainter>

enum GameLevel {
    EASY = 0,
    MEDIUM = 1,
    HARD = 2,
    IMPOSSIBLE = 3,
    AREUOK = 4,
    POWERUP = 5
};

namespace Utils {

    /**
     * @return a string representing the current date and time in the format "yyyy-MM-dd HH:mm:ss"
     */
    static QString getCurrentDateTime() {
        return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    }

    /**
     * @param low (include)
     * @param high (exclude)
     * @return a number from low and high - 1
     */
    static int randInt(int low, int high) {
        return QRandomGenerator::global()->bounded(low, high);
    }

    /**
     * @param pixmap
     * @param opacity from 0.1 - 1.0
     * @return a new pixmap with the opacity applied
     */
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


    static QImage cutImage(const QImage& img, int finalHeight, int numCuts, int currentCut) {

        int width = img.width();
        int height = img.height();

        int nbPart = int((height - 800) / numCuts);

        QImage cutImage = img.copy(0, nbPart * (numCuts - currentCut), width, finalHeight);

        QImage starImage(":/assets/img/star.png");

        QPainter painter(&cutImage);

        return cutImage;
    }

    static void addStars(QImage& image, int numStars) {
            QImage starImage(":/assets/img/background/Star.png");

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> xDist(0, image.width() - starImage.width());
            std::uniform_int_distribution<int> yDist(0, image.height() - starImage.height());

            QPainter painter(&image);
            for (int i = 0; i < numStars; ++i)
            {
                int x = xDist(gen);
                int y = yDist(gen);
                painter.drawImage(x, y, starImage);
            }
            painter.end();
    }

    static void addPlanete(QImage& image, int numStars) {
            QImage planeteImg(":/assets/img/background/Planete1.png");

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> xDist(0, image.width() - planeteImg.width());
            std::uniform_int_distribution<int> yDist(0, image.height() - planeteImg.height());

            QPainter painter(&image);
            for (int i = 0; i < numStars; ++i)
            {
                int x = xDist(gen);
                int y = yDist(gen);
                painter.drawImage(x, y, planeteImg);
            }
            painter.end();
    }


    static QList<QString> parseSqlQuery(const QString& sqlQuery) {
        QString trimmedQuery = sqlQuery.trimmed();

        int selectPos = trimmedQuery.indexOf("SELECT");
        int wherePos = trimmedQuery.indexOf("WHERE");
        int fromPos = trimmedQuery.indexOf("FROM");
        int orderPos = trimmedQuery.indexOf("ORDER BY");

        QString columns = trimmedQuery.mid(selectPos + 6, fromPos - selectPos - 6).trimmed();

        QString table = trimmedQuery.mid(fromPos + 4, wherePos - fromPos - 4).trimmed();

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

    static QList<QString> parseUpdateQuery(QString query) {
        // Remove leading and trailing whitespaces from the query
        QString trimmedQuery = query.trimmed();

        // Find the position of keywords in the query
        int setPos = trimmedQuery.indexOf("SET");
        int wherePos = trimmedQuery.indexOf("WHERE");

        // Extract the table name
        QString table = trimmedQuery.mid(6, setPos - 6).trimmed();

        // Extract the column-value pairs
        QString values = trimmedQuery.mid(setPos + 3, wherePos - setPos - 3).trimmed();

        // Remove parentheses from the values part
        values.remove('(');
        values.remove(')');

        // Remove single quotes around each value
        values = values.simplified();
        values = values.replace('\'', "");

        return {table, values};
        // TODO change it
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
