#include "tictatoewindow.h"
#include "tictactoescene.h"


TicTaToeWindow::TicTaToeWindow() {
    QHBoxLayout *settingsLoayout = new QHBoxLayout();
    reset = new QPushButton("Reset");

    crosIcon = new QIcon(":/icons/X.png");
    circleIcon = new QIcon(":/icons/O.png");

    cros = new QPushButton();
    cros->setIcon(*crosIcon);

    circle = new QPushButton();
    circle->setIcon(*circleIcon);

    firstPlayer = new QLabel();
    secondPlayer = new QLabel();

    firstPlayer->setFixedHeight(20);
    secondPlayer->setFixedHeight(20);

    grayCircle = new QIcon(":/icons/grayCircle.png");
    greenCircle = new QIcon(":/icons/greenCircle.png");

    QPixmap pixmap = grayCircle->pixmap(QSize(15, 15));
    firstPlayer->setPixmap(pixmap);
    secondPlayer->setPixmap(pixmap);

    nextStepMake = new QLabel();
    nextStepMake->setFixedHeight(20);
    QLabel *nextStepMakeLabel = new QLabel("Next step: ");

    quint16 port = 5000;

    portNumber = new QLabel("Port: " + QString::number(port));

    settingsLoayout->addWidget(reset);
    settingsLoayout->addWidget(cros);
    settingsLoayout->addWidget(circle);
    settingsLoayout->addWidget(portNumber);
    settingsLoayout->addStretch();
    settingsLoayout->addWidget(nextStepMakeLabel);
    settingsLoayout->addWidget(nextStepMake);
    settingsLoayout->addStretch();
    settingsLoayout->addWidget(firstPlayer);
    settingsLoayout->addWidget(secondPlayer);

    QGridLayout *ticTacToeGridLayout = new QGridLayout();
    networkHelper = new NetworkHelper("localhost", port);

    int index = SERVICE_FIELDS; // отступ от начала
    for (int row = 0; row < MAX_ROW; row++) {
        for (int col = 0; col < MAX_COL; col++) {
            TicTacToeObject *ticTacToeObject = new TicTacToeObject(&playFor, &fieldStates[index++], &fieldStates[3], this);
            ticTacToeObject->resize(INITIAL_WIDGET_WIDTH, INITIAL_WIDGET_HIGHT);
            ticTacToeObjects.append(ticTacToeObject);
            ticTacToeGridLayout->addWidget(ticTacToeObject, row, col);
            connect(ticTacToeObject, SIGNAL(signalSendDataToServer()), this, SLOT(slotSendToServer()));
        }
    }

    int buffSize = SERVICE_FIELDS + MAX_ROW * MAX_COL;
    for (int var = 0; var < buffSize; ++var) {
        fieldStates[var] = EMPTY;
    }

    QVBoxLayout* mainlayout = new QVBoxLayout(); //main layout for ui
    mainlayout->addLayout(settingsLoayout);
    mainlayout->addLayout(ticTacToeGridLayout);

    ui->centralWidget->setLayout(mainlayout);

    connect(reset, SIGNAL(released()), this, SLOT(slotResetCallback()));
    connect(cros, SIGNAL(released()), this, SLOT(slotPlayForCross()));
    connect(circle, SIGNAL(released()), this, SLOT(slotPlayForCircle()));
    connect(networkHelper, SIGNAL(signalFirstPlayerConnected()), this, SLOT(slotFirstPlayerConnected()));
    connect(networkHelper, SIGNAL(signalSecondPlayerConnected()), this, SLOT(slotSecondPlayerConnected()));
    connect(networkHelper, SIGNAL(signalSecondPlayerDisconnected()), this, SLOT(slotSecondPlayerDisconnected()));
    connect(networkHelper, SIGNAL(signalDataReceived()), this, SLOT(slotDataReceived()));
    connect(networkHelper, SIGNAL(signalDataReset()), this, SLOT(slotResetData()));
    connect(networkHelper, SIGNAL(signalGameOver()), this, SLOT(slotGameOver()));
}

void TicTaToeWindow::slotGameOver() {
    uint8_t *buffer = networkHelper->getData();

    for (int i = 0; i < DATA_SIZE; i++) {
        fieldStates[i] = buffer[i];
    }

    for(TicTacToeObject* ticTacToeObject : ticTacToeObjects) {
        ticTacToeObject->refreshTileValue();
        ticTacToeObject->repaint();
    }

    resetState();
}

void TicTaToeWindow::slotDataReceived() {
    uint8_t *buffer = networkHelper->getData();

    for (int i = 0; i < DATA_SIZE; i++) {
        fieldStates[i] = buffer[i];
    }

    if(playFor == EMPTY && fieldStates[PLAY_FOR] != EMPTY) {
        playFor = fieldStates[PLAY_FOR];
        if(playFor == CROS) {
            playForCross();
        } else {
            playForCircle();
        }
        fieldStates[PLAY_FOR] = EMPTY;
    } else {
        if(fieldStates[NEXT_STEP_BY] == CROS) {
            nextStepMake->setPixmap(crosIcon->pixmap(QSize(15, 15)));
        } else if (fieldStates[NEXT_STEP_BY] == CIRCLE) {
            nextStepMake->setPixmap(circleIcon->pixmap(QSize(15, 15)));
        }
    }

    for(TicTacToeObject* ticTacToeObject : ticTacToeObjects) {
        ticTacToeObject->repaint();
    }
}

void TicTaToeWindow::playForCross() {
    resetData();
    playFor = CROS;
    fieldStates[COMMAND] = EMPTY;
    fieldStates[NEXT_STEP_BY] = EMPTY;
    circle->hide();
}

void TicTaToeWindow::playForCircle() {
    resetData();
    playFor = CIRCLE;
    fieldStates[COMMAND] = EMPTY;
    fieldStates[NEXT_STEP_BY] = EMPTY;
    cros->hide();
}

void TicTaToeWindow::slotPlayForCross() {
    playForCross();
    fieldStates[PLAY_FOR] = CIRCLE;
    networkHelper->sendToData(fieldStates, DATA_SIZE);
}

void TicTaToeWindow::slotPlayForCircle() {
    playForCircle();
    fieldStates[PLAY_FOR] = CROS;
    networkHelper->sendToData(fieldStates, DATA_SIZE);
}

void TicTaToeWindow::slotFirstPlayerConnected() {
    QPixmap pixmap = greenCircle->pixmap(QSize(15, 15));
    firstPlayer->setPixmap(pixmap);
}

void TicTaToeWindow::slotSecondPlayerConnected() {
    QPixmap pixmap = greenCircle->pixmap(QSize(15, 15));
    secondPlayer->setPixmap(pixmap);
}

void TicTaToeWindow::slotSecondPlayerDisconnected() {
    QPixmap pixmap = greenCircle->pixmap(QSize(15, 15));
    secondPlayer->setPixmap(pixmap);
}

void TicTaToeWindow::resetState() {
    if(cros->isHidden()) {
        cros->show();
    }
    if(circle->isHidden()) {
        circle->show();
    }

    nextStepMake->clear();
    playFor = EMPTY;

    int buffSize = SERVICE_FIELDS + MAX_ROW * MAX_COL;
    for (int var = 0; var < buffSize; ++var) {
        fieldStates[var] = EMPTY;
    }
}

void TicTaToeWindow::resetData() {
    resetState();

    for(TicTacToeObject* ticTacToeObject : ticTacToeObjects) {
        ticTacToeObject->reset();
    }
}

void TicTaToeWindow::slotResetData() {
    resetData();
}

void TicTaToeWindow::slotResetCallback() {
    resetData();
    fieldStates[COMMAND] = 'C';
    networkHelper->sendToData(fieldStates, DATA_SIZE);
}

void TicTaToeWindow::slotSendToServer() {
    if(playFor == CROS){
       nextStepMake->setPixmap(circleIcon->pixmap(QSize(15, 15)));
       fieldStates[NEXT_STEP_BY] = CIRCLE;
    } else {
       nextStepMake->setPixmap(crosIcon->pixmap(QSize(15, 15)));
       fieldStates[NEXT_STEP_BY] = CROS;
    }
    fieldStates[PLAY_FOR] = playFor;
    networkHelper->sendToData(fieldStates, DATA_SIZE);
}

TicTaToeWindow::~TicTaToeWindow() {
    for( TicTacToeObject *ticTacToeObject : ticTacToeObjects){
        delete ticTacToeObject;
    }

    delete networkHelper;
}

