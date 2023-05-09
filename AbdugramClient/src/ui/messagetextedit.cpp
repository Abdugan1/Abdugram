#include "messagetextedit.h"
#include "imagebutton.h"

#include <QBoxLayout>
#include <QPixmap>
#include <QDebug>

MessageTextEdit::MessageTextEdit(QWidget *parent)
    : TextEdit{parent}
{
    setPlaceholderText(tr("Write a message..."));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(document(), &QTextDocument::contentsChanged, this, &MessageTextEdit::setAppropriateSize);
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
