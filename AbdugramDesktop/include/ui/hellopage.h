#ifndef HELLOPAGE_H
#define HELLOPAGE_H

#include <QWidget>

class MainLabel;
class SecondaryLabel;
class WelcomeButton;

class HelloPage : public QWidget
{
    Q_OBJECT
public:
    explicit HelloPage(QWidget *parent = nullptr);

signals:
    void startMessagingClicked();

private:
    void setupUi();

private:
    MainLabel       *appNameLabel_ = nullptr;
    SecondaryLabel  *welcomeLabel_ = nullptr;
    WelcomeButton          *startButton_  = nullptr;

};

#endif // HELLOPAGE_H
