#include "ball.h"
#include <QDebug>

Ball::Ball(QObject* parent) : QObject(parent)
{
    x = 320;
    y = 240;
}

void Ball::setX(int value)
{
    if (x == value)
        return;

    x = value;
    emit positionChanged();
}

void Ball::setY(int value)
{
    if (y == value)
        return;

    y = value;
    emit positionChanged();
}

QRect Ball::geometry() const
{
    return QRect(x, y, getWidth(), getHeight());
}

QPoint Ball::getPos() const
{
    return QPoint(x, y);
}

void Ball::move()
{
    const int screenWidth = 640;
    const int screenHeight = 480;

    if (x < 0 || x > screenWidth) 
    {
        (x < 0 ? p2Score : p1Score)++;
        emit scoreChanged();

        setX(screenWidth / 2);
        setY(screenHeight / 2);
        kx *= -1;
        return;
    }

    if (y < 0 || y > screenHeight - getHeight())
        ky *= -1;

    setX(x + kx);
    setY(y + ky);

    qDebug() << "Ball position:" << x << y;
}

void Ball::handle_collision(int xMove)
{
    x += xMove;       
    kx *= -1;     
    emit positionChanged();
}