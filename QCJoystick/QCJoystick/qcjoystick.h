#ifndef QCJOYSTICK_H
#define QCJOYSTICK_H

#include <QObject>
#include "qcmessage.h"
#include "CXBOXController.h"
#include "XInput.h"

#define BUTTONCHECKED true
#define BUTTONUNCHECKED false

#define JSTKUPDATETIME 20


class QCJoystick : public QObject
{
	Q_OBJECT
	QC_MESSAGE

public:

	typedef enum userIp_t{
		DPAD_UP			= 0x0001,
		DPAD_DOWN		= 0x0002,
		DPAD_LEFT		= 0x0004,
		DPAD_RIGHT		= 0x0008,
		START			= 0x0010,
		BACK			= 0x0020,
		LEFT_THUMB		= 0x0040,
		RIGHT_THUMB		= 0x0080,
		LEFT_SHOULDER	= 0x0100,
		RIGHT_SHOULDER	= 0x0200,
		A				= 0x1000,
		B				= 0x2000,
		X				= 0x4000,
		Y				= 0x8000,
		
		LEFT_TRIGGER	= 0x000A,
		RIGHT_TRIGGER	= 0x000B,
		LEFT_THUMB_X	= 0x000C,
		LEFT_THUMB_Y	= 0x000D,
		RIGHT_THUMB_X	= 0x000E,
		RIGHT_THUMB_Y	= 0x000F,
	}userIp;

	QCJoystick(QObject *parent=0);
	~QCJoystick();

	bool connectHardware(bool);
	bool run(bool run);

	bool isAvailable();
	bool isRunning();
	
	void setAnalogOn(bool flag);
	void setResolution(unsigned int value);

	bool getButtonState(userIp button);
	int getAnalogValue(userIp analog);
	
	
	XINPUT_GAMEPAD jState;

signals:
	void userInput(WORD input);
	void running(bool flag);
	
private:
	CXBOXController *joystick;
	int timerId;
	
	XINPUT_GAMEPAD jState_prev;
	bool runningFlag;
	bool analogOnFlag;
	int analogResolution;

	void initialize();
	void emitChange();
	void emitPressedButtons(WORD change);
	void emitAnalog();
	void update();
	void connectH();
	void disconnectH();

protected:
	virtual void timerEvent(QTimerEvent *e);

};




#endif