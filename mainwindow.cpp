#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"listen.h"
#include"mytcpserver.h"
#include"serwidget.h"
#include"cliwidget.h"

const int Row=30;//行数
const int Column=30;//列数
const int Width=16;//每个格子的像素宽度（好像不同的还不一样）
const int hight=21;//每个格子的像素高度
const int WINDOW_WIDTH = Row * Width+140;//窗口总长
const int WINDOW_HEIGHT = Column * hight;//窗口总高
const int goods=1;
const int PlayerNum=2;
int route[5][3]={{0,0,0},{0,0,-1},{0,0,1},{0,-1,0},{0,1,0}};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    font.setFamily("Microsoft YaHei");
    font.setPointSize(8);
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT+100);
    this->setFont(font);
    //设置字体

    connect(ui->IsSer,&QPushButton::clicked,this,[=]()
    {
        this->hide();
        qDebug()<<"主窗口被隐藏";
        SerWidget *server=new SerWidget;
        qDebug()<<"新建了一个服务器窗口指针";
        server->show();
    });

    connect(ui->IsCli,&QPushButton::clicked,this,[=]()
    {
        this->hide();
        cliwidget *client=new cliwidget;
        client->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setFont(font);
    QFontMetrics metrics=painter.fontMetrics();

}

