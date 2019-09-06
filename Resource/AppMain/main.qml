import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtMultimedia 5.9
import QtQuick.Layouts 1.12

import SGDetFilterLib 1.0

Window {
    id: mainWindow
    visible: true
    width: 720
    height: 640
    title: qsTr("sgDetector")

    MediaPlayer {
        id: video_cam00
        objectName: "video_cam00"
        autoPlay: true
        // source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
        // source: "gst-pipeline: uridecodebin uri=rtsp://admin:rdNN2018@192.168.1.64:554/ch01.264?dev=1 ! autovideosink sync=false"
        // source: "gst-pipeline: rtspsrc location=rtsp://admin:rdNN2018@192.168.1.64:554/ch01.264?dev=1 ! rtph264depay ! tee name=t t. ! queue ! h264parse ! matroskamux ! filesink location=/home/ierturk/cam_00.mp4 t. ! queue ! decodebin ! autovideosink sync=false"
        // source: "gst-pipeline: filesrc location=/home/ierturk/Work/REPOs/data/20190904_left.mp4 ! decodebin ! videoflip method=clockwise ! autovideosink"
        source: "gst-pipeline: rtspsrc location=rtsp://192.168.1.21:8554/ latency=0 drop-on-latency=true ! rtph264depay ! decodebin ! videoflip method=clockwise ! autovideosink"
    }

    MediaPlayer {
        id: video_cam01
        autoPlay: true
        // source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
        // source: "gst-pipeline: uridecodebin uri=rtsp://192.168.1.66:554/ch01.264?dev=1 ! autovideosink sync=false"
        // source: "gst-pipeline: rtspsrc location=rtsp://192.168.1.66:554/ch01.264?dev=1 ! rtph264depay ! tee name=t t. ! queue ! h264parse ! matroskamux ! filesink location=/home/ierturk/cam_01.mp4 t. ! queue ! decodebin ! autovideosink sync=false"
        source: "gst-pipeline: filesrc location=/home/ierturk/Work/REPOs/data/20190904_right.mp4 ! decodebin ! videoflip method=clockwise ! autovideosink"    }

    GridLayout {
        id: gridLayout
        width: 740
        rows: 1
        columns: 2
        anchors.fill: parent

        VideoOutput {
            id: videoOutput_cam00
            Layout.preferredHeight: 640
            Layout.preferredWidth: 360
            source: video_cam00
            filters: [ videoFilter_00 ]

            focus: true
            Keys.onSpacePressed: video_cam00.playbackState === video_cam00.PlayingState ? video.pause() : video.play()
            Keys.onLeftPressed: video_cam00.seek(video_cam00.position - 5000)
            Keys.onRightPressed: video_cam00.seek(video_cam00.position + 5000)
        }

        VideoOutput {
            id: videoOutput_cam01
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.preferredHeight: 640
            Layout.preferredWidth: 360
            source: video_cam01
            filters: [ videoFilter_00 ]

            Keys.onSpacePressed: video_cam01.playbackState === video_cam01.PlayingState ? video.pause() : video.play()
            Keys.onLeftPressed: video_cam01.seek(video_cam01.position - 5000)
            Keys.onRightPressed: video_cam01.seek(video_cam01.position + 5000)
        }


    }

    SGDetFilter {
        id: videoFilter_00
        orientation: videoOutput_cam00.orientation
    }


}
