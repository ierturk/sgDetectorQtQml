import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.9

Video {
    id: video
    width : 800
    height : 600
    source: "file:///home/ierturk/Work/REPOs/ssd/yoloData/VID_20190627_191450.mp4"
    
    MouseArea {
        anchors.fill: parent
        onClicked: {
            video.play()
        }
    }
    
    focus: true
    Keys.onSpacePressed: video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
    Keys.onLeftPressed: video.seek(video.position - 5000)
    Keys.onRightPressed: video.seek(video.position + 5000)
}
