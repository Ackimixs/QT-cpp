#ifndef TP2_SQLCLIENTWINDOW_H
#define TP2_SQLCLIENTWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QTableWidget>
#include <QHeaderView>

#include "ButtonPanel.h"

class SQLClientWindow : public QMainWindow {
private:
    QWidget* parent;
    QVBoxLayout* layout;
    ButtonPanel* buttonPanel;
    QTextEdit* notificationPanel;
    QTableWidget* tableWidget;

public:
    SQLClientWindow();

};


#endif //TP2_SQLCLIENTWINDOW_H
