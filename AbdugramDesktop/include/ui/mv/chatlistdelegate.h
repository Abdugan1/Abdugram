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

private:
    void setPainterOrigin(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void drawChatItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawChatPicture(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawChatName(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawLastMessage(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageDate(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawUnreadMessageCount(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void drawFoundUserItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawUsername(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void drawSectionSeparator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawSectionBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawSectionName(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize chatItemSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sectionSeparatorSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QString dateTimeToString(const QDateTime &dateTime) const;
};

#endif // CHATLISTDELEGATE_H
