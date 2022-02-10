#include "serwidget.h"
#include"listen.h"
#include"mytcpserver.h"

SerWidget::SerWidget(QWidget *parent) : QWidget(parent),ui(new Ui::serwidget)//
{
    extern const int WINDOW_WIDTH;//窗口总长
    extern const int WINDOW_HEIGHT;//窗口总高

    this->setParent(parent);
    ui->setupUi(this);
    font.setFamily("Microsoft YaHei");
    font.setPointSize(8);
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT+100);
    this->setFont(font);
    //设置字体

    qDebug()<<"打开了服务器端";

    /*QLabel* cli_status=new QLabel;
    cli_status->setText("正在连接中……");
    ui->statusbar->addWidget(cli_status);*/

    Initdata();

    QThread *ListenThread=new QThread;
    listen *listener=new listen;
    listener->moveToThread(ListenThread);
    ListenThread->start();
    listener->beginListen();

    connect(listener->listenServer,&myTCPServer::newDescription,this,[=](qintptr sock)
    {
        QThread *TalkThread=new QThread;
        talk *talker=new talk(sock);
        talkers.append(talker);
        if(!IP_IDs.contains(talker->AskIP()))
        {
            IP_IDs.insert(talker->AskIP(),++connectedNum);
        }
        talker->moveToThread(TalkThread);
        TalkThread->start();
        talker->send("Oh",IP_IDs.value(talker->AskIP()));

        if(talkers.length()>=2)
        {
            broadcast(QString("begin"),QString("OK"));
        }

        connect(talker,&talk::recved,this,[=](cli_data cliData)
        {
            int player=IP_IDs.value(talker->AskIP());
            updateData(player,cliData);
            if(cliData.ops1==1)
            {
                attack(player,Status.dir1[player]);
            }
            judge_win();
            update();

            broadcast(QString("data"),Status);
        });

        connect(talker,&talk::losscon,this,[=]()
        {
            talkers.removeOne(talker);

        });
    });


}

void SerWidget::Initdata()
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

    update();
}
void SerWidget::dowhenWin(int player)
{
    QString str1=QString::number(player);
    QString str2;
    str1=str1+"号赢了!";
}
void SerWidget::dowhenWin(int player1,int player2)
{
    QString str1;
    QString str2;
    //str1=str1+"号赢了!";
    str1="都输了";
    str2="你们都输了，又称双赢！";
}
void SerWidget::judge_win()
{
    if(Status.own1[1]<=0&&Status.own1[2]>0) dowhenWin(2);
    else if(Status.own1[2]<=0&&Status.own1[1]>0) dowhenWin(1);
    else if(Status.own1[1]<0&&Status.own1[2]<0) dowhenWin(1,2);
}


void SerWidget::paintEvent(QPaintEvent *e)
{
    extern const int Row;//行数
    extern const int Column;//列数
    extern const int Width;//每个格子的像素宽度（好像不同的还不一样）
    extern const int hight;//每个格子的像素高度
    extern const int goods;
    extern const int PlayerNum;

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
        //int Myrol=own[1][point]/5,Myleft=own[1][point]%5;
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
        //int Myrol=own[2][point]/5,Myleft=own[2][point]%5;
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
void SerWidget::keyPressEvent(QKeyEvent *event)
{
    int temp=event->key();
    switch (temp) {
    case Qt::Key_W:Move(1,1);break;
    case Qt::Key_S:Move(1,2);break;
    case Qt::Key_A:Move(1,3);break;
    case Qt::Key_D:Move(1,4);break;
    case Qt::Key_Q:
        {
            attack(1,Status.dir1[1]);
            break;
        }
    case Qt::Key_Up:Move(2,1);break;
    case Qt::Key_Down:Move(2,2);break;
    case Qt::Key_Left:Move(2,3);break;
    case Qt::Key_Right:Move(2,4);break;
    case Qt::Key_Slash:
        {
        attack(2,Status.dir1[2]);
        break;
        }
    }
    judge_win();
    update();
}
int SerWidget::judge(int x,int y)
{
    extern const int Row;//行数
    extern const int Column;//列数

    if(x<=0||x>=Row+1) return 0;
    if(y<=0||y>=Column+1) return 0;
    return 1;
}
void SerWidget::Move(int people, int direction)
{
    extern int route[][3];

    int xx,yy;
    if(people==1)
    {
        Status.dir1[1]=direction;
        xx=Status.x1[1]+route[direction][1];
        yy=Status.y1[1]+route[direction][2];
        if(judge(xx,yy)==1)//没走到墙上
        {
            if(xx!=Status.x1[2]||yy!=Status.y1[2])//没走到对方身上
            {
                if(Status.data1[xx][yy]==12)
                {
                    //own[1][1]--;
                    Status.own1[1]--;
                }
                else if(Status.data1[xx][yy]==1)
                {

                }
                else
                {
                    Status.data1[Status.x1[1]][Status.y1[1]]=-1;//表示空气，不输出内容(玩家走到x，y了)
                    Status.x1[1]=xx;
                    Status.y1[1]=yy;
                    Status.data1[xx][yy]=1;
                }
            }
            else
            {
                Status.dir1[1]=direction;
            }
        }
    }
    else
    {
        Status.dir1[2]=direction;
        xx=Status.x1[2]+route[direction][1];
        yy=Status.y1[2]+route[direction][2];
        if(judge(xx,yy)==1)
            {
            if(xx!=Status.x1[1]||yy!=Status.y1[1])//没走到对方身上
            {
                if(Status.data1[xx][yy]==11)
                {
                    //own[2][1]--;
                    Status.own1[2]--;
                }
                else if(Status.data1[xx][yy]==12)
                {

                }
                else
                {
                    Status.data1[Status.x1[2]][Status.y1[2]]=-1;//表示空气，不输出内容
                    Status.x1[2]=xx;
                    Status.y1[2]=yy;
                    Status.data1[xx][yy]=2;
                }
            }
            else
            {
                Status.dir1[2]=direction;
            }
        }
    }
}
void SerWidget::attack(int people, int direction)
{
    extern int route[][3];

    int x_attack[4],y_attack[4],enemy=0,deal_number=0;//deal_number表示在该方向上，需要把拳风消失后几格的值改为空气
    if(people==1)
        {
            x_attack[1]=Status.x1[1]+route[direction][1];
            y_attack[1]=Status.y1[1]+route[direction][2];
            enemy=2;
        }
        else {
            x_attack[1]=Status.x1[2]+route[direction][1];
            y_attack[1]=Status.y1[2]+route[direction][2];
            enemy=1;
        }
        x_attack[2]=x_attack[1]+route[direction][1];
        y_attack[2]=y_attack[1]+route[direction][2];
        x_attack[3]=x_attack[2]+route[direction][1];
        y_attack[3]=y_attack[2]+route[direction][2];
        {
            if(!judge(x_attack[2],y_attack[2])&&!judge(x_attack[1],y_attack[1]))
            {
            //不处理
            return ;
            }
            if(!judge(x_attack[2],y_attack[2]))
            {
                if(Status.data1[x_attack[1]][y_attack[1]]==-1)
                {
                    Status.data1[x_attack[1]][y_attack[1]]=people+10;//墙前面没人(people+10表示拳)
                deal_number=1;
            }
            else
                //own[enemy][1]--;
                Status.own1[enemy]--;
            }
            else if(Status.data1[x_attack[2]][y_attack[2]]==enemy)
            {
                Status.data1[x_attack[1]][y_attack[1]]=people+10;
                if(!judge(x_attack[3],y_attack[3]))
                {
                    //own[enemy][1]--;
                    Status.own1[enemy]--;
                    deal_number=1;
                }
                else
                {
                    //own[enemy][1]--;
                    Status.own1[enemy]--;
                    //data[x[0]][y[0]]=-1;
                    if(people==1)
                    {
                        Status.x1[2]=x_attack[3];
                        Status.y1[2]=y_attack[3];
                    }
                    else
                    {
                        Status.x1[1]=x_attack[3];
                        Status.y1[1]=y_attack[3];
                    }
                    Status.data1[x_attack[3]][y_attack[3]]=enemy;
                    Status.data1[x_attack[2]][y_attack[2]]=people+10;
                    deal_number=2;
                }
            }
            else if(Status.data1[x_attack[2]][y_attack[2]]==-1)
            {
                if(Status.data1[x_attack[1]][y_attack[1]]==enemy)
                {
                    //own[enemy][1]--;
                    Status.own1[enemy]--;
                    if(Status.data1[x_attack[3]][y_attack[3]]==-1)
                    {
                        Status.data1[x_attack[3]][y_attack[3]]=enemy;
                        if(people==1)
                        {
                            Status.x1[2]=x_attack[3];
                            Status.y1[2]=y_attack[3];
                        }
                        else
                        {
                            Status.x1[1]=x_attack[3];
                            Status.y1[1]=y_attack[3];
                        }
                    }
                    else if(Status.data1[x_attack[3]][y_attack[3]]==100)
                    {
                        Status.data1[x_attack[2]][y_attack[2]]=enemy;
                        if(people==1)
                        {
                            Status.x1[2]=x_attack[2];
                            Status.y1[2]=y_attack[2];
                        }
                        else
                        {
                            Status.x1[1]=x_attack[2];
                            Status.y1[1]=y_attack[2];
                        }
                    }
                }
                if(Status.data1[x_attack[3]][y_attack[3]]!=100)
                {
                    Status.data1[x_attack[1]][y_attack[1]]=Status.data1[x_attack[2]][y_attack[2]]=people+10;
                    deal_number=2;
                }
                else
                {
                    Status.data1[x_attack[1]][y_attack[1]]=people+10;
                    deal_number=1;
                }
            }
        }
        if(deal_number==1)
        {
        QTimer::singleShot(100,this,[=]()
            {
            Status.data1[x_attack[1]][y_attack[1]]=-1;
            update();
            broadcast("data",Status);
            }//延时100ms才消失拳
        );


    }

    else if(deal_number==2)
    {
        QTimer::singleShot(100,this,[=]()
            {
            Status.data1[x_attack[1]][y_attack[1]]=-1;
            Status.data1[x_attack[2]][y_attack[2]]=-1;
            update();
            broadcast("data",Status);
            }
        );
    }
    else
    {
        update();
        broadcast("data",Status);
    }
}

void SerWidget::updateData(int player,cli_data player_data)
{
    //own[player][1]=player_data.own1;
    Status.own1[player]=player_data.own1;
    Status.dir1[player]=player_data.dir1;
    Status.x1[player]=player_data.x1,Status.y1[player]=player_data.y1;
}

template<class T>
void SerWidget::broadcast(QString type,T text)
{
    if(type=="data")
    {
        QListIterator<talk*> i(talkers);
        for(;i.hasNext();)
        {
            i.next()->send(Status);
        }
    }
    else if(type=="begin")
    {
        QListIterator<talk*> i(talkers);
        for(;i.hasNext();)
        {
            i.next()->send(type,QString("OK"));
        }
    }
}
