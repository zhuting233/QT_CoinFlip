#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<mycoin.h>

class PlayScene : public QMainWindow
{
    Q_OBJECT
    int levelIndex;
    int gameArray[4][4];
    bool isWin;
public:
    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int index);
    void paintEvent(QPaintEvent *event);
    MyCoin * coinBtn[4][4];
signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
