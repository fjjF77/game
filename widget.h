#ifndef WIDGET_H
#define WIDGET_H

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

const int Row=30;//行数
const int Column=30;//列数
const int Width=16;//每个格子的像素宽度（好像不同的还不一样）
const int hight=21;//每个格子的像素高度
const int WINDOW_WIDTH = Row * Width+140;//窗口总长
const int WINDOW_HEIGHT = Column * hight;//窗口总高
const int goods=1;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
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
    Ui::Widget *ui;
    int data[Row+2][Column+2];//0和Row+1/Column+1处均为墙（墙为100）
    //data表示当前格子的状态，-1：空气，1：玩家1，2：玩家2，……，11：玩家1拳，12：玩家2拳，100：墙
    int own[3][goods+1];//own[i][j]，i=1时代表玩家1，2时代表玩家2；j=1时代表血量
    int dir[3];//代表该玩家走到某一个格子时的面向方向
    int x1,x2,y1,y2;//x1,y1代表玩家1坐标，x2，y2代表玩家2坐标
    int route[5][3];//代表超上下左右走时xy的坐标改变量
    QFont font;
    QTimer *timer;
};
#endif // WIDGET_H
