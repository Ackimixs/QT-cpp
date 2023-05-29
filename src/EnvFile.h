#ifndef CPP_QT_TPMINIPROJET_ENVFILE_H
#define CPP_QT_TPMINIPROJET_ENVFILE_H


#include <QFile>
#include <QTextStream>
#include <QMap>

#include <QFile>
#include <QTextStream>
#include <QMap>

class EnvFile
{
public:
    static QMap<QString, QString> readFile(const QString& filePath);

};


#endif //CPP_QT_TPMINIPROJET_ENVFILE_H
