#include "qcjoystick.h"



QCJoystick::QCJoystick(QObject *parent)
:QObject(parent)
{
	initialize();
}


QCJoystick::~QCJoystick(){
}


void QCJoystick::timerEvent(QTimerEvent *e)
{
	//get controller status structure
	//Check for change and emit userInput Signals;
	if(joystick->IsConnected()){
		update();
	}

	else{
		run(false);
	}
}

void QCJoystick::initialize(){
	analogOnFlag = true;
	runningFlag = false;
	analogResolution = 1000;
	joystick = 0;
}




bool QCJoystick::isAvailable(){
	if(joystick) return joystick->IsConnected();
	return false;
}

bool QCJoystick::isRunning(){
	return runningFlag;
}

bool QCJoystick::connectHardware(bool choice){
	if(choice) connectH();
	else disconnectH();
	return isAvailable();
}

void QCJoystick::connectH(){
	if (isAvailable()) return;
	disconnectH();
	joystick = new CXBOXController(1);
}

void QCJoystick::disconnectH(){
	if(isRunning()) {
		run(false);
	}
	if(joystick) {
		delete joystick;
		joystick = 0;
	}
}

bool QCJoystick::run(bool option){
	if(isRunning()!=option){
		if(option){
			if(isAvailable()){
				jState_prev = joystick->GetState().Gamepad;
				timerId = startTimer(JSTKUPDATETIME);
				runningFlag = true;
			}
		}
		else{
			killTimer(timerId);
			runningFlag = false;
		}
	}

	emit(running(runningFlag));
	return runningFlag;
}

void QCJoystick::update(){
	jState = joystick->GetState().Gamepad;
	emitChange();
	jState_prev = jState;
}

void QCJoystick::emitChange(){
	emitPressedButtons(jState_prev.wButtons^jState.wButtons);
	emitAnalog();
}

void QCJoystick::emitPressedButtons(WORD change){
	WORD i = 1;
	while(i && change){
		if(i&change) {
			emit(userInput((WORD)i));
		}
		i<<=1;
	}
}

void QCJoystick::emitAnalog(){
	if(analogOnFlag){ //checks analogOnFlag set by setAnalog(bool) function
		if(jState_prev.bLeftTrigger!=jState.bLeftTrigger) emit(userInput(LEFT_TRIGGER));
		if(jState_prev.bRightTrigger!=jState.bRightTrigger) emit(userInput(RIGHT_TRIGGER));
		if((jState_prev.sThumbLX-jState.sThumbLX)/analogResolution) emit(userInput(LEFT_THUMB_X));
		if((jState_prev.sThumbLY-jState.sThumbLY)/analogResolution) emit(userInput(LEFT_THUMB_Y));
		if((jState_prev.sThumbRX-jState.sThumbRX)/analogResolution) emit(userInput(RIGHT_THUMB_X));
		if((jState_prev.sThumbRY-jState.sThumbRY)/analogResolution) emit(userInput(RIGHT_THUMB_Y));
	}
}

void QCJoystick::setAnalogOn(bool flag){ // sets analogOnFlag
	if(isRunning()){
		killTimer(timerId);
		jState.bLeftTrigger = 0;
		jState.bRightTrigger = 0;
		jState.sThumbLX = 0;
		jState.sThumbLY = 0;
		jState.sThumbRX = 0;
		jState.sThumbRY = 0;
		emitAnalog();
		timerId = startTimer(JSTKUPDATETIME);
	}
	analogOnFlag = flag;
}

void QCJoystick::setResolution(unsigned int value){
	analogResolution = value;
}

bool QCJoystick::getButtonState(userIp button){
	if(button>=0x000A && button<= 0x000F) return false;
	return (button&jState.wButtons)!=0 ;
}
int QCJoystick::getAnalogValue(userIp analog){
	switch(analog){
		case QCJoystick::LEFT_TRIGGER:
			return (int) jState.bLeftTrigger;

		case QCJoystick::RIGHT_TRIGGER:
			return (int)jState.bRightTrigger;

		case QCJoystick::LEFT_THUMB_X:
			return (int)(jState.sThumbLX/analogResolution);

		case QCJoystick::LEFT_THUMB_Y:
			return (int)(jState.sThumbLY/analogResolution);	

		case QCJoystick::RIGHT_THUMB_X:
			return (int)(jState.sThumbRX/analogResolution);

		case QCJoystick::RIGHT_THUMB_Y:
			return (int)(jState.sThumbRY/analogResolution);
	}
	return 0;
}