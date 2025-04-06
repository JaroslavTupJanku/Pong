#pragma once

#include <QObject>
#include <QRectF>
#include <memory>
#include "ball.h"
#include "bat.h"

class Pong : public QObject
{
    Q_OBJECT
        Q_PROPERTY(QObject* ball READ getBall CONSTANT)
        Q_PROPERTY(QObject* playerBat READ getPlayerBat CONSTANT)
        Q_PROPERTY(QObject* cpuBat READ getCpuBat CONSTANT)
        Q_PROPERTY(bool paused READ isPaused NOTIFY pausedChanged)

public:
    explicit Pong(QObject* parent = nullptr);

    Q_INVOKABLE void update();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void movePlayer(int y);

    Q_INVOKABLE bool rectsIntersect(const QRectF& r1, const QRectF& r2) const {
        return r1.intersects(r2);
    }

    QObject* getBall() const { return ball.get(); }
    QObject* getPlayerBat() const { return playerBat.get(); }
    QObject* getCpuBat() const { return cpuBat.get(); }

    bool isPaused() const { return paused; }

signals:
    void pausedChanged();

private:
    void handle_collisions(Ball* b, Bat* cpu, Bat* player);

    std::shared_ptr<Ball> ball;
    std::shared_ptr<Bat> cpuBat;
    std::shared_ptr<Bat> playerBat;
    bool paused = false;
};

using PongPtr = std::shared_ptr<Pong>;
