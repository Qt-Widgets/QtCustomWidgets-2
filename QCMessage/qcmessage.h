#ifndef QCMESSAGE_H
#define QCMESSAGE_H

#include <QString>
#include <QObject>
#include <QPlainTextEdit>
//#include "qcmessage.h"

class QCMessage : public QObject
{
	Q_OBJECT
//	QC_MESSAGE

public:
	QCMessage(QObject *parent = 0);
	~QCMessage();

private:
	QPlainTextEdit *cmdHistBox;

signals:
	void passedMessage(const QString& c);

public slots:
	void Memit(const QString& text);

public:
	void setCmdHistBox(QPlainTextEdit *box);
};


//#define Messaging(x) connect(this.message

#define MESSAGE(x) message.Memit(QString(x))
#define QC_MESSAGE public: QCMessage message;
#define MCONNECT(x) connect(&x->message,SIGNAL(passedMessage(const QString&)),&this->message,SLOT(Memit(const QString&)))
#define MDISPLAY(x) message.setCmdHistBox(x);

#endif