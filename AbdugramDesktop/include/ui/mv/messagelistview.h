#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H

#include <QListView>

class MessageListModel;
class MessageListDelegate;

class ChatItem;

class Message;

class MessageListView : public QListView
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor timeColor READ timeColor WRITE setTimeColor NOTIFY timeColorChanged)
public:
    explicit MessageListView(QWidget *parent = nullptr);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

    QColor textColor() const;
    void setTextColor(const QColor &newTextColor);

    QColor timeColor() const;
    void setTimeColor(const QColor &newTimeColor);

    void setChatId(int chatId);

signals:
    void backgroundColorChanged();
    void textColorChanged();
    void timeColorChanged();

private slots:
    void scrollToBottomIfSenderIsMe(const Message &message);

private:
    MessageListModel    *model_     = nullptr;
    MessageListDelegate *delegate_ = nullptr;

    // for delegate
    QColor backgroundColor_ = Qt::black;
    QColor textColor_       = Qt::black;
    QColor timeColor_       = Qt::black;
};

#endif // MESSAGELISTVIEW_H
