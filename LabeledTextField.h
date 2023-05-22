#ifndef TP2_LABELEDTEXTFIELD_H
#define TP2_LABELEDTEXTFIELD_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>

class LabeledTextField : public QWidget {
private:
    QHBoxLayout* layout;
    QLabel* label;
    QTextEdit* textEdit;

public:
    LabeledTextField();
    void setText(QString s);
};


#endif //TP2_LABELEDTEXTFIELD_H
