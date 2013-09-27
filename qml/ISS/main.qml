import QtQuick 2.0
import ISS 1.0

Rectangle {
    width: 360
    height: 360

    GridView {

        anchors.fill: parent

        model: list1

        cellHeight: 160
        cellWidth: 160

        delegate: Item
        {
            width: 160
            height: 160

            Rectangle
            {
                x:4
                y:4
                width: 152
                height: 152
                color: "black"
            }
            Rectangle
            {
                anchors.fill: parent

                visible: GridView.isCurrentItem

                color: "blue"
            }
            Image{
                anchors.centerIn: parent
                source: model.preview_url
                scale: Math.min( 150/model.preview_height, 150/model.preview_width)
            }

            MouseArea {
                anchors.fill: parent

            }

        }



    }



    ListModel
    {
        id: list1
    }

    ISService
    {
        id: i1

        E621Service
        {

            id:service1

            onObjectReady:
            {
                console.log(" request ",request," ready: ", object["id"] );
                list1.append( object );

            }

            Component.onCompleted:
            {
                console.log( "request nr :", service1.requestImageInfoByTags( ["my_little_pony","rating:s"], -1 ) );
            }
        }

    }

}
