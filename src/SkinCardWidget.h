#ifndef CPP_QT_MINIPROJET_SKINCARDWIDGET_H
#define CPP_QT_MINIPROJET_SKINCARDWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>

#include "settings.h"

class SkinCardWidget : public QWidget {
    Q_OBJECT
public:
    SkinCardWidget(const QString& shipNb, const QColor& backgroundColor, int price, QWidget* parent = nullptr);

signals:
    void shipBought();

    void changeShipSelect();

protected:
    void mousePressEvent(QMouseEvent* event) override;
private:
    QString imagePath;
    QColor backgroundColor;
    QString shipNb;
    int price;

    QLabel* priceLabel;
};




#endif //CPP_QT_MINIPROJET_SKINCARDWIDGET_H
