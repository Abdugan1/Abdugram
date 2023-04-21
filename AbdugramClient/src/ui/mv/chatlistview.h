#ifndef CHATLISTVIEW_H
#define CHATLISTVIEW_H

#include <QListView>

class ChatListModel;
class ChatListDelegate;

class ChatListView : public QListView
{
    Q_OBJECT
    Q_PROPERTY(QColor chatNameColor READ chatNameColor WRITE setChatNameColor NOTIFY chatNameColorChanged)
    Q_PROPERTY(QColor lastMessageColor READ lastMessageColor WRITE setLastMessageColor NOTIFY lastMessageColorChanged)
    Q_PROPERTY(QColor messageDateColor READ messageDateColor WRITE setMessageDateColor NOTIFY messageDateColorChanged)
    Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor NOTIFY highlightColorChanged)
public:
    explicit ChatListView(QWidget *parent = nullptr);

    QColor chatNameColor() const;
    void setChatNameColor(const QColor &newChatNameColor);

    QColor lastMessageColor() const;
    void setLastMessageColor(const QColor &newLastMessageColor);

    QColor messageDateColor() const;
    void setMessageDateColor(const QColor &newMessageDateColor);

    QColor highlightColor() const;
    void setHighlightColor(const QColor &newHighlightColor);

signals:
    void chatNameColorChanged();
    void lastMessageColorChanged();
    void messageDateColorChanged();

    void highlightColorChanged();

private:
    ChatListModel    *model_    = nullptr;
    ChatListDelegate *delegate_ = nullptr;

    // For delegate
    QColor chatNameColor_    = Qt::black;
    QColor lastMessageColor_ = Qt::black;
    QColor messageDateColor_ = Qt::black;
    QColor highlightColor_   = Qt::black;
};

#endif // CHATLISTVIEW_H