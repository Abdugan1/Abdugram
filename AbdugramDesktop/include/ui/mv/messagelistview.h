#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H

#include <QListView>

class MessageListModel;
class MessageListDelegate;

class Message;

class MessageListView : public QListView
{
    Q_OBJECT
public:
    explicit MessageListView(QWidget *parent = nullptr);

    void setChatId(int chatId);
    void setChatIdWithoutSelect(int chatId);

signals:
    void notificationRequested(const Message &message);

private slots:
    void scrollToBottomIfSenderIsMeOrIfShouldScroll(const Message &message);
    void showNotificationIfMessageIdIsNotCurrent(const Message &message);

private:
    MessageListModel    *model_     = nullptr;
    MessageListDelegate *delegate_ = nullptr;

    bool shouldScroll_ = true;
};

#endif // MESSAGELISTVIEW_H
