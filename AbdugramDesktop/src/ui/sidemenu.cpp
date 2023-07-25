#include "ui/sidemenu.h"
#include "ui/sidemenubutton.h"
#include "ui/mainlabel.h"
#include "ui/secondarylabel.h"

#include "net/networkhandler.h"

#include <sql_client/databaseclient.h>
#include <sql_common/data_structures/user.h>

#include <QLabel>
#include <QBoxLayout>
#include <QPropertyAnimation>
#include <QFocusEvent>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QFrame>
#include <QDebug>

SideMenu::SideMenu(QWidget *parent)
    : QFrame{parent}
{
    setupUi();

    connect(logoutButton_, &SideMenuButton::clicked, this, []() {networkHandler()->sendLogoutRequest();});
    connect(networkHandler(), &NetworkHandler::syncFinished, this, &SideMenu::onSyncFinished);
}

void SideMenu::showEvent(QShowEvent *event)
{
    startShowAnimation();
    setFocus(Qt::MouseFocusReason);
}

void SideMenu::closeEvent(QCloseEvent *event)
{
    event->ignore();
    closeAnimation();
}

void SideMenu::focusOutEvent(QFocusEvent *event)
{
    if (event->reason() == Qt::ActiveWindowFocusReason)
        return;

    emit lostFocus();
    QFrame::focusOutEvent(event);
}

void SideMenu::startShowAnimation()
{
    QPropertyAnimation *showAnim = new QPropertyAnimation{this, "size"};
    showAnim->setStartValue(QSize{0, height()});
    showAnim->setEndValue(QSize{normalWidth_, height()});
    showAnim->setEasingCurve(QEasingCurve::OutQuint);
    showAnim->setDuration(300);

    showAnim->start(QAbstractAnimation::DeleteWhenStopped);
}

void SideMenu::closeAnimation()
{
    QPropertyAnimation *closeAnim = new QPropertyAnimation{this, "size"};
    closeAnim->setStartValue(QSize{normalWidth_, height()});
    closeAnim->setEndValue(QSize{0, height()});
    closeAnim->setEasingCurve(QEasingCurve::OutQuint);
    closeAnim->setDuration(300);

    connect(closeAnim, &QPropertyAnimation::finished, this, &QWidget::hide);

    closeAnim->start(QAbstractAnimation::DeleteWhenStopped);
}

void SideMenu::onSyncFinished()
{
//    qDebug() <<
    username_->setText(database()->getUserById(networkHandler()->userId()).username());
}

void SideMenu::setupUi()
{
    avatar_ = new QLabel;
    avatar_->setPixmap(QPixmap{":/images/avatar.png"});

    username_ = new MainLabel;

    QFont boldFont;
    boldFont.setBold(true);
    username_->setFont(boldFont);

    QVBoxLayout *avatarLayout = new QVBoxLayout;
    avatarLayout->setContentsMargins(0, 20, 15, 0);
    avatarLayout->setSpacing(0);
    avatarLayout->addWidget(avatar_);
    avatarLayout->addWidget(username_);

    const int leftMargin = 20;

    QVBoxLayout *userInfoLayout = new QVBoxLayout;
    userInfoLayout->setContentsMargins(leftMargin, 0, 0, 0);
    userInfoLayout->setSpacing(0);
    userInfoLayout->addLayout(avatarLayout);
    userInfoLayout->addWidget(username_);

    logoutButton_ = new SideMenuButton{tr("Log out")};

    appName_ = new SecondaryLabel{"Abdugram Desktop"};
    appName_->setFont(boldFont);
    appVersion_ = new SecondaryLabel{tr("Version 0.0.1")};

    QVBoxLayout *appInfoLayout = new QVBoxLayout;
    appInfoLayout->setContentsMargins(leftMargin, 0, 0, 15);
    appInfoLayout->setSpacing(0);
    appInfoLayout->addWidget(appName_);
    appInfoLayout->addWidget(appVersion_);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(userInfoLayout);
    mainLayout->addSpacerItem(new QSpacerItem{1, 10, QSizePolicy::Maximum, QSizePolicy::Fixed});
    mainLayout->addWidget(logoutButton_);
    mainLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Maximum, QSizePolicy::Expanding});
    mainLayout->addLayout(appInfoLayout);

    setLayout(mainLayout);
    setAutoFillBackground(true);

    normalWidth_ = sizeHint().width();
}
