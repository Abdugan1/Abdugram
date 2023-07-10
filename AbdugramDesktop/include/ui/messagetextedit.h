#ifndef MESSAGETEXTEDIT_H
#define MESSAGETEXTEDIT_H

#include "textedit.h"

class ImageButton;

class MessageTextEdit : public TextEdit
{
    Q_OBJECT
public:
    explicit MessageTextEdit(QWidget *parent = nullptr);

signals:
    void sendMessageRequest(const QString &messageText);

public slots:
    void sendMessage();

private slots:
    void setAppropriateSize();

protected:
    void showEvent(QShowEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    void setupUi();

private:
    ImageButton *sendButton_ = nullptr;
};

#endif // MESSAGETEXTEDIT_H
