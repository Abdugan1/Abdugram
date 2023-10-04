#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H

#include <QListView>
#include <QSharedPointer>

#include <sql_common/data_structures/message.h>

class MessageListModel;
class MessageListDelegate;

class IconButton;
class Document;
class ContextMenu;

class QAction;

class MessageListView;

class MessageTextSelectionHelper
{
public:
    explicit MessageTextSelectionHelper(MessageListView *view);

    void handleMousePress(QMouseEvent *event);
    void handleMouseMove(QMouseEvent *event);
    void handleMouseDoubleClick(QMouseEvent *event);

private:
    bool leftButtonPressed(const QMouseEvent *event) const;

    bool isMessageItem(const QModelIndex &index) const;

    int relativeTextCursorPos(const QSharedPointer<Document> &doc,
                              const QModelIndex &index,
                              const QPoint &mousePos) const;

private:
    MessageListView *view_ = nullptr;

    QModelIndex previousPressedIndex_;
    QModelIndex pressedIndex_;
    QPoint pressedPos_;

    bool wordSelection_ = false;
};

class MessageListViewContextMenuHelper
{
public:
    explicit MessageListViewContextMenuHelper(MessageListView *view);

    void popup(const QModelIndex &indexUnderMouse, const QPoint &pos);

private:
    void initContextMenus();

private:
    MessageListView *view_ = nullptr;

    ContextMenu *contextMenu_ = nullptr;
    QAction *copyAction_ = nullptr;

    QModelIndex lastIndex_;
};

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

    void onContextMenuRequested(const QPoint &pos);

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

    QSharedPointer<MessageTextSelectionHelper> textSelectionHelper_;
    QSharedPointer<MessageListViewContextMenuHelper> contextMenuHelper_;

    friend class MessageTextSelectionHelper;
};

#endif // MESSAGELISTVIEW_H
