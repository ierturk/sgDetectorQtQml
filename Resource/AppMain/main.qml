import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.9

import QtGStreamer 1.0

import SGDetFilterLib 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("sgDetector")


    VideoItem {
        id: videoGst

        width: window.width
        height: 260
        surface: videoSurface1 //bound on the context from main()
    }

    MediaPlayer {
        id: video
        // source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
        // source: "https://r3---sn-nv47lnsk.googlevideo.com/videoplayback?expire=1566972244&ei=9MRlXYDqBJS8gAeN8rbAAg&ip=95.6.55.163&id=o-AClaGJFgh1_uSrUpebxHw3V4MeKbMN_VWay5cGX8ks7U&itag=22&source=youtube&requiressl=yes&mm=31%2C26&mn=sn-nv47lnsk%2Csn-h0jeen7k&ms=au%2Conr&mv=m&mvi=2&pl=24&initcwndbps=506250&mime=video%2Fmp4&ratebypass=yes&dur=1441.169&lmt=1562204851160945&mt=1566950528&fvip=3&c=WEB&txp=2211222&sparams=expire%2Cei%2Cip%2Cid%2Citag%2Csource%2Crequiressl%2Cmime%2Cratebypass%2Cdur%2Clmt&sig=ALgxI2wwRQIhAOR3NueJn4WSEh1HnFjw4xbnEa4gSOIbsgnl7mgBTU2kAiBiHglZBXADMzBSWp-QkbGP9kdZfhi8j9GtVhhHrLWNZA%3D%3D&lsparams=mm%2Cmn%2Cms%2Cmv%2Cmvi%2Cpl%2Cinitcwndbps&lsig=AHylml4wRAIgTgUfNgbKagjCfkCUxOL4HKc8dK-Emi9rjOkEd5rX3v4CIFcxKbXQGz-KpuyM4xLC-zBvRg-W7mNJ_U2o_fUHY4v2"
        source: "rtsp://192.168.1.66:554/ch01.264?dev=1"
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
/*
    Video {
        id: cam1Stream
        x: 49
        y: 91
        width: 505
        height: 336
        source: "rtsp://admin:rdNN2018@192.168.1.64:554/ch01.264?dev=1"
        autoPlay: true
        opacity: 1.0
        fillMode: Image.Stretch
        muted: false
    }
*/
}

