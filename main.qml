import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id: window
    width: 768
    height: 480
    visible: true
    title: qsTr("Hello World")

    property var items: []


    // not resizeble
//        maximumHeight: height
//        maximumWidth: width
//        minimumHeight: height
//        minimumWidth: width


    property int widthField: 160
    property int heightField: 120

    property int modeInsert: ModeInserts.ADD.UNAVAILABLE_CELL

    /* С помощью объекта Connections
     * Устанавливаем соединение с классом ядра приложения
     * */
    Connections {
        target: bfs
        property int lastIdxCellChecked: -1
        function onPointChecked(x, y) {
            if(lastIdxCellChecked != -1)
                items[lastIdxCellChecked].color = "lightgreen"
            var idx = x + (y * widthField);
            items[idx].color = "pink"
            lastIdxCellChecked = idx
        }
        function onPathViewed(x, y){
            items[x + (y * widthField)].color = "green"
            if(lastIdxCellChecked != -1)
                items[lastIdxCellChecked].color = "lightgreen"
            lastIdxCellChecked= -1
        }
    }

    Rectangle {
        id: frameField
        width: parent.width * 0.8
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 0
        color: "darkgray"

        Grid {
            id: field
            property int start_x: -1
            property int start_y: -1
            property int finish_x: -1
            property int finish_y: -1
            property int unavailable_x: -1
            property int unavailable_y: -1
            property bool isUnavSeted: false

            anchors.fill: parent
            columns: widthField
            rows: heightField
            // spacing: 1

            onUnavailable_xChanged: {
//                console.log("[x] add unabailable: ", unavailable_x, " ", unavailable_y);
                if(unavailable_x != -1 && unavailable_y != -1){
                    bfs.setUnavailableCell(unavailable_x, unavailable_y);
                    isUnavSeted = true;
                }
                if(isUnavSeted){
                    unavailable_x = -1
                    unavailable_y = -1
                    isUnavSeted = false;
                }
            }

            onUnavailable_yChanged: {
//                console.log("[y] add unabailable: ", unavailable_x, " ", unavailable_y);
                if(unavailable_x != -1 && unavailable_y != -1){
                    bfs.setUnavailableCell(unavailable_x, unavailable_y);
                    isUnavSeted = true;
                }
                if(isUnavSeted){
                    unavailable_x = -1
                    unavailable_y = -1
                    isUnavSeted = false;
                }
            }
        }
    }

    Rectangle {
        id: manager
        width: parent.width * 0.2
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: 0
        border.width: 1
        border.color: "darkblue"

        color: "steelblue"

        Column {
            id: column
            anchors.fill: parent
            padding: 5
            spacing: 5

            Button {
                id: button
                width: parent.width - 20
                height: 40
                text: qsTr("Remove grid")
                anchors.horizontalCenter: parent.horizontalCenter

                property bool isClicked: true
                onClicked: {
                    isClicked = !isClicked
                    for (var i = 0; i < items.length; i++) {
                        items[i].border.width = isClicked
                    }
                }
            }

            Button {
                id: buttonClear
                width: parent.width - 20
                height: 40
                text: qsTr("Clear restricted areas")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    for (var i = 0; i < items.length; i++){
                        items[i].color = items[i].defaultColor
                    }
                    field.start_x = -1;
                    field.start_y = -1;
                    field.finish_x = -1;
                    field.finish_y = -1;
                    bfs.clearField();
                }
            }

            Button {
                id: buttonSearch
                width: parent.width - 20
                height: 40
                text: qsTr("Search")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    if (field.start_x != -1 && field.start_y != -1 && field.finish_x != -1 && field.finish_y != -1)
                        bfs.search(field.start_x, field.start_y, field.finish_x, field.finish_y)
                }
            }

            ComboBox {
                id: comboBox
                anchors.horizontalCenter: parent.horizontalCenter
                currentIndex: 0
                width: parent.width - 20
                //model: ["First", "Second", "Third"]
                model: ["UNAVAILABLE_CELL", "START_POINT", "FINISH_POINT"]
                onCurrentIndexChanged: {
                    modeInsert = currentIndex
                }
            }
        }
    }

    Component.onCompleted: {
        heightField = bfs.getCols();
        widthField = bfs.getRows();

        // Create field
        var counterItems = 0;
        for (var i = 0; i < heightField; i++){
            for (var j = 0; j < widthField; j++){
                var component = Qt.createComponent("Cell.qml")

                if( component.status !== Component.Ready ) {
                    if( component.status === Component.Error )
                        console.debug("Error:"+ component.errorString() );
                    return; // or maybe throw
                }

                if (component === null) {
                    console.log("Error creating cell");
                }

                var cell = component.createObject(field);
                items[counterItems] = cell;
                counterItems++
//                console.log("cell added: ", i, " ", j)
                cell.cell_x = i
                cell.cell_y = j
                cell.width = frameField.width / field.columns
                cell.height = frameField.height / field.rows
                cell.parent = field
            }
        }
    }


    onWidthChanged: {
        for (var i = 0; i < items.length; i++){
            items[i].width = frameField.width / field.columns
            items[i].height = frameField.height / field.rows
        }
    }

    onHeightChanged: {
        for (var i = 0; i < items.length; i++){
            items[i].width = frameField.width / field.columns
            items[i].height = frameField.height / field.rows
        }
    }
}
