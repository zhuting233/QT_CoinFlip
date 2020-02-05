#include "mypushbutton.h"
#include<QDebug>
#include<QBitmap>
#include<QPropertyAnimation>

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    normalImgPath = normalImg;
    pressedImgPath = pressImg;
    QPixmap pixmap;
    bool ret = pixmap.load(normalImgPath);
    if(!ret)
    {
        qDebug()<<normalImg<<"加载图片失败!";
    }
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    //过滤透明区域
    this->setMask(pixmap.mask());

}

void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation *animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}

void MyPushButton::zoom2()
{
    QPropertyAnimation* animation1 = new QPropertyAnimation(this,"geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pressedImgPath!="")
    {
        QPixmap pixmap;
        bool ret = pixmap.load(pressedImgPath);
        if(!ret)
        {
            qDebug()<<pressedImgPath<<" 加载图片失败";
        }
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    return QPushButton::mousePressEvent(e);
}


void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath!="")
    {
        QPixmap pixmap;
        bool ret = pixmap.load(normalImgPath);
        if(!ret)
        {
            qDebug()<<normalImgPath<<" 加载图片失败";
        }
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}

