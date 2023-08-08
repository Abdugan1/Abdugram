#ifndef HELLOPAGE_H
#define HELLOPAGE_H

#include "ui/components/widget.h"

class HeaderLabel;
class SecondaryLabel;
class WelcomeButton;

class HelloPage : public Widget
{
    Q_OBJECT
public:
    explicit HelloPage(QWidget *parent = nullptr);

signals:
    void startMessagingClicked();

private:
    void setupUi();

private:
    HeaderLabel       *appNameLabel_ = nullptr;
    SecondaryLabel  *welcomeLabel_ = nullptr;
    WelcomeButton   *startButton_  = nullptr;

};

#endif // HELLOPAGE_H
