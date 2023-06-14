#ifndef MESSAGESTABLE_H
#define MESSAGESTABLE_H

class Message;

class MessagesTable
{
public:
    static int addMessage(const Message &message);

    static Message getMessageById(int id);

private:
    explicit MessagesTable() = default;
};

#endif // MESSAGESTABLE_H
