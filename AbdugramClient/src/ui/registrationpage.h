#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include <QWidget>

#include <net_common/messages/abdumessage.h>

class HeaderLabel;
class SecondaryLabel;
class FieldLineEdit;
class Button;
class ImageButton;
class PhoneLineEdit;
class PasswordLineEdit;

class RegistrationPage : public QWidget
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
    FieldLineEdit    *lastNameEdit_        = nullptr;
    FieldLineEdit    *usernameEdit_        = nullptr;
    FieldLineEdit    *emailEdit_           = nullptr;
    PhoneLineEdit    *phoneNumberEdit_     = nullptr;
    PasswordLineEdit *passwordEdit_        = nullptr;
    FieldLineEdit    *confirmPasswordEdit_ = nullptr;

    Button      *nextButton_ = nullptr;
    ImageButton *backButton_ = nullptr;

    SecondaryLabel *toLoginPageLabel_ = nullptr;

};

#endif // REGISTRATIONPAGE_H
