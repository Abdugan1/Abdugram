#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H

#include <QListView>

class MessageListModel;
class MessageListDelegate;

class Message;

class MessageListView : public QListView
{
    Q_OBJECT
public:
    explicit MessageListView(QWidget *parent = nullptr);

    void setChatId(int chatId);
    void setChatIdWithoutSelect(int chatId);

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
