#ifndef CPP_QT_TPMINIPROJET_LOGGER_H
#define CPP_QT_TPMINIPROJET_LOGGER_H

#include <QDebug>
#include <QString>

#include "Color.h"
#include "utils.h"

class Logger {

public:

    enum Type {
        Error,
        Success,
        Debug,
        Create,
        Delete,
        Collision
    };

    Logger();

    static bool isDevMode;

    static void log(QList<QString> Headers, Logger::Type sucess, QString message, bool inDevMode = false);

    static QString enumToString(Logger::Type type);

};


#endif //CPP_QT_TPMINIPROJET_LOGGER_H
