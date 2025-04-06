#include "bat.h"
#include <QDebug>

Bat::Bat(QObject* parent) : QObject(parent)
{
    setIsPlayer(isPlayer);
}

void Bat::setIsPlayer(bool value)
{
    isPlayer = value;
    x = isPlayer ? 30 : 640 - 45;
    y = 480 / 2;
    ky = isPlayer ? 0 : 2;

    emit isPlayerChanged();
    emit positionChanged();
}


void Bat::move(const QPoint& point)
{
    const int screenHeight = 480;
    const bool outOfBounds = y < 0 || y > screenHeight - getHeight();

    if (isPlayer) 
    {
        y = point.y() - getHeight() / 2;
    }
    else 
    {
        const int centerY = y + getHeight() / 2;
        const int delta = point.y() - centerY;

        if (qAbs(delta) > 5)  
            y += (delta > 0) ? 3 : -3;

        y = std::clamp(y, 0, screenHeight - getHeight());
    }

    emit positionChanged();
}

QRect Bat::geometry() const
{
    return QRect(x, y, getWidth(), getHeight());
}