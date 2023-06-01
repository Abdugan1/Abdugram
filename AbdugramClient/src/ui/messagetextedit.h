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
#ifdef Q_OS_LINUX
    void showEvent(QShowEvent *event) override;
#endif

    void keyPressEvent(QKeyEvent *event) override;

private:
    void setupUi();
};

#endif // MESSAGETEXTEDIT_H
