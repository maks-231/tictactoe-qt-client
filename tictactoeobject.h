#ifndef TICTACTOEOBJECT_H
#define TICTACTOEOBJECT_H

#include <QWidget>

class TicTacToeObject : public QWidget {
Q_OBJECT

public:
    TicTacToeObject(uint8_t *playFor, uint8_t *data, uint8_t *nextStep, QWidget *parent);
    ~TicTacToeObject();
    void reset();
    void setData(uint8_t *data);
    void refreshTileValue();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void signalSendDataToServer();

private:
    QPixmap *pic;
    bool tileSetFlag = false;
    uint8_t *data = nullptr;
    uint8_t tileValue = 0;
    uint8_t *playFor = nullptr;
    uint8_t *nextStep = nullptr;
};

#endif // TICTACTOEOBJECT_H
