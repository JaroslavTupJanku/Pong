import QtQuick 2.9
import QtQuick.Window 2.2
import Game 1.0 

Window 
{
    width: 640
    height: 480
    visible: true
    title: "Pong"

    MouseArea 
    {
        anchors.fill: parent
        hoverEnabled: true
        onPositionChanged: {
            playerBat.move(Qt.point(mouse.x, mouse.y))
        }
    }  

    Pong {
        id: pong
    }

    Ball {
        id: ball
    }

    Bat 
    {
        id: cpuBat
        isPlayer: false
    }

    Bat
    {
        id: playerBat
        isPlayer: true
    }

    Rectangle 
    {
        x: cpuBat.x
        y: cpuBat.y
        width: cpuBat.width
        height: cpuBat.height
        color: "blue"
    }

    Rectangle 
    {
        x: playerBat.x
        y: playerBat.y
        width: playerBat.width
        height: playerBat.height
        color: "blue"
    }

    Rectangle 
    {
        x: ball.x
        y: ball.y
        width: ball.width
        height: ball.height
        color: "red"
        radius: width / 2
    }

    Text {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Player: " + ball.player1Score + " | CPU: " + ball.player2Score
        font.pixelSize: 24
        color: "red"
    }

    Timer {
        interval: 16
        running: true
        repeat: true
        onTriggered: 
        {
            ball.move()
            cpuBat.move(ball.getPos())

            var playerRect = Qt.rect(playerBat.x, playerBat.y, playerBat.width, playerBat.height)
            var ballRect = Qt.rect(ball.x, ball.y, ball.width, ball.height)
            var cpuRect = Qt.rect(cpuBat.x, cpuBat.y, cpuBat.width, cpuBat.height)

            if (pong.rectsIntersect(playerRect, ballRect)) {
                ball.handle_collision(5)
            }

            if (pong.rectsIntersect(cpuRect, ballRect)) {
                ball.handle_collision(-5)
            }
        }
    }
}