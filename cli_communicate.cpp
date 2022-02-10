#include "cli_communicate.h"

cli_communicate::cli_communicate(QString ser_ip,QObject *parent) : QObject(parent)
{
    cli_socket=new QTcpSocket;
    connecting=0;

    //QString ser_ip="127.0.0.1";
    unsigned short ser_port=QString("8010").toUShort();
    cli_socket->connectToHost(QHostAddress(ser_ip),ser_port);

    connect(cli_socket,&QTcpSocket::connected,this,[=]()
    {
        connect(cli_socket,&QTcpSocket::readyRead,this,[=]()
        {
            QByteArray dataTmp=cli_socket->readAll();
            QString text=dataTmp;
            if(text.startsWith(QString("Oh")))
            {
                text.remove(0,2);
                emit connected(text.toInt());
                connecting=1;
            }
            else
            {
                ser_data data1(text);
                emit recv(data1);
            }
        });

    });

    connect(cli_socket,&QTcpSocket::disconnected,this,[=]()
    {
        qDebug()<<"与服务器断开了连接……";
        connecting=0;
        emit disconnected();
        cli_socket->deleteLater();
    });
}

void cli_communicate::send(cli_data data1)
{
    if(connecting)
    {
        QByteArray text=data1.toStr().toUtf8();
        cli_socket->write(text);
    }
}

void cli_communicate::send(QString str)
{
    if(connecting)
    {
        QByteArray text=str.toUtf8();
        cli_socket->write(text);
    }
}
