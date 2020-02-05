#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
    QString normalImgPath;
    QString pressedImgPath;
public:
    explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString normalImg,QString pressImg="");
    //向下跳跃
    void zoom1();
    //向上跳跃
    void zoom2();
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
