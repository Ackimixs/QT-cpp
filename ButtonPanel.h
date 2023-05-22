#ifndef TP2_BUTTONPANEL_H
#define TP2_BUTTONPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class ButtonPanel : public QWidget {
    Q_OBJECT
public:
    ButtonPanel();

private:
    QPushButton* configure;
    QPushButton* connect;
    QPushButton* disconnect;

    QHBoxLayout* layout;

};


#endif //TP2_BUTTONPANEL_H
