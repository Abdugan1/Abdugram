#include "ui/passwordlineedit.h"
#include "ui/secondarylabel.h"

#include <QBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QResizeEvent>
#include <QDebug>


PasswordLineEdit::PasswordLineEdit(const QString &placeholder, QWidget *parent)
    : FieldLineEdit{placeholder, parent}
    , toolTip_{ToolTip{}}
{
}

void PasswordLineEdit::focusInEvent(QFocusEvent *event)
{
    FieldLineEdit::focusInEvent(event);
    toolTip_.move(mapToGlobal(rect().bottomLeft()));
    toolTip_.show();
    toolTip_.resize(width(), toolTip_.height());
}

void PasswordLineEdit::focusOutEvent(QFocusEvent *event)
{
    FieldLineEdit::focusOutEvent(event);
    toolTip_.hide();
}

ToolTip::ToolTip()
    : QWidget{}
    , passwordRules_{new SecondaryLabel{tr("Lenght from 8 to 32 characters.\n"
                                           "Must contain capital letter.\n"
                                           "Must contain special character.")}}
{
    QFrame *frame = new QFrame;
    frame->setObjectName("toolTipFrame");
    QVBoxLayout *frameLayout = new QVBoxLayout;
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->addWidget(passwordRules_, 0, Qt::AlignLeft | Qt::AlignVCenter);
    frame->setLayout(frameLayout);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setColor(Qt::black);
    shadow->setBlurRadius(10);
    shadow->setOffset(5);
    frame->setGraphicsEffect(shadow);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 5, 5);
    mainLayout->addWidget(frame);

    setLayout(mainLayout);
    setWindowFlag(Qt::ToolTip);
    setAttribute(Qt::WA_TranslucentBackground);
}
