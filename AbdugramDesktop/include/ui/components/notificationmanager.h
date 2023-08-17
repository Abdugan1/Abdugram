#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QObject>
#include <QString>
#include <memory>

#include <list>

class QWidget;

class Notification;
class Button;

class Message;

class NotificationManager : public QObject
{
    Q_OBJECT
public:
    static NotificationManager *instance();

    void init(QWidget *window);

    void addNotification(const Message &message);

    void removeNotificationsWithChatId(int chatId);

signals:
    void pressed(const Message &message);

private slots:
    void removeNotification();
    void removeAllNotifications();
    void updateNotificationsPosition();

private:
    explicit NotificationManager();

    void setAppearPosition(Notification *notification);
    QPoint getStartAppearPosition() const;

private:
    QWidget *window_ = nullptr;

    QList<Notification *> notifications_;
    std::shared_ptr<Button> hideAllButton_ = nullptr;
};

inline NotificationManager *notificationManager()
{
    return NotificationManager::instance();
}

#endif // NOTIFICATIONMANAGER_H
