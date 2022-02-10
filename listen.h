#ifndef LISTEN_H
#define LISTEN_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include"mytcpserver.h"

class listen : public QObject
{
    Q_OBJECT
public:
    explicit listen(QObject *parent = nullptr);
    void beginListen();
    myTCPServer *listenServer;

signals:
    //void newcon(qintptr sock1);
};

#endif // LISTEN_H
