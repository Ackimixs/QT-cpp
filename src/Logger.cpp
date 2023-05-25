#include "Logger.h"

bool Logger::isDevMode = true;

Logger::Logger() {
    qInfo() << "Logger created";
}

void Logger::log(QList<QString> Headers, Logger::Type type, QString message, bool inDevMode) {
    QString time = Utils::getCurrentDateTime();

    if (!inDevMode || Logger::isDevMode) {
        if (type == Logger::Error) {
            qInfo() << Color::bgBlack << time << Color::reset << Color::bgRed << "[" << Headers.join(", ").trimmed() << "]" << enumToString(type).trimmed() << Color::reset << "|" << message;
        } else if (type == Logger::Success) {
            qInfo() << Color::bgBlack << time << Color::reset << Color::bgGreen << "[" << Headers.join(", ").trimmed() << "]" << enumToString(type).trimmed() << Color::reset  << "|" << message;
        } else if (type == Logger::Debug) {
            qInfo() << Color::bgBlack << time << Color::reset << Color::bgCyan << "[" << Headers.join(", ").trimmed() << "]" << enumToString(type).trimmed() << Color::reset  << "|" << message;
        } else if (type == Logger::Create) {
            qInfo() << Color::bgBlack << time << Color::reset << Color::bgBrightGreen << "[" << Headers.join(", ").trimmed() << "]" << enumToString(type).trimmed() << Color::reset  << "|" << message;
        } else if (type == Logger::Delete) {
            qInfo() << Color::bgBlack << time << Color::reset << Color::bgYellow << "[" << Headers.join(", ").trimmed() << "]" << enumToString(type).trimmed() << Color::reset  << "|" << message;
        } else if (type == Logger::Collision) {
            qInfo() << Color::bgBlack << time << Color::reset << Color::bgBlue << "[" << Headers.join(", ").trimmed() << "]" << enumToString(type).trimmed() << Color::reset  << "|" << message;
        } else {
            qInfo() << Color::bgBlack << time << Color::reset << "[" << Headers.join(", ").trimmed() << "]" << enumToString(type).trimmed() << "|" << message;
        }
    }
}

QString Logger::enumToString(Logger::Type type) {
    switch (type) {
        case Logger::Collision:
            return "collision";
        case Logger::Error:
            return "error";
        case Logger::Success:
            return "success";
        case Logger::Debug:
            return "debug";
        case Logger::Create:
            return "create";
        case Logger::Delete:
            return "delete";
        default:
            return "undefined";
    }
}