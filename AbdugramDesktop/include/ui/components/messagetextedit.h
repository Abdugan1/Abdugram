#ifndef MESSAGETEXTEDIT_H
#define MESSAGETEXTEDIT_H

#include <QTextEdit>

class IconButton;

class MessageTextEdit : public QTextEdit
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
    IconButton *sendButton_ = nullptr;
};

#endif // MESSAGETEXTEDIT_H
