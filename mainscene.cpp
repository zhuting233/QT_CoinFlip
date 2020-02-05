#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include"chooselevelscene.h"
#include<QTimer>
#include<QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/Coin0001.png"));
    this->setWindowTitle("小太阳带你翻金币");

    connect(ui->actionQuit,&QAction::triggered,[=](){
       this->close();
    });

    QSound *startSound = new QSound(":/TapButtonSound.wav",this);

    MyPushButton *startBtn = new MyPushButton(":/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    chooseScene = new ChooseLevelScene;
    connect(startBtn,&QPushButton::clicked,[=](){
        chooseScene->setGeometry(this->geometry());
        startBtn->zoom1();
        startSound->play();
        startBtn->zoom2();
        QTimer::singleShot(400,this,[=](){
            this->hide();
            chooseScene->show();
        });

    });

    //监听选择场景的返回信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        this->setGeometry(chooseScene->geometry());
        this->show();
    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

MainScene::~MainScene()
{
    delete ui;
}

