#include "cliwidget.h"

cliwidget::cliwidget(QWidget *parent) : QWidget(parent)
{
    extern const int WINDOW_WIDTH;//窗口总长
    extern const int WINDOW_HEIGHT;//窗口总高
    font.setFamily("Microsoft YaHei");
    font.setPointSize(8);
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT+100);
    this->setFont(font);
    //设置字体
    this->setParent(parent);
    qDebug()<<"打开了客户端";

    QThread *Thread1=new QThread;
    cli_1=new cli_communicate;
    cli_1->moveToThread(Thread1);
    Thread1->start();

    connect(cli_1,&cli_communicate::connected,this,[=](int playerNum)
    {
        qDebug()<<"已连接到服务器";
        MyNum=playerNum;
        Initdata();
        update();
    });

    connect(cli_1,&cli_communicate::recv,this,[=](ser_data dataAll)
    {
        Status=dataAll;
        myStatus.change(MyNum,dataAll);
    });

    connect(cli_1,&cli_communicate::disconnected,this,[=]()
    {

    });
}

void cliwidget::Initdata()
{
    extern const int Row;//行数
    extern const int Column;//列数

    int i,j;
    Status.dir1[1]=4;
    Status.dir1[2]=3;
    //own[1][1]=own[2][1]=11;
    Status.own1[1]=Status.own1[2]=11;
    Status.x1[1]=2;
    Status.y1[1]=(Row+2)/2;
    Status.x1[2]=Column-1;
    Status.y1[2]=Status.y1[1];
    for(i=0;i<=Row+1;i++)
    {
        for(j=0;j<=Column+1;j++)
        {
            Status.data1[i][j]=-1;
        }
    }
    for(i=0;i<=Column+1;i++)
    {
        Status.data1[0][i]=100;
        Status.data1[Row+1][i]=100;
    }
    for(i=1;i<=Row;i++)
    {
        Status.data1[i][0]=100;
        Status.data1[i][Column+1]=100;
    }

    Status.data1[Status.x1[1]][Status.y1[1]]=1;
    Status.data1[Status.x1[2]][Status.y1[2]]=2;
}
void cliwidget::dowhenWin(int wonNum)
{
    QString str1,str2;
    if(MyNum==wonNum)
    {
        str1="恭喜你！你赢了！";
    }
    else
    {
        str1=QString::number(wonNum,10)+"号赢了!";
    }
    str2=str1+"!!是否继续游戏";
    if(QMessageBox::question(this,str1,str2,QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)
            ==QMessageBox::Ok){
        Initdata();
        cli_1->send("goon");
        update();
    }
    else{
        this->close();
    }

}

void cliwidget::paintEvent(QPaintEvent *e)
{
    extern const int Row;//行数
    extern const int Column;//列数
    extern const int Width;//每个格子的像素宽度（好像不同的还不一样）
    extern const int hight;//每个格子的像素高度
    extern const int goods;

    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setFont(font);
    QFontMetrics metrics=painter.fontMetrics();
    int i;
    int point=1,xx,yy,base,cnt,record;
    base=metrics.ascent();
    for(i=0;i<=Row+1;i++)
    {
        xx=i*Width;
        for(int j=0;j<=Column+1;j++)
        {

            yy=base+j*hight;
            switch(Status.data1[i][j])
            {
                case 100:
            {
                painter.setPen(QColor(Qt::black));
                painter.drawText(xx,yy,"墙");
                break;
            }
                case 1:
            {
                painter.setPen(QColor(Qt::red));
                painter.drawText(xx,yy,"我");
                break;//红色，一号玩家
            }
                case 2:
            {
                painter.setPen(QColor(Qt::green));
                painter.drawText(xx,yy,"我");
                break;//绿色，二号玩家
            }
            case 3:{
                painter.setPen(QColor(Qt::red));
                painter.drawText(xx,yy,QChar(30));
                break;
            }//红色，一号玩家,显示上的箭头
            case 4:{
                painter.setPen(QColor(Qt::red));
                painter.drawText(xx,yy,QChar(31));
                break;
            }//红色，一号玩家,显示下的箭头
            case 5:{
                painter.setPen(QColor(Qt::red));
                painter.drawText(xx,yy,QChar(17));
                break;
            }//红色，一号玩家,显示左的箭头
            case 6:{
                painter.setPen(QColor(Qt::red));
                painter.drawText(xx,yy,QChar(17));
                break;
            }//红色，一号玩家,显示右的箭头
            case 7:{
                painter.setPen(QColor(Qt::green));
                painter.drawText(xx,yy,QChar(30));
                break;
            }//绿色，二号玩家,显示上的箭头
            case 8:{
                painter.setPen(QColor(Qt::green));
                painter.drawText(xx,yy,QChar(31));
                break;
            }//绿色，二号玩家,显示下的箭头
            case 9:{
                painter.setPen(QColor(Qt::green));
                painter.drawText(xx,yy,QChar(17));
                break;
            }//绿色，二号玩家,显示左的箭头
            case 10:{
                painter.setPen(QColor(Qt::green));
                painter.drawText(xx,yy,QChar(17));
                break;
            }//绿色，二号玩家,显示右的箭头
                case 11:
            {
                painter.setPen(QColor(Qt::red));
                painter.drawText(xx,yy,"拳");
                break;//红色，一号玩家
            }
                case 12:
            {
                painter.setPen(QColor(Qt::green));
                painter.drawText(xx,yy,"拳");
                break;//绿色，二号玩家
            }
            }
        }
    }
    //接下来是画旁边的血量等
    cnt=0;
    painter.setPen(QColor(Qt::red));
    painter.drawText((Row+1)*Width+20,base,"1号");
    while(point<=goods)
    {
        int Myrol=Status.own1[1]/5,Myleft=Status.own1[1]%5;

        switch (point) {
        case 1:{
            for(int j=1;j<=Myrol;j++)
            {
                cnt++;
                painter.drawText((Row+1)*Width+20,base+cnt*hight,"血血血血血");
            }
            if(Myleft)
            {
                cnt++;
                for(int j=1;j<=Myleft;j++)
                {
                    painter.drawText((Row+1)*Width+20+(j-1)*Width,base+cnt*hight,"血");
                }
            }
        }
        }//为方便以后扩展道具
        point++;
    }
    cnt+=2;
    painter.setPen(QColor(Qt::green));
    painter.drawText((Row+1)*Width+20,base+cnt*hight,"2号");
    //i+=2;
    point=1;
    while(point<=goods)
    {
        int Myrol=Status.own1[2]/5,Myleft=Status.own1[2]%5;
        switch (point) {
        case 1:{
            for(int j=1;j<=Myrol;j++)
            {
                cnt++;
                painter.drawText((Row+1)*Width+20,base+cnt*hight,"血血血血血");
            }
            if(Myleft)
            {
                cnt++;
                for(int j=1;j<=Myleft;j++)
                {
                    painter.drawText((Row+1)*Width+20+(j-1)*Width,base+cnt*hight,"血");
                }
            }
        }
        }//为方便以后扩展道具
        point++;
    }
}
void cliwidget::keyPressEvent(QKeyEvent *event)
{
    int temp=event->key();
    switch (temp) {
    case Qt::Key_W:Move(1);break;
    case Qt::Key_S:Move(2);break;
    case Qt::Key_A:Move(3);break;
    case Qt::Key_D:Move(4);break;
    case Qt::Key_Q:
        {
            attack(myStatus.dir1);
            break;
        }
    }
}

int cliwidget::judge(int x,int y)
{
    extern const int Row;//行数
    extern const int Column;//列数

    if(x<=0||x>=Row+1) return 0;
    if(y<=0||y>=Column+1) return 0;
    return 1;
}

void cliwidget::Move(int direction)
{
    extern int route[][3];

    myStatus.change(MyNum,Status);
    int xx=myStatus.x1+route[direction][1],yy=myStatus.y1+route[direction][2];
    if(judge(xx,yy))
    {
        myStatus.dir1=direction;
        myStatus.x1+=route[direction][1];
        myStatus.y1+=route[direction][2];
        cli_1->send(myStatus);
    }
}

void cliwidget::attack(int direction)
{
    myStatus.change(MyNum,Status);
    myStatus.dir1=direction;
    myStatus.ops1=1;
    cli_1->send(myStatus);
}
