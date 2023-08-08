#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include "ui/components/widget.h"

class HeaderLabel;
class SecondaryLabel;
class FieldLineEdit;
class WelcomeButton;
class IconButton;
class PhoneLineEdit;
class PasswordLineEdit;

class RegistrationPage : public Widget
{
    Q_OBJECT
public:
    explicit RegistrationPage(QWidget *parent = nullptr);

signals:
    void backButtonClicked();
    void toLoginPageClicked();

private slots:
    void sendRegisterMessage();

    void onLineEditsChanged();

protected:
    void showEvent(QShowEvent *event) override;

private:
    void setupUi();

private:
    HeaderLabel    *tellUsAboutLabel_ = nullptr;
    SecondaryLabel *pageInfo_         = nullptr;
    
    FieldLineEdit    *firstNameEdit_       = nullptr;
    FieldLineEdit    *usernameEdit_        = nullptr;
    FieldLineEdit    *emailEdit_           = nullptr;
    PhoneLineEdit    *phoneNumberEdit_     = nullptr;
    PasswordLineEdit *passwordEdit_        = nullptr;
    FieldLineEdit    *confirmPasswordEdit_ = nullptr;
    
    WelcomeButton      *nextButton_ = nullptr;
    IconButton *backButton_ = nullptr;

    SecondaryLabel *toLoginPageLabel_ = nullptr;

};

#endif // REGISTRATIONPAGE_H
