#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<playscene.h>
#include<QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent),pScene(nullptr)
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/Coin0001.png"));
    this->setWindowTitle("选择关卡");

    QSound *choSound = new QSound(":/TapButtonSound.wav",this);
    QSound *bacSound = new QSound(":/BackButtonSound.wav",this);

    QMenuBar* bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu *startMenu = bar->addMenu("开始");
    QAction *quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    closeBtn = new MyPushButton(":/BackButton.png",":/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()-closeBtn->width(),this->height()-closeBtn->height());

    connect(closeBtn,&QPushButton::clicked,[=](){
        bacSound->play();
        QTimer::singleShot(400,this,[=](){
            this->hide();
            emit this->chooseSceneBack();
        });
    });

    for (int i=0;i<20;i++) {
        MyPushButton *menuBtn = new MyPushButton(":/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,130+(i/4)*70);

        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->move(25+(i%4)*70,130+(i/4)*70);
        //设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);
        connect(menuBtn,&MyPushButton::clicked,[=](){
            if(pScene==nullptr){
                choSound->play();
                this->hide();
                pScene = new PlayScene(i+1);
                pScene->setGeometry(this->geometry());
                pScene->show();

                connect(pScene,&PlayScene::chooseSceneBack,[=](){
                    this->setGeometry(pScene->geometry());
                    this->show();
                    delete pScene;
                    pScene = nullptr;
                });
            }
        });
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);



}
