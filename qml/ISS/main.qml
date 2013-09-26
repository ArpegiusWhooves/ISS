import QtQuick 2.0
import ISS 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    ISService
    {
        id: i1

        E621Service
        {

            id:service1

            Component.onCompleted:
            {


                //service1.get(obj1);

                service1.get({"url":"http://example.com"});

            }
        }

    }

}
