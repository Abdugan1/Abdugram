#include "ui/components/drawer.h"
#include "ui/components/button.h"
#include "ui/components/mainlabel.h"
#include "ui/components/secondarylabel.h"
#include "ui/components/widget.h"

#include "ui/components/colorrepository.h"

#include "net/networkhandler.h"

#include <sql_client/databaseclient.h>
#include <sql_common/data_structures/user.h>

#include <QLabel>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QGraphicsDropShadowEffect>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPainter>
#include <QDebug>

Drawer::Drawer(QWidget *parent)
    : OverlayWidget(parent)
{
    setupUi();
    setupStates();

    connect(this, &OverlayWidget::overlayClicked, this, &Drawer::closeDrawer);

    connect(settingsButton_, &Button::clicked, this, &Drawer::settingsRequested);
    connect(settingsButton_, &Button::clicked, this, &Drawer::closeDrawer);

    connect(logoutButton_, &Button::clicked, this, []() {networkHandler()->sendLogoutRequest();});
    connect(logoutButton_, &Button::clicked, this, &Drawer::closeDrawer);
    connect(networkHandler(), &NetworkHandler::syncFinished, this, &Drawer::onSyncFinished);
}

void Drawer::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.setOpacity(overlayOpacity_);
    painter.fillRect(rect(), Qt::SolidPattern);
}

void Drawer::onSyncFinished()
{
    username_->setText(database()->getUserById(networkHandler()->userId()).username());
}

void Drawer::setupUi()
{
    avatar_ = new QLabel;
    avatar_->setPixmap(QPixmap{":/images/bear_64.png"}.scaled(QSize{50, 50}, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    username_ = new MainLabel;
    username_->setBold(true);

    QVBoxLayout *avatarLayout = new QVBoxLayout;
    avatarLayout->setContentsMargins(0, 20, 15, 15);
    avatarLayout->setSpacing(0);
    avatarLayout->addWidget(avatar_);

    const int leftMargin = 20;

    QVBoxLayout *userInfoLayout = new QVBoxLayout;
    userInfoLayout->setContentsMargins(leftMargin, 0, 0, 0);
    userInfoLayout->setSpacing(0);
    userInfoLayout->addLayout(avatarLayout);
    userInfoLayout->addWidget(username_);
    
    logoutButton_ = new Button{tr("Log out"), QIcon{":/images/logout.png"}};
    logoutButton_->setTextColor(Colors.value(colornames::beautyRedColor));

    settingsButton_ = new Button{tr("Settings"), QIcon{":/images/setting.png"}};
    settingsButton_->setTextColor(Colors.value(colornames::mainLabelColor));

    appName_ = new SecondaryLabel{"Abdugram Desktop"};
    appName_->setBold(true);

    appVersion_ = new SecondaryLabel{tr("Version 0.0.1")};

    QVBoxLayout *appInfoLayout = new QVBoxLayout;
    appInfoLayout->setContentsMargins(leftMargin, 0, 0, 15);
    appInfoLayout->setSpacing(0);
    appInfoLayout->addWidget(appName_);
    appInfoLayout->addWidget(appVersion_);

    QVBoxLayout *backgroundLayout = new QVBoxLayout;
    backgroundLayout->setContentsMargins(0, 0, 0, 0);
    backgroundLayout->setSpacing(0);
    backgroundLayout->setSizeConstraint(QLayout::SetNoConstraint);

    backgroundLayout->addLayout(userInfoLayout);
    backgroundLayout->addSpacerItem(new QSpacerItem{1, 10, QSizePolicy::Maximum, QSizePolicy::Fixed});
    backgroundLayout->addWidget(settingsButton_);
    backgroundLayout->addWidget(logoutButton_);
    backgroundLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Maximum, QSizePolicy::Expanding});
    backgroundLayout->addLayout(appInfoLayout);

    Widget *widget = new Widget;
    widget->setFixedWidth(DrawerWidth);
    widget->setLayout(backgroundLayout);

    setWidget(widget);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(widget);
    mainLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum});

    setLayout(mainLayout);

    hide();
}

void Drawer::setupStates()
{
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setColor(QColor{0, 0, 0, 180});
    shadow->setXOffset(5);
    shadow->setYOffset(0);
    widget()->setGraphicsEffect(shadow);

    auto stateMachine = new QStateMachine{this};

    closedState_ = new QState(stateMachine);
    closedState_->assignProperty(this, "offset", -DrawerWidth);
    closedState_->assignProperty(this, "overlayOpacity", 0.0);
    closedState_->assignProperty(shadow, "blurRadius", 0.0);

    closingState_ = new QState(stateMachine);
    closingState_->assignProperty(this, "offset",  0);

    showedState_ = new QState(stateMachine);
    showedState_->assignProperty(this, "offset", 0);
    showedState_->assignProperty(this, "overlayOpacity", 0.2);
    showedState_->assignProperty(shadow, "blurRadius", 20.0);

    showingState_ = new QState(stateMachine);
    showingState_->assignProperty(this, "offset", -DrawerWidth);

    //------------------------------------------------------------------------//
    auto closeOffsetAnim = new QPropertyAnimation{this, "offset"};
    connect(closeOffsetAnim, &QPropertyAnimation::finished, this, &QWidget::hide);
    closeOffsetAnim->setEasingCurve(QEasingCurve::OutCubic);
    closeOffsetAnim->setDuration(200);

    auto closeOverlayOpacityAnim = new QPropertyAnimation{this, "overlayOpacity"};
    connect(closeOverlayOpacityAnim, &QPropertyAnimation::finished, this, QOverload<>::of(&QWidget::update));
    closeOverlayOpacityAnim->setEasingCurve(QEasingCurve::InCubic);
    closeOverlayOpacityAnim->setDuration(50);

    auto closeShadowAnim = new QPropertyAnimation{shadow, "blurRadius"};
    closeShadowAnim->setDuration(250);

    //------------------------------------------------------------------------//

    auto showOffsetAnim = new QPropertyAnimation{this, "offset"};
    showOffsetAnim->setEasingCurve(QEasingCurve::OutCubic);
    showOffsetAnim->setDuration(250);

    auto showOverlayOpacityAnim = new QPropertyAnimation{this, "overlayOpacity"};
    closeOverlayOpacityAnim->setEasingCurve(QEasingCurve::InCubic);
    showOverlayOpacityAnim->setDuration(50);

    auto showShadowAnim = new QPropertyAnimation{shadow, "blurAnimation"};
    showOffsetAnim->setDuration(250);

    //------------------------------------------------------------------------//

    auto closedToShowing = closedState_->addTransition(this, &Drawer::aboutToShow,  showingState_);

    auto showingToShowed = showingState_->addTransition(showingState_, &QState::propertiesAssigned, showedState_);
    showingToShowed->addAnimation(showOffsetAnim);
    showingToShowed->addAnimation(showOverlayOpacityAnim);
    showingToShowed->addAnimation(showShadowAnim);

    auto showedToClosing = showedState_->addTransition(this, &Drawer::aboutToClose, closingState_);

    auto closingToClosed = closingState_->addTransition(closingState_, &QState::propertiesAssigned, closedState_);
    closingToClosed->addAnimation(closeOffsetAnim);
    closingToClosed->addAnimation(closeOverlayOpacityAnim);
    closingToClosed->addAnimation(closeShadowAnim);

    stateMachine->setInitialState(closedState_);
    stateMachine->start();
}

qreal Drawer::overlayOpacity() const
{
    return overlayOpacity_;
}

void Drawer::setOverlayOpacity(qreal newOverlayOpacity)
{
    if (qFuzzyCompare(overlayOpacity_, newOverlayOpacity))
        return;
    overlayOpacity_ = newOverlayOpacity;
    update();
    emit overlayOpacityChanged();
}

void Drawer::openDrawer()
{
    raise();
    setVisible(true);
    setFocus(Qt::MouseFocusReason);

    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    emit aboutToShow();
}

void Drawer::closeDrawer()
{
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    emit aboutToClose();
}

int Drawer::offset() const
{
    return offset_;
}

void Drawer::setOffset(int newOffset)
{
    if (offset_ == newOffset)
        return;
    offset_ = newOffset;
    widget()->setGeometry(widget()->rect().translated(offset_, 0));
    emit offsetChanged();
}
