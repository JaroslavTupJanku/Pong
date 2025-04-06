#pragma once

#include <QObject>
#include <QRect>
#include <QPoint>

class Bat : public QObject
{
    Q_OBJECT
        Q_PROPERTY(int x READ getX NOTIFY positionChanged)
        Q_PROPERTY(int y READ getY NOTIFY positionChanged)
        Q_PROPERTY(int width READ getWidth CONSTANT)
        Q_PROPERTY(int height READ getHeight CONSTANT)
        Q_PROPERTY(bool isPlayer READ getIsPlayer WRITE setIsPlayer NOTIFY isPlayerChanged)

    public:
        explicit Bat(QObject* parent = nullptr);

        Q_INVOKABLE void move(const QPoint& point);
        QRect geometry() const;

        int getX() const { return x; }
        int getY() const { return y; }
        int getWidth() const { return 15; }
        int getHeight() const { return 80; }

        bool getIsPlayer() const { return isPlayer; }
        void setIsPlayer(bool value);

    signals:
        void positionChanged();
        void isPlayerChanged();

    private:
        int x = 0;
        int y = 0;
        float ky = 0;
        bool isPlayer = true;
};