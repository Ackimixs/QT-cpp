#ifndef TP1_WINDOW_H
#define TP1_WINDOW_H

#include <QWidget>
#include <QPushButton>

class Window : public QWidget {
    Q_OBJECT
public:
    Window(QWidget* parent = nullptr);

private:
    QPushButton* button;
};


#endif //TP1_WINDOW_H
