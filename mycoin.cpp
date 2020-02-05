#include "mycoin.h"
#include<QDebug>
#include<QTimer>

MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
{

}

MyCoin::MyCoin(QString butImg):min(1),max(8),isAnimation(false),isWin(false)
{
    QPixmap pixmap;
    bool ret = pixmap.load(butImg);
    if(!ret)
    {
        qDebug()<<butImg<<"加载图片失败";
    }
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{Border:0px};");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/Coin000%1.png").arg(min++);
        pixmap.load(str);
        setFixedSize(pixmap.width(),pixmap.height());
        setStyleSheet("QPushButton{border:0px;}");
        setIcon(pixmap);
        setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(min>max){
            this->min = 1;
            timer1->stop();
            isAnimation = false;
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/Coin000%1.png").arg(max--);
        pixmap.load(str);
        setFixedSize(pixmap.width(),pixmap.height());
        setStyleSheet("QPushButton{border:0px;}");
        setIcon(pixmap);
        setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(max<min){
            this->max = 8;
            timer2->stop();
            isAnimation = false;
        }
    });
}

void MyCoin::changeFlag()
{
    if(flag){
        timer1->start(30);
        isAnimation = true;
        this->flag = false;
    }else{
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }

}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(isAnimation || isWin){
        return;
    }else{
        return QPushButton::mousePressEvent(e);
    }
}


