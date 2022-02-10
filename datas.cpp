#include "datas.h"
#include<QString>

cli_data::cli_data(int own,int dir,int x,int y,int ops)
{
     own1=own;
     dir1=dir;
     x1=x,y1=y;
     ops1=ops;
}

cli_data::cli_data(QString s)
{
    QStringList l=s.split("-");
    for(int i=0;i<l.size();i++)
    {
        QString str=l[i];
        int j=0;
        while(str[j].isLetter()) j++;
        QString str1=str.mid(0,j),str2=str.mid(j,-1);
        if(str1=="own") {own1=str2.toInt();}
        else if(str1=="dir") {dir1=str2.toInt();}
        else if(str1=="x") {x1=str2.toInt();}
        else if(str1=="y") {y1=str2.toInt();}
        else if(str1=="ops") {ops1=str2.toInt();}
    }
}

cli_data::cli_data()
{
    own1=0;
    dir1=0;
    x1=0,y1=0;
    ops1=0;
}

void cli_data::change(int playerNum,ser_data dataAll)
{
    own1=dataAll.own1[playerNum];
    dir1=dataAll.dir1[playerNum];
    x1=dataAll.x1[playerNum],y1=dataAll.y1[playerNum];
    ops1=0;
}

QString cli_data::toStr()
{
    QString text="";
    text=text+"-own"+QString::number(own1,10);
    text=text+"-dir"+QString::number(dir1,10);
    text=text+"-x"+QString::number(x1,10);
    text=text+"-y"+QString::number(y1,10);
    text=text+"-ops"+QString::number(ops1,10);
    return text;
}

ser_data::ser_data(int own[],int dir[],int x[],int y[],int **data)
{
    extern const int Row;
    extern const int Column;
    extern const int PlayerNum;

    dir1=new int[PlayerNum+1];
    own1=new int[PlayerNum+1];
    x1=new int[PlayerNum+1];
    y1=new int[PlayerNum+1];
    data1=new int*[Row+2];
    for(int i=0;i<=Row+1;i++)
    {
        data1[i]=new int[Column+2];
    }

    memcpy(own1,own,sizeof(own));
    memcpy(dir1,dir,sizeof(dir));
    memcpy(x1,x,sizeof(x));
    memcpy(y1,y,sizeof(y));
    //memcpy(ops1,ops,sizeof(ops));
    memcpy(data1,data,sizeof(data));
}

ser_data::ser_data(QString s)
{
    extern const int Row;
    extern const int Column;
    extern const int PlayerNum;

    dir1=new int[PlayerNum+1];
    own1=new int[PlayerNum+1];
    x1=new int[PlayerNum+1];
    y1=new int[PlayerNum+1];
    data1=new int*[Row+2];
    for(int i=0;i<=Row+1;i++)
    {
        data1[i]=new int[Column+2];
    }

    QStringList l=s.split("-");
    int num=1;
    for(int i=0;i<l.size();i++)
    {
        QString str=l[i];
        int j=0;
        while(str[j].isLetter()) j++;
        QString str1=str.mid(0,j),str2=str.mid(j,-1);
        if(str1=="own") {own1[num]=str2.toInt();}
        else if(str1=="dir") {dir1[num]=str2.toInt();}
        else if(str1=="x") {x1[num]=str2.toInt();}
        else if(str1=="y") {y1[num++]=str2.toInt();}
        //else if(str1=="ops") {ops1[num++]=str2.toInt();}
        else if(str=="data")
        {
            QStringList lstr=str2.split(",");
            int k=0;
            for(int i=1;i<=Row;i++)
            {
                for(int j=1;j<=Column;j++)
                {
                    data1[i][j]=lstr[k++].toInt();
                }
            }
        }
    }
}

ser_data::ser_data()
{
    extern const int Row;
    extern const int Column;
    extern const int PlayerNum;

    dir1=new int[PlayerNum+1];
    own1=new int[PlayerNum+1];
    x1=new int[PlayerNum+1];
    y1=new int[PlayerNum+1];
    data1=new int*[Row+2];
    for(int i=0;i<=Row+1;i++)
    {
        data1[i]=new int[Column+2];
    }
    //qDebug()<<"内存分配完毕";

    dir1[1]=4;
    dir1[2]=3;
    //own[1][1]=own[2][1]=11;
    own1[1]=own1[2]=11;
    x1[1]=2;
    y1[1]=(Row+2)/2;
    x1[2]=Column-1;
    y1[2]=y1[1];
    //qDebug()<<"开始初始化";
    for(int i=0;i<=Row+1;i++)
    {
        for(int j=0;j<=Column+1;j++)
        {
            data1[i][j]=-1;
        }
    }
    //qDebug()<<"初始化完毕";
    for(int i=0;i<=Column+1;i++)
    {
        data1[0][i]=100;
        data1[Row+1][i]=100;
    }
    for(int i=1;i<=Row;i++)
    {
        data1[i][0]=100;
        data1[i][Column+1]=100;
    }

    data1[x1[1]][y1[1]]=1;
    data1[x1[2]][y1[2]]=2;
}

void ser_data::operator=(ser_data dataTmp)
{
    memcpy(own1,dataTmp.own1,sizeof(dataTmp.own1));
    memcpy(dir1,dataTmp.dir1,sizeof(dataTmp.dir1));
    memcpy(x1,dataTmp.x1,sizeof(dataTmp.x1));
    memcpy(y1,dataTmp.y1,sizeof(dataTmp.y1));
    //memcpy(ops1,ops,sizeof(ops));
    memcpy(data1,dataTmp.data1,sizeof(dataTmp.data1));
}

QString ser_data::toStr()
{
    extern const int PlayerNum;
    extern const int Row;
    extern const int Column;

    QString text=QString::number(PlayerNum,10);
    for(int i=1;i<=PlayerNum;i++)
    {
        text=text+"-own"+QString::number(own1[i],10);
        text=text+"-dir"+QString::number(dir1[i],10);
        text=text+"-x"+QString::number(x1[i],10);
        text=text+"-y"+QString::number(y1[i],10);
        //text=text+"-ops"+QString::number(ops1[i],10);
    }
    text=text+"-data";
    for(int i=1;i<=Row;i++)
    {
        for(int j=1;j<=Column;j++)
        {
            text=text+","+QString::number(data1[i][j],10);
        }
    }
    return text;
}
