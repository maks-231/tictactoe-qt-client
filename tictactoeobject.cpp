#include <QPainter>
#include <iostream>

#include "tictactoeobject.h"
#include "tictatoewindow.h"

TicTacToeObject::TicTacToeObject(uint8_t *playFor, uint8_t *data, uint8_t *nextStep, QWidget *parent) : QWidget(parent) {
    this->data = data;
    this->playFor = playFor;
    this->nextStep = nextStep;
}

TicTacToeObject::~TicTacToeObject() {
    delete pic;
}

void TicTacToeObject::paintEvent(QPaintEvent *e) {
    QPainter painter(this);

    if(*data != EMPTY) {
        if(*data == CROS) {
            pic = new QPixmap(":/icons/X.png");
        } else if(*data == CIRCLE) {
            pic = new QPixmap(":/icons/O.png");
        } else if(*data == CROS2) {
            pic = new QPixmap(":/icons/X2.png");
        } else if(*data == CIRCLE2) {
            pic = new QPixmap(":/icons/O2.png");
        }
        painter.drawPixmap(20, 20, width() - 40, height() - 30, *pic);
    }

    painter.setPen(QPen(Qt::black, 1));
    painter.drawRoundedRect(0, 5, width() - 5 , height() - 7 ,3, 3);
    QWidget::paintEvent(e);
}

void TicTacToeObject::refreshTileValue() {
    tileValue = *data;
}

void TicTacToeObject::mouseReleaseEvent(QMouseEvent *event) {
    std::cout << "*nextStep = " << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(*nextStep) <<  ", *playFor = " << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(*playFor) << std::endl;
    if((*nextStep == *playFor) || *nextStep == EMPTY) {
        if(*playFor != EMPTY && *data == EMPTY) {
            std::cout << "Tile set to " << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(*nextStep) << std::endl;
            tileValue = *data = *playFor;
            emit signalSendDataToServer();
        }
    }
    repaint();
    QWidget::mouseReleaseEvent(event);
}

void TicTacToeObject::reset() {
    tileValue = EMPTY;
    repaint();
}

void TicTacToeObject::setData(uint8_t *data){
    this->data = data;
}
