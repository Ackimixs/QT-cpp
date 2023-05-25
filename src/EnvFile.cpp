#include "EnvFile.h"

QMap<QString, QString> EnvFile::readFile(const QString &filePath) {
    QMap<QString, QString> envVariables;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty() && !line.startsWith('#')) {
                QStringList parts = line.split('=');
                if (parts.size() == 2) {
                    QString key = parts[0].trimmed();
                    QString value = parts[1].trimmed();
                    envVariables.insert(key, value);
                }
            }
        }
        file.close();
    }

    return envVariables;
}