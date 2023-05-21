import QtQuick 2.15

Rectangle {
    property string defaultColor: "lightgray"
    property var cell_x: 0
    property var cell_y: 0

    width: 10
    height: 10
    color: "lightgray"
    border.width: 1
    border.color: "darkgray"
    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("on cell clicked: ", cell_x, cell_y)
            switch (window.modeInsert ){
            case ModeInserts.ADD.UNAVAILABLE_CELL:
                field.unavailable_x = cell_x;
                field.unavailable_y = cell_y;
                parent.color = "darkorange"
                break
            case ModeInserts.ADD.START_POINT:
                if(field.start_x === -1 && field.start_y === -1){
                    parent.color = "yellow"
                    field.start_x = cell_x;
                    field.start_y = cell_y;
                }

                break
            case ModeInserts.ADD.FINISH_POINT:
                if(field.finish_x === -1 && field.finish_y === -1){
                    parent.color = "red"
                    field.finish_x = cell_x;
                    field.finish_y = cell_y;
                }
                break
            default:
                 parent.color = "darkorange"
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:16;height:100;width:100}
}
##^##*/
