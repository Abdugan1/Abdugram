#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H

#include <QListView>
#include <QSharedPointer>

#include <sql_common/data_structures/message.h>

class MessageListModel;
class MessageListDelegate;

class IconButton;
class Document;

class MessageListView : public QListView
{
    Q_OBJECT
public:
    explicit MessageListView(QWidget *parent = nullptr);

    void setChatId(int chatId);
    void setChatIdWithoutSelect(int chatId);

signals:
    void notificationRequested(const Message &message);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void onSyncFinished();
    void onLoggedOut();

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

    int getRelativeCursorPos(const QSharedPointer<Document> &doc,
                             const QModelIndex &index,
                             const QPoint &mousePos) const;

private:
    MessageListModel    *model_     = nullptr;
    MessageListDelegate *delegate_ = nullptr;

    IconButton *scrollToBottomButton_ = nullptr;

    Message lastMessage_;

    bool autoScroll_ = true;

    QModelIndex previousPressedIndex_;
    QModelIndex pressedIndex_;
    QPoint pressedPos_;

    bool wordSelection_ = false;
};

#endif // MESSAGELISTVIEW_H
