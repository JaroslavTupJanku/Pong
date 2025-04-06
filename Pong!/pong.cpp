#include "pong.h"

Pong::Pong(QObject* parent) : QObject(parent)
{
    ball = std::make_shared<Ball>(this);
    playerBat = std::make_shared<Bat>(this);
    playerBat->setIsPlayer(true);

    cpuBat = std::make_shared<Bat>(this);
    cpuBat->setIsPlayer(false);
}

void Pong::update()
{
    if (paused) return;

    handle_collisions(ball.get(), cpuBat.get(), playerBat.get());

    ball->move();
    cpuBat->move(ball->getPos()); 
}

void Pong::movePlayer(int y)
{
    QPoint simulatedMouse(0, y);
    playerBat->move(simulatedMouse);
}

void Pong::handle_collisions(Ball* b, Bat* cpu, Bat* player)
{
    const QRect ballRect = b->geometry();

    const int offset = cpu->geometry().intersects(ballRect) ? -5
        : player->geometry().intersects(ballRect) ? 5 : 0;

    if (offset != 0)
        b->handle_collision(offset);
}

void Pong::pause()
{
    paused = !paused;
    emit pausedChanged();
}