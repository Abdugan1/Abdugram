#ifndef MESSAGESTABLE_H
#define MESSAGESTABLE_H

class Message;

class MessagesTable
{
public:
    static bool addMessage(const Message &message);

    static Message getMessageById(int id);

    static int lastInsertedId();

private:
    explicit MessagesTable() = default;

    static int lastInsertedId_;
};

#endif // MESSAGESTABLE_H
