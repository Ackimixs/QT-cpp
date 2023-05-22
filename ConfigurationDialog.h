#ifndef TP2_CONFIGURATIONDIALOG_H
#define TP2_CONFIGURATIONDIALOG_H

#include <QDialog>
#include "LabeledTextField.h"

class ConfigurationDialog : public QDialog {
private:
    QVBoxLayout* layout;
    LabeledTextField* ipAddress;
    LabeledTextField* user;
    LabeledTextField* password;

public:
    ConfigurationDialog();
};


#endif //TP2_CONFIGURATIONDIALOG_H
