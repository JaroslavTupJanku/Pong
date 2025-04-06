#pragma once

#include <QObject>
#include <QRect>
#include <QPoint>

class Ball : public QObject
{
    Q_OBJECT
        Q_PROPERTY(int x READ getX WRITE setX NOTIFY positionChanged)
        Q_PROPERTY(int y READ getY WRITE setY NOTIFY positionChanged)
        Q_PROPERTY(int width READ getWidth CONSTANT)
        Q_PROPERTY(int height READ getHeight CONSTANT)
        Q_PROPERTY(int player1Score READ getPlayer1Score NOTIFY scoreChanged)
        Q_PROPERTY(int player2Score READ getPlayer2Score NOTIFY scoreChanged)

public:
    explicit Ball(QObject* parent = nullptr);

    Q_INVOKABLE void move();
    Q_INVOKABLE void handle_collision(int xMove);
    Q_INVOKABLE QPoint getPos() const;

    int getX() const { return x; }
    void setX(int value);

    int getY() const { return y; }
    void setY(int value);

    int getWidth() const { return 15; }
    int getHeight() const { return 15; }

    int getPlayer1Score() const { return p1Score; }
    int getPlayer2Score() const { return p2Score; }

    QRect geometry() const;

signals:
    void positionChanged();
    void scoreChanged();

private:
    int x = 0;
    int y = 0;
    float kx = -2;
    float ky = 2;
    int p1Score = 0;
    int p2Score = 0;
};
