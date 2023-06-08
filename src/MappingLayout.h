#ifndef CPP_QT_MINIPROJET_MAPPINGLAYOUT_H
#define CPP_QT_MINIPROJET_MAPPINGLAYOUT_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QString>

class MappingLayout : public QHBoxLayout {
public:
    MappingLayout(QString label);
    void setText(QString text);
    void setInputText(QString text);
    QString getText();

private:
    QLabel* mappingLabel1;
    QLineEdit* mappingLineEdit1;

};


#endif //CPP_QT_MINIPROJET_MAPPINGLAYOUT_H
