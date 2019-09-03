import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtMultimedia 5.9
import QtQuick.Layouts 1.12

import SGDetFilterLib 1.0

Window {
    id: mainWindow
    visible: true
    width: 1080
    height: 360
    title: qsTr("sgDetector")

    MediaPlayer {
        id: video_cam00
        objectName: "video_cam00"
        autoPlay: true
        // source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
        source: "gst-pipeline: rtspsrc location=rtsp://admin:rdNN2018@192.168.1.64:554/ch01.264?dev=1 ! application/x-rtp, media=video, encoding-name=H264 ! rtph264depay ! decodebin ! videoconvert ! autovideosink"
    }

    MediaPlayer {
        id: video_cam01
        autoPlay: true
        // source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
        source: "gst-pipeline: rtspsrc location=rtsp://192.168.1.66:554/ch01.264?dev=1 ! application/x-rtp, media=video, encoding-name=H264 ! rtph264depay ! decodebin ! videoconvert ! autovideosink"
    }

    SGDetFilter {
        id: videoFilter_00
        orientation: videoOutput_cam00.orientation
    }

    SGDetFilter {
        id: videoFilter_01
        orientation: videoOutput_cam01.orientation
    }

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        columnSpacing: 5
        rowSpacing: 5
        rows: 1
        columns: 2



        VideoOutput {
            id: videoOutput_cam00
            Layout.maximumWidth: 640
            Layout.preferredWidth: 640
            Layout.preferredHeight: 360
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            // color: "red"
            Layout.fillHeight: true
            Layout.fillWidth: true

            source: video_cam00
            filters: [ videoFilter_00 ]
            focus: true
            Keys.onSpacePressed: video.playbackState === MediaPlayer.PlayingState ? video.pause() : video.play()
            Keys.onLeftPressed: video.seek(video.position - 5000)
            Keys.onRightPressed: video.seek(video.position + 5000)
        }

        VideoOutput {
            id: videoOutput_cam01
            Layout.maximumWidth: 640
            Layout.preferredWidth: 640
            Layout.preferredHeight: 360
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            // color: "blue"
            Layout.fillHeight: true
            Layout.fillWidth: true

            source: video_cam01
            filters: [ videoFilter_01 ]
            Keys.onSpacePressed: video.playbackState === MediaPlayer.PlayingState ? video.pause() : video.play()
            Keys.onLeftPressed: video.seek(video.position - 5000)
            Keys.onRightPressed: video.seek(video.position + 5000)
        }
    }
}
