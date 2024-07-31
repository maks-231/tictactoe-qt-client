#include "networkhelper.h"

NetworkHelper::NetworkHelper(const QString &strHost, quint16 port) {
   socket = new QTcpSocket();
   socket->connectToHost(strHost, port);

   this->port = port;

   connect(socket, SIGNAL(connected()), this, SLOT(slotConnected()));
   connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
   connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

NetworkHelper::~NetworkHelper() {
    loop = false;
    socket->disconnect();
    delete socket;
}

uint8_t* NetworkHelper::getData() {
    return buffer;
}

void NetworkHelper::slotReadyRead() {
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_11);

    qint64 bytesAvailable = socket->bytesAvailable();
    QByteArray data = socket->read(bytesAvailable);
    char *ch = data.data();

    for (int i = 0; i < bytesAvailable; i++) {
        buffer[i] = static_cast<uint8_t>(ch[i]);
    }

    if(ch[1]=='A') {
        std::cout <<"Two player connected, the game may start!" << std::endl;
        emit signalSecondPlayerConnected();
    } else if(ch[1]=='B') {
        std::cout <<"One of the player disconnected, the game stopped!" << std::endl;
        emit signalSecondPlayerDisconnected();
    } else if(ch[1]=='C') {
        std::cout <<"Reset command received!" << std::endl;
        emit signalDataReset();
    } else if(ch[1]=='D') {
        std::cout <<"Game Over!" << std::endl;
        emit signalGameOver();
    }else {
        emit signalDataReceived();
    }

    int buffSize = static_cast<int>(bytesAvailable);
    std::cout << "Received bytes number "<< std::dec << buffSize << std::endl;
    std::cout << "Port: " << std::dec << port <<" Received data: ";

    for (int i = 0; i < buffSize; i++) {
        std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(ch[i]) << " ";
    }
    std::cout << std::endl;
}

void NetworkHelper::slotError(QAbstractSocket::SocketError err) {
    QString str = "Error: " + (err == QAbstractSocket::HostNotFoundError ? "The host was not found" :
                              err == QAbstractSocket::RemoteHostClosedError ? "The remote host is closed" :
                              err == QAbstractSocket::ConnectionRefusedError ? "The connection was refused" :
                              err == QAbstractSocket::ConnectionRefusedError ? "The connection was refused" :
                              socket->errorString());

    std::cout << str.toStdString() << std::endl;
}

void NetworkHelper::sendToData(const uint8_t *data, uint8_t buffSize) {
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_11);

    std::cout << "Port: " << std::dec << port <<" Sent     data: ";
    for(int i = 0; i < buffSize; i++) {
        arrBlock.append(static_cast<char>(data[i]));
        std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(data[i]) << " ";
    }
    std::cout << std::endl;
    socket->write(arrBlock);
}

void NetworkHelper::slotConnected() {
    std::cout << "Connected to the server" << std::endl;
    emit signalFirstPlayerConnected();
}
