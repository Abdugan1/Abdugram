#include "ui/messagetextedit.h"
#include "ui/imagebutton.h"

#include <QBoxLayout>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>

MessageTextEdit::MessageTextEdit(QWidget *parent)
    : TextEdit{parent}
{
    setupUi();

    connect(sendButton_, &ImageButton::clicked, this, &MessageTextEdit::sendMessage);
    connect(document(), &QTextDocument::contentsChanged, this, &MessageTextEdit::setAppropriateSize);
}

void MessageTextEdit::sendMessage()
{
    const QString text = document()->toPlainText().trimmed();
    clear();

    if (text.isEmpty())
        return;

    emit sendMessageRequest(text);
}

void MessageTextEdit::setAppropriateSize()
{
    static const int MaxHeight = 250;
    const int height = document()->size().height() + contentsMargins().top() + contentsMargins().bottom();
    setMinimumHeight(std::min(height, MaxHeight));
    setMaximumHeight(std::min(height, MaxHeight));
}

void MessageTextEdit::showEvent(QShowEvent *event)
{
    setAppropriateSize();
}

void MessageTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return && !(event->modifiers() & Qt::ShiftModifier)) {
        sendMessage();
    } else {
        TextEdit::keyPressEvent(event);
    }
}

void MessageTextEdit::setupUi()
{
    sendButton_ = new ImageButton{QPixmap{":/images/back_button.png"}};
    sendButton_->setShortcut(QKeySequence{Qt::Key_Return});

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);
    hLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum});
    hLayout->addWidget(sendButton_, 0, Qt::AlignRight | Qt::AlignBottom);

    setLayout(hLayout);

    setPlaceholderText(tr("Write a message..."));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
