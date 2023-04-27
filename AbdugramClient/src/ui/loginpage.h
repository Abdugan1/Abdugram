#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

class HeaderLabel;
class SecondaryLabel;
class FieldLineEdit;
class Button;
class ImageButton;

#include <net_common/messages/abdumessage.h>

class LoginPage : public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);

signals:
    void backButtonClicked();
    void toRegisterPageClicked();

    void loginRequested(const AbduMessagePtr &registerMessage);

private slots:
    void sendLoginMessage();

    void onLineEditsChanged();

protected:
    void showEvent(QShowEvent *event) override;

private:
    void setupUi();

private:
    HeaderLabel *header_ = nullptr;
    FieldLineEdit *usernameEdit_ = nullptr;
    FieldLineEdit *passwordEdit_ = nullptr;
    Button   *nextButton_   = nullptr;
    SecondaryLabel *toRegisterPage_ = nullptr;

    ImageButton *backButton_ = nullptr;
};

#endif // LOGINPAGE_H
