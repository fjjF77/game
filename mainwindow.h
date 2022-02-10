#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QPainter>
#include<QFont>
#include<QFontMetrics>
#include<QString>
#include<QPushButton>

extern const int Row;//行数
extern const int Column;//列数
extern const int Width;//每个格子的像素宽度（好像不同的还不一样）
extern const int hight;//每个格子的像素高度
extern const int WINDOW_WIDTH;//窗口总长
extern const int WINDOW_HEIGHT;//窗口总高
extern const int goods;
extern const int PlayerNum;
//int data[Row+2][Column+2];//0和Row+1/Column+1处均为墙（墙为100）
//data表示当前格子的状态，-1：空气，1：玩家1，2：玩家2，……，11：玩家1拳，12：玩家2拳，100：墙
//int own[PlayerNum+1][goods+1];//own[i][j]，i=1时代表玩家1，2时代表玩家2；j=1时代表血量
//int dir[PlayerNum+1];//代表该玩家走到某一个格子时的面向方向
//int x[PlayerNum+1],y[PlayerNum+1];//x1,y1代表玩家1坐标，x2，y2代表玩家2坐标
extern int route[5][3];//代表超上下左右走时xy的坐标改变量

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);

private:
    Ui::MainWindow *ui;
    QFont font;
};

#endif // MAINWINDOW_H
