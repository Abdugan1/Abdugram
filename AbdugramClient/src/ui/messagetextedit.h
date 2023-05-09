#ifndef MESSAGETEXTEDIT_H
#define MESSAGETEXTEDIT_H

#include "textedit.h"

class ImageButton;

class MessageTextEdit : public TextEdit
{
    Q_OBJECT
public:
    explicit MessageTextEdit(QWidget *parent = nullptr);

private slots:
    void setAppropriateSize();

#ifdef Q_OS_LINUX
protected:
    void showEvent(QShowEvent *event) override;
#endif

private:
    void setupUi();
};

#endif // MESSAGETEXTEDIT_H
