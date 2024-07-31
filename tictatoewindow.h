#ifndef TICTATOE_H
#define TICTATOE_H

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QPicture>
#include <QPicture>

#include "mainwindow.h"
#include "tictactoeobject.h"
#include "networkhelper.h"

#include "common.h"

class OpenGLScene;

class TicTaToeWindow : public MainWindow {
Q_OBJECT

public:
    TicTaToeWindow();
    ~TicTaToeWindow();

public slots:
    void slotPlayForCross();
    void slotPlayForCircle();
    void slotResetCallback();
    void slotFirstPlayerConnected();
    void slotSecondPlayerConnected();
    void slotSecondPlayerDisconnected();
    void slotDataReceived();
    void slotResetData();
    void slotSendToServer();
    void slotGameOver();

private:
    void playForCross();
    void playForCircle();
    void resetData();
    void resetState();

    QPushButton *cros;
    QPushButton *circle;
    QPushButton *reset;
    QLabel *firstPlayer;
    QLabel *secondPlayer;
    QLabel *nextStepMake;
    QLabel *portNumber;
    QIcon *grayCircle;
    QIcon *greenCircle;

    QIcon *crosIcon;
    QIcon *circleIcon;

    QList<TicTacToeObject*> ticTacToeObjects;

    NetworkHelper *networkHelper;

    uint8_t fieldStates[SERVICE_FIELDS + MAX_ROW * MAX_COL]; // буффер содержит 5 байт сервисных данных + 9 байт состо€ние €че€к
    uint8_t playFor = EMPTY;
};

#endif // TICTATOE_H
