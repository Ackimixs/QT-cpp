#ifndef CPP_QT_MINIPROJET_MAPPINGLAYOUT_H
#define CPP_QT_MINIPROJET_MAPPINGLAYOUT_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>
#include <QKeyEvent>

#include "keyPressedDialogRecorder.h"
#include "Database.h"
#include "settings.h"
#include "Logger.h"

class MappingLayout : public QHBoxLayout {
    Q_OBJECT
public:
    MappingLayout(QString label);

protected:

    QString keySettings;

    QLabel* mappingLabel1;
    QPushButton* recordButton;
    keyPressedDialogRecorder* dialog;

private slots:
    void recordKeyInfo();

    void keyChanged(int key);
};


#endif //CPP_QT_MINIPROJET_MAPPINGLAYOUT_H
