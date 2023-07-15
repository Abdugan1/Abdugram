#ifndef MESSAGELISTDELEGATE_H
#define MESSAGELISTDELEGATE_H

#include <QStyledItemDelegate>

class MessageListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MessageListDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    void setPainterOriginOnMessage(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageTime(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setPainterOriginOnDateSeparator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawDateSeparatorItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawDateSeparatorBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawDateSeparatorDate(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize messageSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize dateSeparatorSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QRect getMessageBackgroundRect(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QRect getDateSeparatorBackgroundRect(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QRect getTextRect(const QString &text, const QFont &font) const;

    QString dateToString(const QModelIndex &index) const;
};

#endif // MESSAGELISTDELEGATE_H
