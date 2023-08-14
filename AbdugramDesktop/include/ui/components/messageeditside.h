#ifndef MESSAGETEXTEDIT_H
#define MESSAGETEXTEDIT_H

#include "ui/components/widget.h"
#include <QTextEdit>

class IconButton;

class MessageTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit MessageTextEdit();
};

class MessageEditSide : public Widget
{
    Q_OBJECT
public:
    explicit MessageEditSide(QWidget *parent = nullptr);

    void setFocusToTextEdit();

    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void sendMessageRequest(const QString &messageText);
    void escapePressed();

public slots:
    void sendMessage();

private slots:
    void setAppropriateSize();

protected:
    void showEvent(QShowEvent *event) override;

private:
    void setupUi();

private:
    MessageTextEdit  *messageTextEdit_ = nullptr;
    IconButton *sendButton_ = nullptr;
};

#endif // MESSAGETEXTEDIT_H
