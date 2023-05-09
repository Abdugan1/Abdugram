#ifndef MESSAGESIDE_H
#define MESSAGESIDE_H

#include <QFrame>

class MessageTextEdit;
class ImageButton;

class MessageSide : public QFrame
{
    Q_OBJECT
public:
    explicit MessageSide(QWidget *parent = nullptr);

private:
    void setupUi();

private:
    MessageTextEdit *messageTextEdit_   = nullptr;
    ImageButton     *sendButton_        = nullptr;
};

#endif // MESSAGESIDE_H
