#ifndef SERWIDGET_H
#define SERWIDGET_H

#include <QWidget>
#include<QDebug>
#include<QLabel>
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
#include"talk.h"
#include"datas.h"
#include "ui_serwidget.h"



QT_BEGIN_NAMESPACE
namespace Ui { class serwidget; }
QT_END_NAMESPACE

class SerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerWidget(QWidget *parent = nullptr);
    void Initdata();
    void Move(int people,int direction);//1向上,2向下,3向左,4向右（move控制玩家移动）
    void attack(int people,int direction);//控制玩家攻击
    void judge_win();
    void dowhenWin(int x);
    void dowhenWin(int x,int y);
    int judge(int x,int y);//0表示此位置不能走，1表示此位置能走(判断边界)
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::serwidget *ui;
    void updateData(int player,cli_data player_data);
    template<class T>
    void broadcast(QString type,T text);
    QMap<QString,int> IP_IDs;
    QList<talk*> talkers;
    ser_data Status;
    int connectedNum=0;
    QFont font;
    QTimer *timer;
};
#endif  // SERWIDGET_H
