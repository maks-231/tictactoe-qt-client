#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QTcpSocket>
#include <QDataStream>

#include <iostream>
#include <iomanip>

#include "common.h"

class NetworkHelper : public QObject {
Q_OBJECT

public:
    NetworkHelper(const QString &strHost, quint16 port);
    virtual ~NetworkHelper();
    void sendToData(const uint8_t*, uint8_t);
    uint8_t* getData();

private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotConnected();

signals:
    void signalFirstPlayerConnected();
    void signalSecondPlayerConnected();
    void signalSecondPlayerDisconnected();
    void signalDataReceived();
    void signalDataReset();
    void signalGameOver();

private:
    QTcpSocket *socket = nullptr;
    uint8_t buffer[BUFF_SIZE];
    quint16 port = 0;
    bool loop = true;
};

#endif // NETWORKHELPER_H
