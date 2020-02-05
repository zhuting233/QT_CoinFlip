#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include<mypushbutton.h>
#include<playscene.h>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
    MyPushButton *closeBtn;
    PlayScene *pScene;
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

signals:
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
