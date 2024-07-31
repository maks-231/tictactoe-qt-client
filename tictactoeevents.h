#ifndef TICTACTOEEVENTS_H
#define TICTACTOEEVENTS_H

#include <QObject>

class TicTacToeEvents {
Q_OBJECT

public:
    virtual ~TicTacToeEvents(){}

signals:
    void signalSendDataToServer();

};

#endif // TICTACTOEEVENTS_H
