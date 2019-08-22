import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.9

import SGDetFilterLib 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("sgDetector")

    MediaPlayer {
        id: video
        // source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
        source: "https://r3---sn-nv47lnsk.googlevideo.com/videoplayback?expire=1566537888&ei=QCRfXfXqGoTt1gLElq2gBA&ip=95.6.55.163&id=o-AIJMz9wBf6bnKw2zqMAQ3YifS1ZAqnCdeR5NdLOIQEtY&itag=22&source=youtube&requiressl=yes&mm=31%2C26&mn=sn-nv47lnsk%2Csn-h0jeen7k&ms=au%2Conr&mv=m&mvi=2&pl=24&initcwndbps=421250&mime=video%2Fmp4&ratebypass=yes&dur=1441.169&lmt=1562204851160945&mt=1566516168&fvip=3&c=WEB&txp=2211222&sparams=expire%2Cei%2Cip%2Cid%2Citag%2Csource%2Crequiressl%2Cmime%2Cratebypass%2Cdur%2Clmt&sig=ALgxI2wwRgIhAIYmjMCM_vE-rvsN3Q9P0W8-PAUOmEI1mcKNl6yC2IZ2AiEArAvRkBNgFKWliiHIssXaYbM0Kl5K1hl8yl7FM6OTcXE%3D&lsparams=mm%2Cmn%2Cms%2Cmv%2Cmvi%2Cpl%2Cinitcwndbps&lsig=AHylml4wRQIgTktTP4XduP938p4JWfSbaJpN2kgqYDGti1a5pOOG8O4CIQCs1ea0cOTiiyaYOXk9Wn3s8WimkY46Qder7cl3ESCsYg%3D%3D"
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

