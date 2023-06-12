#include "SkinCardWidget.h"

SkinCardWidget::SkinCardWidget(const QString& shipNb, const QColor& backgroundColor, int price, QWidget* parent)
    : QWidget(parent), imagePath(":/assets/img/player/" + shipNb + ".png"), backgroundColor(backgroundColor), price(price), shipNb(shipNb) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap(imagePath));
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    this->priceLabel = new QLabel(QString("%1").arg(price), this);
    if (SettingsManager::getInstance().value("hasShip" + shipNb).toBool()) {
        priceLabel->setText("Owned");
    }
    this->priceLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(this->priceLabel);

    setLayout(layout);

    setStyleSheet(QString("background-color: %1;").arg(backgroundColor.name()));
}

void SkinCardWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (SettingsManager::getInstance().value("hasShip" + shipNb).toBool()) {
            SettingsManager::getInstance().setValue("selectedShip", shipNb);
            emit changeShipSelect();
        }
        else {
            if (SettingsManager::getInstance().value("money").toInt() >= price) {
                SettingsManager::getInstance().setValue("money", SettingsManager::getInstance().value("money").toInt() - price);
                SettingsManager::getInstance().setValue("hasShip" + shipNb, true);
                SettingsManager::getInstance().setValue("selectedShip", shipNb);
                this->priceLabel->setText("Owned");
                emit shipBought();
                emit changeShipSelect();
            }
        }
    }
    QWidget::mousePressEvent(event);
}