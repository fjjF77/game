#ifndef CLIWIDGET_H
#define CLIWIDGET_H

#include <QWidget>
#include<QDebug>
#include<QPainter>
#include<QFont>
#include<QFontMetrics>
#include<QColor>
#include<QKeyEvent>
#include<QTime>
#include<QTimer>
#include<QMessageBox>
#include<QTimerEvent>
#include<QString>
#include <QThread>
#include<QMap>
#include"datas.h"
#include"cli_communicate.h"


class cliwidget : public QWidget
{
    Q_OBJECT
public:
    explicit cliwidget(QWidget *parent = nullptr);
    void Initdata();
    void Move(int direction);//1向上,2向下,3向左,4向右（move控制玩家移动）
    void attack(int direction);//控制玩家攻击
    void judge_win();
    void dowhenWin(int x);
    void dowhenWin(int x,int y);
    int judge(int x,int y);//0表示此位置不能走，1表示此位置能走(判断边界)
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *event);

signals:

private:
    void updateData(int player,ser_data game_data);
    int MyNum;
    cli_communicate *cli_1;
    cli_data myStatus;
    ser_data Status;
    QFont font;
    QTimer *timer;
};

#endif // CLIWIDGET_H
