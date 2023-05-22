#include "SQLClientWindow.h"

SQLClientWindow::SQLClientWindow() : QMainWindow() {
    this->setWindowTitle("SQL Client");
    this->setMinimumSize(600, 400);

    this->parent = new QWidget();
    this->layout = new QVBoxLayout();
    this->parent->setLayout(this->layout);

    this->buttonPanel = new ButtonPanel();

    this->notificationPanel = new QTextEdit();

    this->tableWidget = new QTableWidget();
    this->tableWidget->setRowCount(5);
    this->tableWidget->setColumnCount(3);

    this->layout->addWidget(this->buttonPanel);
    this->layout->addWidget(this->notificationPanel);
    this->layout->addWidget(this->tableWidget);


    this->setCentralWidget(this->parent);

    this->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}