import QtQuick 2.15

Rectangle{
    property int data_
    width: pixel_size
    height: pixel_size
    Component.onCompleted:  {
        border.color="black"
        switch (data_){
            case 0:
                color="black"
                border.color="black"
                break
            case 1:
                color="red"
                break
            case 2:
                color="green"
                break
            case 3:
                color="blue"
                break
            case 4:
                color="yellow"
                break
            case 5:
                color="cyan"
                break
            case 6:
                color="pink"
                break
        }
    }

    border.width: 2

}
