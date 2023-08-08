#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include "ui/components/widget.h"

class HeaderLabel;
class SecondaryLabel;
class FieldLineEdit;
class WelcomeButton;
class IconButton;

#include <net_common/messages/abdumessage.h>

class LoginPage : public Widget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);

signals:
    void backButtonClicked();
    void toRegisterPageClicked();

private slots:
    void onNextButtonClicked();

    void onLineEditsChanged();

protected:
    void showEvent(QShowEvent *event) override;

private:
    void setupUi();

private:
    HeaderLabel *header_ = nullptr;
    FieldLineEdit *usernameEdit_ = nullptr;
    FieldLineEdit *passwordEdit_ = nullptr;
    WelcomeButton   *nextButton_   = nullptr;
    SecondaryLabel *toRegisterPage_ = nullptr;
    
    IconButton *backButton_ = nullptr;
};

#endif // LOGINPAGE_H
