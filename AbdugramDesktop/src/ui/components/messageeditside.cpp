#include "ui/components/messageeditside.h"
#include "ui/components/iconbutton.h"

#include "ui/components/colorrepository.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>

const QMargins TextPadding{7, 10, 7, 10};

MessageTextEdit::MessageTextEdit()
    : QTextEdit{}
{
    setPlaceholderText(tr("Write a message..."));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameStyle(QFrame::NoFrame);
    setViewportMargins(TextPadding);
}

MessageEditSide::MessageEditSide(QWidget *parent)
    : Widget{parent}
{
    setupUi();
    
    connect(sendButton_, &IconButton::clicked, this, &MessageEditSide::sendMessage);
    connect(messageTextEdit_->document(), &QTextDocument::contentsChanged, this, &MessageEditSide::setAppropriateSize);
}

void MessageEditSide::setFocusToTextEdit()
{
    messageTextEdit_->setFocus(Qt::MouseFocusReason);
}

bool MessageEditSide::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        auto keyPressEvent = static_cast<QKeyEvent *>(event);
        if (keyPressEvent->key() == Qt::Key_Return && !(keyPressEvent->modifiers() & Qt::ShiftModifier)) {
            sendMessage();
            return true;
        } else if (keyPressEvent->key() == Qt::Key_Escape) {
            emit escapePressed();
            return true;
        }
    }
    return Widget::eventFilter(watched, event);
}

void MessageEditSide::sendMessage()
{
    const QString text = messageTextEdit_->document()->toPlainText().trimmed();
    messageTextEdit_->clear();

    if (text.isEmpty())
        return;

    emit sendMessageRequest(text);
}

void MessageEditSide::setAppropriateSize()
{
    static const int MaxHeight = 250;
    const int height = messageTextEdit_->document()->size().height() + TextPadding.top() + TextPadding.bottom();
    setFixedHeight(std::min(height, MaxHeight));
}

void MessageEditSide::showEvent(QShowEvent *event)
{
    setAppropriateSize();
    Widget::showEvent(event);
}

void MessageEditSide::setupUi()
{
    messageTextEdit_ = new MessageTextEdit;
    messageTextEdit_->installEventFilter(this);

    sendButton_ = new IconButton{QPixmap{":/images/send.png"}};

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(messageTextEdit_);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setSpacing(0);
    buttonLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Maximum, QSizePolicy::Expanding});
    buttonLayout->addWidget(sendButton_, 0, Qt::AlignCenter);
    buttonLayout->addSpacing(8);

    mainLayout->addLayout(buttonLayout);

    setAppropriateSize();

    setLayout(mainLayout);

    QPalette p = palette();
    p.setColor(QPalette::PlaceholderText, Colors.value(colornames::secondaryLabelColor));
    p.setColor(QPalette::Highlight, Colors.value(colornames::decorationColor));
    p.setColor(QPalette::Text, Colors.value(colornames::mainLabelColor));
    setPalette(p);

    setBackgroundColor(Colors.value(colornames::backgroundLighterHelper1));
}
