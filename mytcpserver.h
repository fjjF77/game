#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include<QTcpServer>

class myTCPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit myTCPServer(QObject *parent = nullptr);

signals:
    void newDescription(qintptr sock);

protected:
    void incomingConnection(qintptr sock);
};

#endif // MYTCPSERVER_H
