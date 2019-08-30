import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.9

import SGDetFilterLib 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("sgDetector")

    MediaPlayer {
        id: video
        autoPlay: true
        // source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
        source: "gst-pipeline: rtspsrc location=rtsp://admin:rdNN2018@192.168.1.66:554/ch01.264?dev=1 caps=\"application/x-rtp, media=(string)video, payload=(int)96, clock-rate=(int)90000, encoding-name=(string)H264\" ! rtph264depay ! decodebin ! videoconvert ! autovideosink"

        autoLoad: true
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
/*
        Component.onCompleted: {
            console.warn("warn completed")
            console.log("log completed")
            console.error("error completed")
            console.debug("debug completed")
            console.exception("exception completed")
            console.info("info completed")
        }
*/
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

