#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include<QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT

public:
    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString butImg);
    int posX,posY;
    bool flag;
    QTimer *timer1;
    QTimer *timer2;
    int min, max;
    bool isAnimation;
    void changeFlag();
    void mousePressEvent(QMouseEvent *e);
    bool isWin;
signals:

};

#endif // MYCOIN_H
