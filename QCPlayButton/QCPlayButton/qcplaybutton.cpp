#include "qcplaybutton.h"
#include <QPaintEvent>
#include <QtGui/qpainter.h>
#include <stdlib.h>

QCPlayButton::QCPlayButton(QWidget * parent)
	: QPushButton(parent)
{
	loadIcons();
	playing = false;
}

QCPlayButton::~QCPlayButton()
{

}

void QCPlayButton::paintEvent(QPaintEvent * e)
{
	paintButton(getIconType());
	emit(paintedsignal(getIconType()));
}

void QCPlayButton::loadIcons(){
	//char* val = getenv("HEM_DIR");
	char* val = "//tsclient/f/Hemobot/Hemobot";
	iconPlay_ori[0] = new QPixmap(QString(val)+"/QTCustomWidgets/QCPlayButton/QCPlayButton/Resources/PlayButton_Style_1/button_play_normal.png");
	iconPlay_ori[1] = new QPixmap(QString(val)+"/QTCustomWidgets/QCPlayButton/QCPlayButton/Resources/PlayButton_Style_1/button_play_disabled.png");
	iconPlay_ori[2] = new QPixmap(QString(val)+"/QTCustomWidgets/QCPlayButton/QCPlayButton/PlayButton_Style_1/button_play_active.png");
	iconPlay_ori[3] = new QPixmap(QString(val)+"/QTCustomWidgets/QCPlayButton/QCPlayButton/PlayButton_Style_1/button_play_pressed.png");

	iconPause_ori[0] = new QPixmap(QString(val)+"/QTCustomWidgets/QCPlayButton/QCPlayButton/PlayButton_Style_1/button_pause_normal.png");
	iconPause_ori[1] = new QPixmap(QString(val)+"/QTCustomWidgets/QCPlayButton/QCPlayButton/PlayButton_Style_1/button_pause_disabled.png");
	iconPause_ori[2] = new QPixmap(QString(val)+"/QTCustomWidgets/QCPlayButton/QCPlayButton/PlayButton_Style_1/button_pause_active.png");
	iconPause_ori[3] = new QPixmap(QString(val)+"/QTCustomWidgets/QCPlayButton/QCPlayButton/PlayButton_Style_1/button_pause_pressed.png");
}

void QCPlayButton::ResizeIcons(){
	int i;
	for(i=0;i<4;i++){
		iconPlay[i] = new QPixmap(iconPlay_ori[i]->scaled(size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		iconPause[i] = new QPixmap(iconPause_ori[i]->scaled(size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	}
}

iconType_t QCPlayButton::getIconType(){
	if (isDown()) return PRESSED;
	if (underMouse()||hasFocus()) return FOCUSED;
	if (isEnabled()) return ACTIVE;
	else return DISABLED;
}

void QCPlayButton::paintButton(iconType_t type){
	ResizeIcons();
	QPainter painter(this);
	if(playing) painter.drawPixmap((width()-iconPause[type]->width())/2,(height()-iconPause[type]->width())/2,*iconPause[type]);
	else painter.drawPixmap((width()-iconPlay[type]->width())/2,(height()-iconPlay[type]->width())/2,*iconPlay[type]);
}

void QCPlayButton::toggleButton(){
	playing=!playing;
	update();
}


void QCPlayButton::setPlayingMode(bool flag){
	if (flag) playing = true;
	else playing = false;
	update();
}

bool QCPlayButton::isPlayMode(){
	if(playing) return true;
	else return false;
}