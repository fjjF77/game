#include "mytcpserver.h"

myTCPServer::myTCPServer(QObject *parent) : QTcpServer(parent)
{

}

void myTCPServer::incomingConnection(qintptr sock)
{
    emit newDescription(sock);
}
