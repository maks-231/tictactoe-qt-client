#include <QPainter>
#include <iostream>

#include "tictactoescene.h"

TicTacToeScene::TicTacToeScene(QWidget *parent) : QWidget(parent) {
}


void TicTacToeScene::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    std::cout << std::endl << painter.viewport().width() << "  " << painter.viewport().height() << std::endl;

    painter.setPen(QPen(Qt::black, 10));
    painter.drawLine(10, 100, 545, 100);
    painter.drawLine(10, 260, 545, 260);

    painter.drawLine(180, 10, 180, 400);
    painter.drawLine(360, 10, 360, 400);

    painter.end();
}

void TicTacToeScene::mouseReleaseEvent(QMouseEvent *event) {
    repaint();
    QWidget::mouseReleaseEvent(event);
}

