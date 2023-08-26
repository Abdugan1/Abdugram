#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H

#include <QListView>

#include <sql_common/data_structures/message.h>

class MessageListModel;
class MessageListDelegate;

class IconButton;

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
    void onMessageAdded(const Message &message);
    void scrollToEndIfNeccessary(const Message &message);
    void showNotificationIfMessageIdIsNotCurrent(const Message &message);

    void onScrollChanged(int value);
    void onScrollRangeChanged(int min, int max);

    void smoothScrollToBottom();

private:
    void setupUi();

    void scrollToEnd();

    void readMessages();
    void readMessagesFromRow(int row);

private:
    MessageListModel    *model_     = nullptr;
    MessageListDelegate *delegate_ = nullptr;

    IconButton *scrollToBottomButton_ = nullptr;

    Message lastMessage_;

    bool autoScroll_ = true;
};

#endif // MESSAGELISTVIEW_H
