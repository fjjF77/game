#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    font.setFamily("Microsoft YaHei");
    font.setPointSize(8);
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT+100);
    this->setFont(font);
    //设置字体

    Initdata();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::Initdata()
{
    int i,j;
    route[1][1]=route[2][1]=0;
    route[2][2]=route[4][1]=1;
    route[1][2]=route[3][1]=-1;
    route[3][2]=route[4][2]=0;
    dir[1]=4;
    dir[2]=3;
    own[1][1]=own[2][1]=11;
    x1=2;
    y1=(Row+2)/2;
    x2=Column-1;
    y2=y1;
    for(i=0;i<=Row+1;i++)
    {
        for(j=0;j<=Column+1;j++)
        {
            data[i][j]=-1;
        }
    }
    for(i=0;i<=Column+1;i++)
    {
        data[0][i]=100;
        data[Row+1][i]=100;
    }
    for(i=1;i<=Row;i++)
    {
        data[i][0]=100;
        data[i][Column+1]=100;
    }

    data[x1][y1]=1;
    data[x2][y2]=2;
}
void Widget::dowhenWin(int x)
{
    QString str1=QString::number(x);
    QString str2;
    str1=str1+"号赢了!";
    str2=str1+"!!是否继续游戏";
    if(QMessageBox::question(this,str1,str2,QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)
            ==QMessageBox::Ok){
        Initdata();
        update();
    }
    else{
        this->close();
    }

}
void Widget::dowhenWin(int x,int y)
{
    QString str1;
    QString str2;
    //str1=str1+"号赢了!";
    str1="都输了";
    str2="你们都输了，又称双赢！";
    str2=str1+"!!是否继续游戏";
    if(QMessageBox::question(this,str1,str2,QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)
            ==QMessageBox::Ok){
        Initdata();
        update();
    }
    else{
        this->close();
    }

}
void Widget::judge_win()
{
    if(own[1][1]<=0&&own[2][1]>0) dowhenWin(2);
    else if(own[2][1]<=0&&own[1][1]>0) dowhenWin(1);
    else if(own[1][1]<0&&own[2][1]<0) dowhenWin(1,2);
}


void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setFont(font);
    QFontMetrics metrics=painter.fontMetrics();
    int i;
    int point=1,x,y,base,cnt,record;
    base=metrics.ascent();
    for(i=0;i<=Row+1;i++)
    {
        x=i*Width;
        for(int j=0;j<=Column+1;j++)
        {

            y=base+j*hight;
            switch(data[i][j])
            {
                case 100:
            {
                painter.setPen(QColor(Qt::black));
                painter.drawText(x,y,"墙");
                break;
            }
                case 1:
            {
                painter.setPen(QColor(Qt::red));
                painter.drawText(x,y,"我");
                break;//红色，一号玩家
            }
                case 2:
            {
                painter.setPen(QColor(Qt::green));
                painter.drawText(x,y,"我");
                break;//绿色，二号玩家
            }
            case 3:{
                painter.setPen(QColor(Qt::red));
                painter.drawText(x,y,QChar(30));
                break;
            }//红色，一号玩家,显示上的箭头
            case 4:{
                painter.setPen(QColor(Qt::red));
                painter.drawText(x,y,QChar(31));
                break;
            }//红色，一号玩家,显示下的箭头
            case 5:{
                painter.setPen(QColor(Qt::red));
                painter.drawText(x,y,QChar(17));
                break;
            }//红色，一号玩家,显示左的箭头
            case 6:{
                painter.setPen(QColor(Qt::red));
                painter.drawText(x,y,QChar(17));
                break;
            }//红色，一号玩家,显示右的箭头
            case 7:{
                painter.setPen(QColor(Qt::green));
                painter.drawText(x,y,QChar(30));
                break;
            }//绿色，二号玩家,显示上的箭头
            case 8:{
                painter.setPen(QColor(Qt::green));
                painter.drawText(x,y,QChar(31));
                break;
            }//绿色，二号玩家,显示下的箭头
            case 9:{
                painter.setPen(QColor(Qt::green));
                painter.drawText(x,y,QChar(17));
                break;
            }//绿色，二号玩家,显示左的箭头
            case 10:{
                painter.setPen(QColor(Qt::green));
                painter.drawText(x,y,QChar(17));
                break;
            }//绿色，二号玩家,显示右的箭头
                case 11:
            {
                painter.setPen(QColor(Qt::red));
                painter.drawText(x,y,"拳");
                break;//红色，一号玩家
            }
                case 12:
            {
                painter.setPen(QColor(Qt::green));
                painter.drawText(x,y,"拳");
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
        int Myrol=own[1][point]/5,Myleft=own[1][point]%5;

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
        int Myrol=own[2][point]/5,Myleft=own[2][point]%5;
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
void Widget::keyPressEvent(QKeyEvent *event)
{
    int temp=event->key();
    switch (temp) {
    case Qt::Key_W:Move(1,1);break;
    case Qt::Key_S:Move(1,2);break;
    case Qt::Key_A:Move(1,3);break;
    case Qt::Key_D:Move(1,4);break;
    case Qt::Key_Q:
        {
            attack(1,dir[1]);
            break;
        }
    case Qt::Key_Up:Move(2,1);break;
    case Qt::Key_Down:Move(2,2);break;
    case Qt::Key_Left:Move(2,3);break;
    case Qt::Key_Right:Move(2,4);break;
    case Qt::Key_Slash:
        {
        attack(2,dir[2]);
        break;
        }
    }
    judge_win();
    update();
}
int Widget::judge(int x,int y)
{
    if(x<=0||x>=Row+1) return 0;
    if(y<=0||y>=Column+1) return 0;
    return 1;
}
void Widget::Move(int people, int direction)
{
    int x,y;
    if(people==1)
    {
        dir[1]=direction;
        x=x1+route[direction][1];
        y=y1+route[direction][2];
        if(judge(x,y)==1)//没走到墙上
            {
            if(x!=x2||y!=y2)//没走到对方身上
            {
                if(data[x][y]==12)
                {
                    own[1][1]--;
                }
                else if(data[x][y]==1)
                {

                }
                else
                {
                    data[x1][y1]=-1;//表示空气，不输出内容(玩家走到x，y了)
                    x1=x;
                    y1=y;
                    data[x][y]=1;
                }
            }
            else
            {
                dir[1]=direction;
            }
        }
    }
    else
    {
        dir[2]=direction;
        x=x2+route[direction][1];
        y=y2+route[direction][2];
        if(judge(x,y)==1)
            {
            if(x!=x1||y!=y1)//没走到对方身上
            {
                if(data[x][y]==11)
                {
                    own[2][1]--;
                }
                else if(data[x][y]==12)
                {

                }
                else
                {
                    data[x2][y2]=-1;//表示空气，不输出内容
                    x2=x;
                    y2=y;
                    data[x][y]=2;
                }
            }
            else
            {
                dir[2]=direction;
            }
        }
    }
}
void Widget::attack(int people, int direction)
{
    int x[4],y[4],enemy=0,deal_number=0;//deal_number表示在该方向上，需要把拳风消失后几格的值改为空气
    if(people==1)
    {
        x[1]=x1+route[direction][1];
        y[1]=y1+route[direction][2];
        enemy=2;
    }
    else {
        x[1]=x2+route[direction][1];
        y[1]=y2+route[direction][2];
        enemy=1;
    }
    x[2]=x[1]+route[direction][1];
    y[2]=y[1]+route[direction][2];
    x[3]=x[2]+route[direction][1];
    y[3]=y[2]+route[direction][2];
    {
        if(!judge(x[2],y[2])&&!judge(x[1],y[1]))
        {
            //不处理
            return ;
        }
        if(!judge(x[2],y[2]))
        {
            if(data[x[1]][y[1]]==-1)
            {
                data[x[1]][y[1]]=people+10;//墙前面没人(people+10表示拳)
                deal_number=1;
            }
            else
                own[enemy][1]--;
        }
        else if(data[x[2]][y[2]]==enemy)
        {
            data[x[1]][y[1]]=people+10;
            if(!judge(x[3],y[3]))
            {
                own[enemy][1]--;
                deal_number=1;
            }
            else
            {
                own[enemy][1]--;
                //data[x[0]][y[0]]=-1;
                if(people==1)
                {
                    x2=x[3];
                    y2=y[3];
                }
                else
                {
                    x1=x[3];
                    y1=y[3];
                }
                data[x[3]][y[3]]=enemy;
                data[x[2]][y[2]]=people+10;
                deal_number=2;
            }
        }
        else if(data[x[2]][y[2]]==-1)
        {
            if(data[x[1]][y[1]]==enemy)
            {
                own[enemy][1]--;
                if(data[x[3]][y[3]]==-1)
                {
                    data[x[3]][y[3]]=enemy;
                    if(people==1)
                    {
                        x2=x[3];
                        y2=y[3];
                    }
                    else
                    {
                        x1=x[3];
                        y1=y[3];
                    }
                }
                else if(data[x[3]][y[3]]==100)
                {
                    data[x[2]][y[2]]=enemy;
                    if(people==1)
                    {
                        x2=x[2];
                        y2=y[2];
                    }
                    else
                    {
                        x1=x[2];
                        y1=y[2];
                    }
                }
            }
            if(data[x[3]][y[3]]!=100)
            {
                data[x[1]][y[1]]=data[x[2]][y[2]]=people+10;
                deal_number=2;
            }
            else
            {
                data[x[1]][y[1]]=people+10;
                deal_number=1;
            }
        }
    }
    if(deal_number==1)
        {
        QTimer::singleShot(100,this,[=]()
            {
            data[x[1]][y[1]]=-1;
            update();
            }//延时100ms才消失拳
        );


    }

    else if(deal_number==2)
    {
        QTimer::singleShot(100,this,[=]()
            {
            data[x[1]][y[1]]=-1;
            data[x[2]][y[2]]=-1;
            update();
            }
        );
    }
    else
    {
        update();
    }
}
