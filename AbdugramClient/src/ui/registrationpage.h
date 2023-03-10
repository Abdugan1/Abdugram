#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include <QWidget>

#include <net_common/messages/abdumessage.h>

class HeaderLabel;
class SecondaryLabel;
class LineEdit;
class Button;
class ImageButton;

class RegistrationPage : public QWidget
{
    Q_OBJECT
public:
    explicit RegistrationPage(QWidget *parent = nullptr);

signals:
    void backButtonClicked();
    void toLoginPageClicked();

    void registerRequested(const AbduMessagePtr &registerMessage);

private slots:
    void sendRegisterMessage();

private:
    void setupUi();

private:
    HeaderLabel    *tellUsAboutLabel_ = nullptr;
    SecondaryLabel *pageInfo_         = nullptr;

    LineEdit *firstNameEdit_       = nullptr;
    LineEdit *lastNameEdit_        = nullptr;
    LineEdit *usernameEdit_        = nullptr;
    LineEdit *emailEdit_           = nullptr;
    LineEdit *phoneNumberEdit_     = nullptr;
    LineEdit *passwordEdit_        = nullptr;
    LineEdit *confirmPasswordEdit_ = nullptr;

    Button      *nextButton_ = nullptr;
    ImageButton *backButton_ = nullptr;

    SecondaryLabel *toLoginPageLabel_ = nullptr;
};

#endif // REGISTRATIONPAGE_H
