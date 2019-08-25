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
        source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
        // source: "https://r3---sn-nv47lnsk.googlevideo.com/videoplayback?expire=1566594496&ei=YAFgXZSGFZHE1gLQ4quABg&ip=95.6.55.163&id=o-AL9kf9iupgeMwCbqJD60lWdQLvP5DEmY-FFg5WCIVgxW&itag=22&source=youtube&requiressl=yes&mm=31%2C26&mn=sn-nv47lnsk%2Csn-h0jeen7k&ms=au%2Conr&mv=m&mvi=2&pl=24&initcwndbps=438750&mime=video%2Fmp4&ratebypass=yes&dur=1441.169&lmt=1562204851160945&mt=1566572818&fvip=3&c=WEB&txp=2211222&sparams=expire%2Cei%2Cip%2Cid%2Citag%2Csource%2Crequiressl%2Cmime%2Cratebypass%2Cdur%2Clmt&sig=ALgxI2wwRQIgd9lRN9EnyWijc3JNck5Ye4zv8wRrhPXPBYCa4WGbsdACIQCfRvihtk_GAiQme5nUSJCsSqhYh7_QYJPS5yI-GhNRrA%3D%3D&lsparams=mm%2Cmn%2Cms%2Cmv%2Cmvi%2Cpl%2Cinitcwndbps&lsig=AHylml4wRgIhALyBHGNYMyFfF5JgFf0IpOAU7jj1_ZF3wlpAL2PhJ-IdAiEAmDP8nhPPns1__r8juqXmFV5lSiF7awJdQJqKEgORw40%3D"
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

