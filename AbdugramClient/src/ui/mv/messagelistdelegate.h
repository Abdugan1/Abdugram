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

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

    QColor textColor() const;
    void setTextColor(const QColor &newTextColor);

    QColor timeColor() const;
    void setTimeColor(const QColor &newTimeColor);

private:
    void setPainterOrigin(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawTime(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    static QRect getBackgroundRect(const QStyleOptionViewItem &option, const QModelIndex &index);
    static QRect getTextRect(const QString &text, const QStyleOptionViewItem &option);

private:
    QColor backgroundColor_ = Qt::black;
    QColor textColor_       = Qt::black;
    QColor timeColor_       = Qt::black;

    static const int MaxWidth_;
    static const int Radius_;
    static const int TempMyId_;

    static const int HMargin_;
    static const int VMargin_;

    static const QMargins BackgroundPaddings_;
};

#endif // MESSAGELISTDELEGATE_H
