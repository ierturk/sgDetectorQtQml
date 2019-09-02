import QtQuick 2.12
import QtQuick.Window 2.2
import QtMultimedia 5.9
import QtQuick.Layouts 1.12

import SGDetFilterLib 1.0

Window {
    id: mainWindow
    visible: true
    width: 1080
    height: 360
    title: qsTr("sgDetector")

    SGDetFilter {
        id: videoFilter
        orientation: videoOutput.orientation
    }


    GridLayout {
        id: gridLayout
        anchors.fill: parent
        columnSpacing: 10
        rowSpacing: 10
        rows: 1
        columns: 2

        Rectangle {
            id: rectangle1
            Layout.maximumWidth: 640
            Layout.preferredWidth: 640
            Layout.preferredHeight: 360
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            color: "red"
            Layout.fillHeight: true
            Layout.fillWidth: true

            MediaPlayer {
                id: video_cam00
                autoPlay: true
                // source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
                source: "gst-pipeline: rtspsrc location=rtsp://admin:rdNN2018@192.168.1.64:554/ch01.264?dev=1 caps=\"application/x-rtp, media=(string)video, payload=(int)96, clock-rate=(int)90000, encoding-name=(string)H264\" ! rtph264depay ! decodebin ! videoconvert ! autovideosink"
            }

            VideoOutput {
                id: videoOutput_cam00
                anchors.fill: parent

                source: video_cam00
                // filters: [ videoFilter ]
                focus: true
                Keys.onSpacePressed: video.playbackState === MediaPlayer.PlayingState ? video.pause() : video.play()
                Keys.onLeftPressed: video.seek(video.position - 5000)
                Keys.onRightPressed: video.seek(video.position + 5000)


            }
        }

        Rectangle {
            id: rectangle
            Layout.maximumWidth: 640
            Layout.preferredWidth: 640
            Layout.preferredHeight: 360
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            color: "blue"
            Layout.fillHeight: true
            Layout.fillWidth: true

            MediaPlayer {
                id: video_cam01
                autoPlay: true
                // source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
                source: "gst-pipeline: rtspsrc location=rtsp://192.168.1.66:554/ch01.264?dev=1 caps=\"application/x-rtp, media=(string)video, payload=(int)96, clock-rate=(int)90000, encoding-name=(string)H264\" ! rtph264depay ! decodebin ! videoconvert ! autovideosink"
            }

            VideoOutput {
                id: videoOutput_cam01
                anchors.fill: parent

                source: video_cam01
                // filters: [ videoFilter ]
                Keys.onSpacePressed: video.playbackState === MediaPlayer.PlayingState ? video.pause() : video.play()
                Keys.onLeftPressed: video.seek(video.position - 5000)
                Keys.onRightPressed: video.seek(video.position + 5000)
            }
        }
    }
}
