import QtQuick 2.5
import QtQuick.Window 2.2
import Pictures 1.0
import QtQuick.Controls 1.3

Window {
    width: 500
    height: 500
    visible: true

    ColorPicture {
        id: pic
        x: 0
        y: 0
        width: 200
        height: 200
        //anchors.centerIn: parent
    }

    ColorPicture {
        id: protoPic
        x: 200
        y: 200
        width: 200
        height: 200
        //anchors.centerIn: parent
    }

    MouseArea {
        id: mouseArea1
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Button {
        id: button1
        x: 197
        y: 464
        text: qsTr("Copy")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        onClicked: {// pic.genRandom(10)
            pic.assign(protoPic)
        }
    }

//    Text {
//        text: qsTr("Hello World")
//        anchors.centerIn: parent
//    }
}

