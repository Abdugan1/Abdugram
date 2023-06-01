#include "messagetextedit.h"
#include "imagebutton.h"

#include <QBoxLayout>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>

MessageTextEdit::MessageTextEdit(QWidget *parent)
    : TextEdit{parent}
{
    setPlaceholderText(tr("Write a message..."));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(document(), &QTextDocument::contentsChanged, this, &MessageTextEdit::setAppropriateSize);
}

void MessageTextEdit::sendMessage()
{
    emit sendMessageRequest(document()->toPlainText());
    clear();
}

void MessageTextEdit::setAppropriateSize()
{
    static const int MaxHeight = 250;
    const int height = document()->size().height() + contentsMargins().top() + contentsMargins().bottom();
    setMinimumHeight(std::min(height, MaxHeight));
    setMaximumHeight(std::min(height, MaxHeight));
}

#ifdef Q_OS_LINUX
void MessageTextEdit::showEvent(QShowEvent *event)
{
    setAppropriateSize();
}
#endif

void MessageTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return && !(event->modifiers() & Qt::ShiftModifier)) {
        sendMessage();
    } else {
        TextEdit::keyPressEvent(event);
    }
}
