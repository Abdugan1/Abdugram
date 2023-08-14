#include "ui/components/sidemenu.h"
#include "ui/components/button.h"
#include "ui/components/mainlabel.h"
#include "ui/components/secondarylabel.h"
#include "ui/components/widget.h"

#include "net/networkhandler.h"

#include <sql_client/databaseclient.h>
#include <sql_common/data_structures/user.h>

#include <QLabel>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QDebug>

SideMenu::SideMenu(QWidget *parent)
    : QWidget{parent}
{
    setupUi();
    
    connect(logoutButton_, &Button::clicked, this, []() {networkHandler()->sendLogoutRequest();});
    connect(logoutButton_, &Button::clicked, this, &SideMenu::close);
    connect(networkHandler(), &NetworkHandler::syncFinished, this, &SideMenu::onSyncFinished);

    parent->installEventFilter(this);
}

bool SideMenu::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::Resize:
    {
        auto r = parentWidget()->geometry();
        r.setWidth(r.width() + DrawerWidth);
        setGeometry(parentWidget()->geometry());
        break;
    }
    default:
        break;
    }
    return QWidget::eventFilter(watched, event);
}

void SideMenu::showEvent(QShowEvent *event)
{
    emit aboutToShow();
    raise();
    startShowAnimation();
    setFocus(Qt::MouseFocusReason);

    setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void SideMenu::closeEvent(QCloseEvent *event)
{
    emit aboutToClose();
    event->ignore();
    closeAnimation();

    setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void SideMenu::mousePressEvent(QMouseEvent *event)
{
    if (!background_->geometry().contains(event->pos())) {
        close();
    }
    return QWidget::mousePressEvent(event);
}

void SideMenu::startShowAnimation()
{
    QPropertyAnimation *showAnim = new QPropertyAnimation{this, "offset"};
    showAnim->setStartValue(-DrawerWidth);
    showAnim->setEndValue(0);
    showAnim->setEasingCurve(QEasingCurve::OutCubic);
    showAnim->setDuration(250);

    showAnim->start(QAbstractAnimation::DeleteWhenStopped);
}

void SideMenu::closeAnimation()
{
    QPropertyAnimation *closeAnim = new QPropertyAnimation{this, "offset"};
    closeAnim->setStartValue(0);
    closeAnim->setEndValue(-DrawerWidth);
    closeAnim->setEasingCurve(QEasingCurve::OutCubic);
    closeAnim->setDuration(250);

    connect(closeAnim, &QPropertyAnimation::finished, this, &QWidget::hide);

    closeAnim->start(QAbstractAnimation::DeleteWhenStopped);
}

void SideMenu::onSyncFinished()
{
    username_->setText(database()->getUserById(networkHandler()->userId()).username());
}

void SideMenu::setupUi()
{
    avatar_ = new QLabel;
    avatar_->setPixmap(QPixmap{":/images/bear_64.png"}.scaled(QSize{50, 50}, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    username_ = new MainLabel;

    QFont boldFont;
    boldFont.setBold(true);
    username_->setFont(boldFont);

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
    logoutButton_->setTextColor("#F64650");

    appName_ = new SecondaryLabel{"Abdugram Desktop"};
    appName_->setFont(boldFont);
    appVersion_ = new SecondaryLabel{tr("Version 0.0.1")};

    QVBoxLayout *appInfoLayout = new QVBoxLayout;
    appInfoLayout->setContentsMargins(leftMargin, 0, 0, 15);
    appInfoLayout->setSpacing(0);
    appInfoLayout->addWidget(appName_);
    appInfoLayout->addWidget(appVersion_);

    QVBoxLayout *backgroundLayout = new QVBoxLayout;
    backgroundLayout->setContentsMargins(0, 0, 0, 0);
    backgroundLayout->setSpacing(0);
    backgroundLayout->addLayout(userInfoLayout);
    backgroundLayout->addSpacerItem(new QSpacerItem{1, 10, QSizePolicy::Maximum, QSizePolicy::Fixed});
    backgroundLayout->addWidget(logoutButton_);
    backgroundLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Maximum, QSizePolicy::Expanding});
    backgroundLayout->addLayout(appInfoLayout);

    background_ = new Widget;
    background_->setFixedWidth(DrawerWidth);
    background_->setLayout(backgroundLayout);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setColor(Qt::black);
    shadow->setBlurRadius(100);
    shadow->setXOffset(5);
    shadow->setYOffset(0);
    background_->setGraphicsEffect(shadow);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(background_);
    mainLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum});

    setLayout(mainLayout);

    hide();
}

int SideMenu::offset() const
{
    return offset_;
}

void SideMenu::setOffset(int newOffset)
{
    if (offset_ == newOffset)
        return;
    offset_ = newOffset;
    setGeometry(rect().translated(offset_, 0));
    emit offsetChanged();
}
