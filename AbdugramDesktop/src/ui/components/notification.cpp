#include "ui/components/notification.h"
#include "ui/components/titlebar.h"
#include "ui/components/mainlabel.h"
#include "ui/components/secondarylabel.h"

#include "ui/components/colorrepository.h"

#include <sql_client/databaseclient.h>
#include <sql_common/data_structures/user.h>

#include <QBoxLayout>
#include <QApplication>
#include <QScreen>
#include <QStateMachine>
#include <QFinalState>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QSound>
#include <QDebug>

const auto RightMargin  = 3;
const auto BottomMargin = 3;

Notification::Notification(const Message &message)
    : Widget{}
    , message_{message}
{
    setupUi();
    setupStates();

    auto user = database()->getUserById(message.senderId());

    username_->setText(user.username());
    messageText_->setText(message.text());
}

void Notification::showEvent(QShowEvent *event)
{
    if (disappearing_)
        disappearTimer_->start();
    Widget::showEvent(event);
}

void Notification::enterEvent(QEvent *event)
{
    emit mouseEntered();
    disappearTimer_->stop();
    Widget::enterEvent(event);
}

void Notification::leaveEvent(QEvent *event)
{
    emit mouseLeaved();
    if (disappearing_)
        disappearTimer_->start();
    Widget::leaveEvent(event);
}

void Notification::closeEvent(QCloseEvent *event)
{
    Widget::closeEvent(event);
    emit closed();
}

void Notification::mousePressEvent(QMouseEvent *event)
{
    Widget::mousePressEvent(event);
    emit pressed(message_);
    close();
}

void Notification::playSound()
{
    QSound::play("qrc:/sounds/notification.wav");
}

void Notification::setupUi()
{
    avatar_ = new QLabel;
    avatar_->setPixmap(QPixmap{":/images/bear_64.png"}
                           .scaled(QSize{60, 60}, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    username_    = new MainLabel;
    messageText_ = new SecondaryLabel;

    closeButton_ = new SystemButton;
    closeButton_->setDefaultIcon(QIcon{":/images/close.png"});
    closeButton_->setHoverIcon(QIcon{":/images/close_hover.png"});
    closeButton_->setHoverColor(Qt::transparent);
    closeButton_->setFixedSize(closeButton_->iconSize().width() + 10,
                               closeButton_->iconSize().height() + 4);

    connect(closeButton_, &SystemButton::clicked, this, &Notification::close);

    auto textLayout = new QVBoxLayout;
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(0);
    textLayout->addWidget(username_);
    textLayout->addWidget(messageText_);
    textLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Maximum, QSizePolicy::Expanding});

    auto mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(10, 10, 10, 0);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(avatar_, 0, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addLayout(textLayout);
    mainLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum});
    mainLayout->addWidget(closeButton_, 0, Qt::AlignRight | Qt::AlignTop);

    setLayout(mainLayout);
    setFixedSize(QSize{Width, Height});

    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::Tool |
                   Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    setCursor(Qt::PointingHandCursor);

    setBackgroundColor(Colors.value(colornames::backgroundLighterHelper3));
}

void Notification::setupStates()
{
    auto opacityEffect = new QGraphicsOpacityEffect;
    setGraphicsEffect(opacityEffect);

    ////////// States //////////
    stateMachine_ = new QStateMachine{this};

    isNotShowedYet_  = new QState{stateMachine_};
    isNotShowedYet_->assignProperty(this, "pos", QPoint{0, 0});
    isNotShowedYet_->assignProperty(opacityEffect, "opacity", 0.0);

    movingState_ = new QState{stateMachine_};
    movingState_->assignProperty(opacityEffect, "opacity", 1.0);

    showedState_ = new QState{stateMachine_};
    showedState_->assignProperty(opacityEffect, "opacity", 1.0);

    disappearingState_ = new QState{stateMachine_};
    disappearingState_->assignProperty(opacityEffect, "opacity", 0.0);

    closedState_ = new QFinalState{stateMachine_};
    ////////// !States //////////

    disappearTimer_ = new QTimer{this};
    disappearTimer_->setInterval(4500);
    disappearTimer_->setSingleShot(true);

    ////////// Animations //////////
    auto isNotShowYetToMovingAnim = new QPropertyAnimation{this, "pos"};
    isNotShowYetToMovingAnim->setDuration(50);

    auto showedToClosingAnimation = new QPropertyAnimation{opacityEffect, "opacity"};
    showedToClosingAnimation->setDuration(1500);

    auto showedToMovingAnim = new QPropertyAnimation{this, "pos"};
    showedToMovingAnim->setDuration(50);

    auto disappearingToMovingAnim = new QPropertyAnimation{this, "pos"};
    disappearingToMovingAnim->setDuration(50);
    ////////// !Animations //////////

    ////////// Transitions //////////
    auto isNotShowYetToMoving = isNotShowedYet_->addTransition(this, &Notification::moved, movingState_);
    isNotShowYetToMoving->addAnimation(isNotShowYetToMovingAnim);

    movingState_->addTransition(isNotShowYetToMovingAnim, &QPropertyAnimation::finished, showedState_);
    movingState_->addTransition(showedToMovingAnim,       &QPropertyAnimation::finished, showedState_);
    movingState_->addTransition(disappearingToMovingAnim, &QPropertyAnimation::finished, showedState_);

    auto showedToDisappearing = showedState_->addTransition(disappearTimer_, &QTimer::timeout, disappearingState_);
    showedToDisappearing->addAnimation(showedToClosingAnimation);

    auto showedToMoving = showedState_->addTransition(this, &Notification::moved, movingState_);
    showedToMoving->addAnimation(showedToMovingAnim);

    auto disappearingToClosed = disappearingState_->addTransition(showedToClosingAnimation, &QPropertyAnimation::finished, closedState_);

    auto disappearingToMoving = disappearingState_->addTransition(this, &Notification::moved, movingState_);
    disappearingToMoving->addAnimation(disappearingToMovingAnim);

    auto disappearingToShowed = disappearingState_->addTransition(this, &Notification::mouseEntered, showedState_);
    ////////// !Transitions //////////

    connect(stateMachine_, &QStateMachine::finished, this, &Notification::close);

    stateMachine_->setInitialState(isNotShowedYet_);

    stateMachine_->start();
}

Message Notification::message() const
{
    return message_;
}

bool Notification::disappearing() const
{
    return disappearing_;
}

void Notification::setDisappearing(bool newDisappearing)
{
    disappearing_ = newDisappearing;
    if (!disappearing_)
        disappearTimer_->stop();
}

void Notification::setAppearPosition(const QPoint &pos)
{
    move(pos);
    isNotShowedYet_->assignProperty(this, "pos", pos);
}

void Notification::setPosition(const QPoint &pos)
{
    movingState_->assignProperty(this, "pos", pos);

    QTimer::singleShot(1, [this] {
        emit moved();
    });
}
