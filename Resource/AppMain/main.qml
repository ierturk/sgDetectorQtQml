import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.9

import SGDetFilterLib 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("My Video Filter")

    MediaPlayer {
        id: mediaplayer
        source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
        autoPlay: true
    }

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
        autoOrientation: true
        source: mediaplayer
        filters: [ videoFilter ]
    }

    MouseArea {
        id: playArea
        anchors.fill: parent
        onPressed: mediaplayer.play();
    }

    SGDetFilter {
        id: videoFilter
        orientation: videoOutput.orientation
    }
}

