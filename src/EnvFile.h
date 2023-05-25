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

    EnvFile(const QString& filePath)
    {
        envVariables = readFile(filePath);
    }

    QString getValue(const QString& key) const
    {
        return envVariables.value(key);
    }

private:
    QMap<QString, QString> envVariables;
};


#endif //CPP_QT_TPMINIPROJET_ENVFILE_H
