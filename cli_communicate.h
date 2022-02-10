#ifndef CLI_COMMUNICATE_H
#define CLI_COMMUNICATE_H

#include <QObject>
#include<QTcpSocket>
#include<QHostAddress>
#include"datas.h"

class cli_communicate : public QObject
{
    Q_OBJECT
public:
    explicit cli_communicate(QString ser_ip=QString("127.0.0.1"),QObject *parent = nullptr);
    void send(cli_data data1);
    void send(QString str);

private:
    QTcpSocket *cli_socket;
    bool connecting;

signals:
    void connected(int playerNum);
    void recv(ser_data data1);
    void disconnected();
};

#endif // CLI_COMMUNICATE_H
