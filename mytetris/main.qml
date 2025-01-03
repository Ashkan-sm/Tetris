import QtQuick 2.15
import QtQuick.Window 2.15


Window {





    property int pixel_size: 40
    property int game_width: 10
    property int game_heigth: 20

    width: pixel_size*game_width*2
    height: pixel_size*game_heigth
    visible: true

    title: qsTr("ASHKAN_TETRIS")
    Rectangle{
        visible:! uiscreen.runnig
        id:gameover
        color:"#cc000000"
        anchors.fill: parent
        z:1
        Column{
            anchors.centerIn: parent
            Text {

                text: "GAME OVER"
                font.bold:true
                font.pointSize: 60
                color: "yellow"
            }

            Rectangle{

                x:parent.width/2-(width/2)
                y:100
                width: 100
                height: 50
                color: "white"
                Text{

                    text: "RETRY"
                    anchors.centerIn: parent

                }
                MouseArea{
                    hoverEnabled: true
                    anchors.fill: parent
                    onClicked: {
                        uiscreen.retry()
                        uiscreen.runnig=true;
                    }
                    onEntered: parent.color="green"
                    onExited: parent.color="white"
                }

            }
        }

    }

    Rectangle{
        color: "gray"
        anchors.right: parent.right;
        width: parent.width/2
        height: parent.height
        Rectangle{
            id:scr
            color: "black"
            width: parent.width*4/6
            height: width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: parent.width/6
            Grid{
                anchors.centerIn: parent
                columns: 4
                Repeater{

                    model: uiscreen.next_obj_2


                    Repeater{

                        model:modelData
                        Pixel{
                            data_:modelData
                        }

                    }

                }
            }

        }
        Column{
            anchors.top: scr.bottom
            anchors.right: parent.right
            anchors.margins: 100
            Text {

                id: score
                color: "black"
                text:"SCORE: " + uiscreen.score
            }
            Text {

                id: level

                color: "black"
                text:"LEVEL: " + uiscreen.level
            }
            Text{

                color: "yellow"
                text:"HIGH_SCORE: " + uiscreen.high_score
            }

            Item {
                height: 100
                width: 100
            }
            Rectangle{


                width: 100
                height: 50
                color: "white"
                Text{
                    text: "RETRY"
                    anchors.centerIn: parent

                }
                MouseArea{
                    hoverEnabled: true
                    anchors.fill: parent
                    onClicked: {
                        uiscreen.retry()
                    }
                    onEntered: parent.color="green"
                    onExited: parent.color="white"
                }

            }
        }
    }
    Grid{
        focus: true
        Keys.onPressed: (event)=>{
            switch (event.key) {
                case Qt.Key_Right:
                    uiscreen.move_right()
                    break
                case Qt.Key_Left:
                    uiscreen.move_left()
                    break
                case Qt.Key_Up:
                    uiscreen.rotate_right()
                    break
                case Qt.Key_Down:
                    uiscreen.move_down()
                    break

            }
        }
        columns: game_width

        Repeater{
            id: rep_window
            model: uiscreen.get_matrix()

            Repeater{

                model:modelData
                Pixel{
                    data_:modelData
                }

            }

        }




    }
    Connections{

        target:uiscreen
        function onMatrixChanged(){

            rep_window.model=uiscreen.get_matrix()
        }
    }
}
