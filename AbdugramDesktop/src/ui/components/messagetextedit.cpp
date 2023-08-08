#include "ui/components/messagetextedit.h"
#include "ui/components/iconbutton.h"

#include "ui/components/colorrepository.h"

#include <QBoxLayout>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>

const QMargins TextPadding{7, 10, 7, 10};

MessageTextEdit::MessageTextEdit(QWidget *parent)
    : QTextEdit{parent}
{
    setupUi();
    
    connect(sendButton_, &IconButton::clicked, this, &MessageTextEdit::sendMessage);
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
    const int height = document()->size().height() + TextPadding.top() + TextPadding.bottom();
    setFixedHeight(std::min(height, MaxHeight));
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
        QTextEdit::keyPressEvent(event);
    }
}

void MessageTextEdit::setupUi()
{
    sendButton_ = new IconButton{QPixmap{":/images/send.png"}};
    sendButton_->setShortcut(QKeySequence{Qt::Key_Return});

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0, 0, 0, TextPadding.bottom() / 2);
    hLayout->setSpacing(0);
    hLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum});
    hLayout->addWidget(sendButton_, 0, Qt::AlignRight | Qt::AlignBottom);

    setLayout(hLayout);

    setPlaceholderText(tr("Write a message..."));
    setAppropriateSize();

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPalette p = palette();
    p.setColor(QPalette::Base, Colors.value(colornames::backgroundColor));
    p.setColor(QPalette::PlaceholderText, Colors.value(colornames::secondaryLabelColor));
    p.setColor(QPalette::Highlight, Colors.value(colornames::decorationColor));
    p.setColor(QPalette::Text, Colors.value(colornames::mainLabelColor));
    setPalette(p);

    setViewportMargins(TextPadding);
}
