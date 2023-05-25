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

};

#endif //CPP_QT_TPMINIPROJET_UTILS_H
