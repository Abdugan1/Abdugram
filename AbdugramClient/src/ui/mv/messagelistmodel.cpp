#include "messagelistmodel.h"
#include "messageitem.h"

MessageListModel::MessageListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    MessageItem nurzhan1;
    nurzhan1.setText("Nurzhan1:\nLorem ipsum dolor sit amet");
    nurzhan1.setDateTime(QDateTime{QDate{2002, 05, 17}, QTime{9, 42}});

    MessageItem nurzhan2;
    nurzhan2.setText("Nurzhan2:\nLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    nurzhan2.setDateTime(QDateTime{QDate{2002, 05, 17}, QTime{9, 42}});

    MessageItem me1;
    me1.setSenderId(0);
    me1.setText("Me1:\nLorem ipsum dolor sit amet, consectetur adipiscing elit");
    me1.setDateTime(QDateTime{QDate{2002, 05, 17}, QTime{9, 42}});

    MessageItem nurzhan3;
    nurzhan3.setText("Nurzhan3:\nLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua");
    nurzhan3.setDateTime(QDateTime{QDate{2002, 05, 17}, QTime{9, 42}});

    messageItems_.append(nurzhan1);
    messageItems_.append(nurzhan2);
    messageItems_.append(me1);
    messageItems_.append(nurzhan3);
}

int MessageListModel::rowCount(const QModelIndex &) const
{
    return messageItems_.count();
}

QVariant MessageListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant{};

    const auto &messageItem = messageItems_.at(index.row());
    switch (role) {
    case Text:     return messageItem.text();     break;
    case DateTime: return messageItem.dateTime(); break;
    case SenderId: return messageItem.senderId(); break;
    }

    return QVariant{};
}
