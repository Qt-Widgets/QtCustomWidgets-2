#ifndef QCPLAYBUTTON_H
#define QCPLAYBUTTON_H

#include <QtGui/qpushbutton.h>

typedef char iconType_t;

class QCPlayButton : public QPushButton
{
	Q_OBJECT

public:

	enum iconType{
		ACTIVE=0,
		DISABLED,
		FOCUSED,
		PRESSED,
	};

	QCPlayButton(QWidget * parent = 0);
	~QCPlayButton();

	bool isPlayMode();

public slots:
	void toggleButton();
	void setPlayingMode(bool flag);

protected:
	bool playing;
	virtual void paintEvent(QPaintEvent * e);
	void loadIcons();

signals:
	void paintedsignal(char x);

private:
	QPixmap* iconPlay_ori[4];
	QPixmap* iconPause_ori[4];
	QPixmap* iconPause[4];
	QPixmap* iconPlay[4];

	iconType_t getIconType(void);
	void paintButton(iconType_t type);
	void ResizeIcons();
};

#endif