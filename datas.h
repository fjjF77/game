#ifndef SER_DATA_H
#define SER_DATA_H
#include<QPair>
#include<QDebug>

class ser_data
{
public:
    ser_data(int own[],int dir[],int x[],int y[],int **data);
    ser_data(QString s);
    ser_data();
    QString toStr();
    void operator =(ser_data dataTmp);
    int *own1,*dir1,*x1,*y1;
    int **data1;
private:

};

#endif

#ifndef CLI_DATA_H
#define CLI_DATA_H
#include<QPair>
#include<QVector>


class cli_data
{
public:
    cli_data(int own,int dir,int x,int y,int ops);
    cli_data(QString s);
    cli_data();
    void change(int playerNum,ser_data dataAll);
    QString toStr();
    int own1,dir1,x1,y1;
    int ops1;  //玩家操作，无操作默认为0，打拳为1

private:

};

#endif
