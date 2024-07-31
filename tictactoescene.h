#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H

#include <QWidget>

class TicTacToeScene : public QWidget {
Q_OBJECT

public:
    TicTacToeScene(QWidget *parent);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    int widthViewport;
    int heighViewport;
};

#endif // OPENGLSCENE_H
