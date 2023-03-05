#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

class HeaderLabel;
class SecondaryLabel;
class LineEdit;
class Button;
class ImageButton;

class LoginPage : public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);

signals:
    void backButtonClicked();
    void toRegisterPageClicked();

private:
    void setupUi();

private:
    HeaderLabel *header_ = nullptr;
    LineEdit *usernameEdit_ = nullptr;
    LineEdit *passwordEdit_ = nullptr;
    Button   *nextButton_   = nullptr;
    SecondaryLabel *toRegisterPage_ = nullptr;

    ImageButton *backButton_ = nullptr;
};

#endif // LOGINPAGE_H
