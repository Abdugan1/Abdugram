#ifndef CHATLISTDELEGATE_H
#define CHATLISTDELEGATE_H

#include <QStyledItemDelegate>

class ChatListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ChatListDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QColor chatNameColor() const;
    void setChatNameColor(const QColor &newChatNameColor);

    QColor lastMessageColor() const;
    void setLastMessageColor(const QColor &newLastMessageColor);

    QColor messageDateColor() const;
    void setMessageDateColor(const QColor &newMessageDateColor);

    QColor highlightColor() const;
    void setHighlightColor(const QColor &newHighlightColor);

private:
    void drawHighlight(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawChatName(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawLastMessage(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageDate(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawSeparator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    bool isContentRectEqual(const QStyleOptionViewItem &option) const;
    void updateContentRect(const QStyleOptionViewItem &option) const;

private:
    static const QMargins AvatarMargins_ ;
    static const QSize    AvatarSize_;

    static const QMargins ChatNameMargins_;
    static const QMargins MessageDateMargins_;

    static const int SeparatorThin_;

    mutable QRect contentRect_;

    QColor chatNameColor_    = Qt::black;
    QColor lastMessageColor_ = Qt::black;
    QColor messageDateColor_ = Qt::black;
    QColor highlightColor_   = Qt::black;
};

#endif // CHATLISTDELEGATE_H
