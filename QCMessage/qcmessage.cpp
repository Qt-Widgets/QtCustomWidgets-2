#include "qcmessage.h"

//QPlainTextEdit* QCMessage::cmdHistBox = 0;

QCMessage::QCMessage(QObject *parent)
	: QObject(parent)
{
	cmdHistBox = NULL;
}

QCMessage::~QCMessage()
{
}


void QCMessage::Memit(const QString& text){
	if(cmdHistBox) cmdHistBox->appendPlainText(": "+text);
	emit(passedMessage(text));
}
 
void QCMessage::setCmdHistBox(QPlainTextEdit *box){
	cmdHistBox = box;
}