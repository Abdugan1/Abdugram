#ifndef MESSAGELISTDELEGATE_H
#define MESSAGELISTDELEGATE_H

#include <QStyledItemDelegate>
#include <QSharedPointer>

class Document;

class MessageListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MessageListDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QModelIndex interactiveIndex() const;
    void setInteractiveIndex(const QModelIndex &newInteractiveIndex);

    QSharedPointer<Document> doc() const;
    void setDoc(QSharedPointer<Document> newDoc);

    int messageHSpacing() const;
    int messageVSpacing() const;

private:
    void setPainterOriginOnMessage(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageTime(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawMessageIsRead(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setPainterOriginOnDateSeparator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawDateSeparatorItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawDateSeparatorBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawDateSeparatorDate(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize messageSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize dateSeparatorSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QRect getDateSeparatorBackgroundRect(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QRect getTextRect(const QString &text, const QFont &font) const;

    QString dateToString(const QModelIndex &index) const;

    int lastLineFullWidth(const QRect &lastLineRect, const QRect &timeRect, bool senderIsMe) const;

private:
    QModelIndex interactiveIndex_;
    QSharedPointer<Document> doc_;

};

#endif // MESSAGELISTDELEGATE_H
