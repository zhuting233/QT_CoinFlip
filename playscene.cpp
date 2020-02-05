#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QPixmap>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include<mycoin.h>
#include<dataconfig.h>
#include<QDebug>
#include<QPropertyAnimation>
#include<QSound>

PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

}

PlayScene::PlayScene(int index):isWin(false)
{
    this->levelIndex = index;
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/Coin0001.png"));
    this->setWindowTitle("翻金币");
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu *startMenu = bar->addMenu("开始");
    QAction *quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSound *bacSound = new QSound(":/BackButtonSound.wav",this);
    QSound *flipSound = new QSound(":/ConFlipSound.wav",this);
    QSound *winSound = new QSound(":/LevelWinSound.wav",this);

    MyPushButton *closeBtn = new MyPushButton(":/BackButton.png",":/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()-closeBtn->width(),this->height()-closeBtn->height());
    connect(closeBtn,&MyPushButton::clicked,[=](){
        bacSound->play();
        QTimer::singleShot(400,this,[=](){
            this->hide();
            emit this->chooseSceneBack();
        });
    });

    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str = QString("Leavel: %1").arg(this->levelIndex);
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-50,120,50));

    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            QLabel* label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);

//            MyCoin *coin = new MyCoin(":/Coin0001.png");
//            coin->setParent(this);
//            coin->move(59+i*50,204+j*50);

        }
    }
    dataConfig config;
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++)        {
            gameArray[i][j] = config.mData[this->levelIndex][i][j];
            QString img;
            if(gameArray[i][j]==1){
                img = ":/Coin0001.png";
            }else{
                img = ":/Coin0008.png";
            }

            MyCoin *coin = new MyCoin(img);
            coinBtn[i][j] = coin;
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX = i;
            coin->posY = j;
            coin->flag = gameArray[i][j];

            connect(coin,&MyCoin::clicked,[=](){
                flipSound->play();
                coin->changeFlag();

                for (int i=0;i<4;i++)
                    for(int j=0;j<4;j++)
                        coinBtn[i][j]->isWin = true;

                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;
                QTimer::singleShot(300, this,[=](){
                    if(coin->posX+1 <=3)
                    {
                      coinBtn[coin->posX+1][coin->posY]->changeFlag();
                      gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posX-1>=0)
                    {
                      coinBtn[coin->posX-1][coin->posY]->changeFlag();
                      gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY+1<=3)
                    {
                     coinBtn[coin->posX][coin->posY+1]->changeFlag();
                     gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY-1>=0)
                    {
                     coinBtn[coin->posX][coin->posY-1]->changeFlag();
                     gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }

                    for (int i=0;i<4;i++)
                        for(int j=0;j<4;j++)
                            coinBtn[i][j]->isWin = false;

                    isWin = true;
                    for (int i=0;i<4;i++) {
                        for(int j=0;j<4;j++){
                //            qDebug()<<coinBtn[i][j]->isWin;
                            if(coinBtn[i][j]->flag == false){
                                isWin = false;
                                break;
                            }
                        }
                }
                    if(isWin){
                        winSound->play();
                        qDebug()<<"胜利";
                        for (int i=0;i<4;i++)
                            for(int j=0;j<4;j++)
                                coinBtn[i][j]->isWin = true;
                        QPropertyAnimation *animation1 = new QPropertyAnimation(winLabel,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+144,winLabel->width(),winLabel->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();
                    }
                //    for (int i=0;i<4;i++)
                //        for(int j=0;j<4;j++)
                //            qDebug()<<coinBtn[i][j]->isWin;

                });

            });
        }
    }

}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}
