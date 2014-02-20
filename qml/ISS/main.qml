import QtQuick 2.2
import QtQuick.Controls 1.1
import ISS 1.0

Rectangle {
    width: 360
    height: 360

    Row
    {
        id:row1

        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            text:"Previous"
            onClicked: {
                spinbox1.value -= 1;
            }
        }

        SpinBox {
            id:spinbox1
            value:1
            onValueChanged:
            {
                list1.clear();
                console.log( "request nr :", service1.requestImageInfoByTags( ["my_little_pony","rating:s","&page="+spinbox1.value], -1 ) );
            }
        }

        Button {
            text:"Next"
            onClicked: {
                spinbox1.value += 1;
            }
        }



    }

    GridView {

        anchors.fill: parent
        anchors.topMargin: row1.height

        model: list1

        cellHeight: 160
        cellWidth: 160

        delegate: Item
        {
            id:rootitem

            width: 160
            height: 160

            property QtObject request: null

            Rectangle
            {
                x:4
                y:4
                width: 152
                height: 152
                color: model.object.fileReady ? "green" :
                                                request ? "red" : "black"
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

            Rectangle
            {
                visible: request != null
                width: 20
                height: request? 10 + 1.5 * request.percent : 0
                color: "green"
            }

            MouseArea {
                anchors.fill: parent

                onDoubleClicked: {

                    console.log( "Starting loading image " + model.object.id );
                    rootitem.request= model.service.requestImageFile( model.object ,model.file_url );

                }

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

        OuroborosService
        {

            id:service1

            domain: "e621.net"

            onObjectReady:
            {
                console.log(" request ",request," ready: ", data["id"] );

                var obj= i1.newObject( "e621" + data["id"] );

                obj.author= data.author;
                obj.width = data.width;
                obj.height = data.height;
                obj.tags = data.tags.split(/\s/);

                list1.append( {
                            preview_url:data.preview_url,
                            preview_height:data.preview_height,
                            preview_width:data.preview_width,
                            file_url:data.file_url,
                            object: obj,
                            service: service1
                            } );

            }

            Component.onCompleted:
            {
                console.log( "request nr :", service1.requestImageInfoByTags( ["my_little_pony","rating:s"], -1 ) );
            }
        }

    }

}
