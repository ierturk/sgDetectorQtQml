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
        id: video
        source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
    }

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
        autoOrientation: true
        source: video
        filters: [ videoFilter ]

        focus: true
        Keys.onSpacePressed: video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
        Keys.onLeftPressed: video.seek(video.position - 5000)
        Keys.onRightPressed: video.seek(video.position + 5000)
    }

    MouseArea {
        id: playArea
        anchors.fill: parent
        onPressed: video.play();
    }

    SGDetFilter {
        id: videoFilter
        orientation: videoOutput.orientation
    }
}

