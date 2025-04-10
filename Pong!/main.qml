import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import Game 1.0

Window 
{
    width: 640
    height: 480
    visible: true
    title: "Pong"

    maximumWidth: width
    maximumHeight: height
    minimumWidth: width
    minimumHeight: height

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

    Row 
    {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        spacing: 20

        Text {
            text: "Player: " + ball.player1Score + " | CPU: " + ball.player2Score
            font.pixelSize: 24
            color: "red"
        }

        Button 
        {
            id: pauseButton
            text: timer.running ? "Pause" : "Resume"
            font.pixelSize: 18

            background: Rectangle 
            {
                radius: 8
                color: "#cc0000"
                border.color: "#990000"
                border.width: 2
            }

            contentItem: Text 
            {
                text: pauseButton.text
                color: "white"
                font.pixelSize: 18
                anchors.centerIn: parent
            }

            onClicked: timer.running = !timer.running
        }
    }

    Rectangle 
    {
        x: cpuBat.x
        y: cpuBat.y
        width: cpuBat.width
        height: cpuBat.height
        color: "blue"
        radius: 4
        gradient: Gradient 
        {
            GradientStop { position: 0.0; color: "#0000ff" }
            GradientStop { position: 1.0; color: "#000088" }
        }
    }

    Rectangle 
    {
        x: playerBat.x
        y: playerBat.y
        width: playerBat.width
        height: playerBat.height
        color: "blue"
        radius: 4
        gradient: Gradient 
        {
            GradientStop { position: 0.0; color: "#0000ff" }
            GradientStop { position: 1.0; color: "#000088" }
        }
    }

    Rectangle 
    {
        x: ball.x
        y: ball.y
        width: ball.width
        height: ball.height
        color: "red"
        radius: width / 2

        gradient: Gradient 
        {
            GradientStop { position: 0.0; color: "#ff4444" }
            GradientStop { position: 1.0; color: "#cc0000" }
        }
    }

    Timer 
    {
        id: timer   
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
