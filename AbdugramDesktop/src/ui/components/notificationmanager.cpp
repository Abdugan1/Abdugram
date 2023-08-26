#include "ui/components/notificationmanager.h"
#include "ui/components/notification.h"
#include "ui/components/button.h"

#include "ui/components/colorrepository.h"

#include <sql_common/data_structures/message.h>

#include <QTimer>
#include <QApplication>
#include <QScreen>
#include <QDebug>

const int Spacing      = 3;
const int RightMargin  = 3;
const int BottomMargin = 3;

NotificationManager *NotificationManager::instance()
{
    static NotificationManager self;
    return &self;
}

void NotificationManager::init(QWidget *window)
{
    window_ = window;
}

void NotificationManager::addNotification(const Message &message)
{
    Q_ASSERT(window_);
    Notification *notification = new Notification{message};
    setAppearPosition(notification);

    connect(notification, &Notification::closed,  this, &NotificationManager::removeNotification);
    connect(notification, &Notification::pressed, this, &NotificationManager::pressed);
    connect(notification, &Notification::pressed, this, [this](const Message &message) {
        removeNotificationsWithChatId(message.chatId());
    });
    notifications_.push_front(notification);

    updateNotificationsPosition();

    notification->show();
    Notification::playSound();
}

void NotificationManager::removeNotificationsWithChatId(int chatId)
{
    const auto begin = std::remove_if(notifications_.begin(), notifications_.end(),
    [chatId](Notification* notification) {
        return notification->message().chatId() == chatId;
    });

    for (auto it = begin; it != notifications_.end(); ++it) {
        (*it)->deleteLater();
    }

    notifications_.erase(begin, notifications_.end());

    updateNotificationsPosition();
}

void NotificationManager::removeNotification()
{
    auto notification = qobject_cast<Notification *>(sender());
    notifications_.removeOne(notification);
    notification->deleteLater();
    updateNotificationsPosition();
}

void NotificationManager::removeAllNotifications()
{
    for (auto notification : qAsConst(notifications_))
        notification->deleteLater();

    notifications_.clear();
    updateNotificationsPosition();
}

void NotificationManager::updateNotificationsPosition()
{
    if (notifications_.empty()) {
        hideAllButton_->hide();
        return;
    }

    const bool disappearing = notifications_.size() <= 1;
    int i = 1;
    const QPoint startPos = getStartAppearPosition();
    for (auto notification : qAsConst(notifications_)) {
        QPoint pos{startPos.x(), startPos.y() - i * (Notification::Height + Spacing)};
        notification->setPosition(pos);
        notification->setDisappearing(disappearing);
        i++;
    }

    if (disappearing) {
        hideAllButton_->hide();
    } else {
        QPoint pos{startPos.x(), startPos.y() - (i - 1) * (Notification::Height + Spacing)
                                     - (hideAllButton_->sizeHint().height() + Spacing)};
        hideAllButton_->move(pos);
        hideAllButton_->show();
    }
}

NotificationManager::NotificationManager()
    : hideAllButton_{new Button{tr("Hide All")}}
{
    hideAllButton_->setTextAlignment(Qt::AlignHCenter);
    hideAllButton_->setTextColor(Colors.value(colornames::decorationColor));
    hideAllButton_->setBackgroundColor(Colors.value(colornames::backgroundLighterHelper3));

    hideAllButton_->setFixedWidth(Notification::Width);

    hideAllButton_->setWindowFlag(Qt::FramelessWindowHint);

    hideAllButton_->setWindowFlags(Qt::FramelessWindowHint |
                                   Qt::Tool |
                                   Qt::WindowStaysOnTopHint);

    hideAllButton_->setAttribute(Qt::WA_TranslucentBackground);
    hideAllButton_->setAttribute(Qt::WA_ShowWithoutActivating);
    
    connect(hideAllButton_.get(), &Button::clicked, this, &NotificationManager::removeAllNotifications);
}

void NotificationManager::setAppearPosition(Notification *notification)
{
    notification->setAppearPosition(getStartAppearPosition());
}

QPoint NotificationManager::getStartAppearPosition() const
{
    const auto windowCenter = window_->geometry().center();

    const auto screen = qApp->screenAt(windowCenter);
    const auto geometry = screen->availableGeometry();

    const auto pos = QPoint{geometry.right()  - Notification::Width  - RightMargin,
                                  geometry.bottom() - BottomMargin};

    return pos;
}
