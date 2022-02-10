#include"listen.h"

listen::listen(QObject* parent) : QObject(parent)
{

}

void listen::beginListen()
{
    listenServer=new myTCPServer(this);

    unsigned short port=QString("8010").toUShort();
    listenServer->listen(QHostAddress::Any,port);

    qDebug()<< "server is listening...";
    /*connect(listenServer,&myTCPServer::newDescription,this,[=](qintptr sock1)
    {
        qDebug()<< "a new Description!";
        emit newcon(sock1);
    });*/


}
