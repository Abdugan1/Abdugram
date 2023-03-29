#include "loginpage.h"
#include "headerlabel.h"
#include "secondarylabel.h"
#include "lineedit.h"
#include "button.h"
#include "imagebutton.h"

#include <QBoxLayout>

#include <net_common/messages/loginmessage.h>

LoginPage::LoginPage(QWidget *parent)
    : QWidget{parent}
{
    setupUi();

    connect(nextButton_, &Button::clicked, this, &LoginPage::sendLoginMessage);

    connect(backButton_, &ImageButton::clicked, this, &LoginPage::backButtonClicked);

    connect(toRegisterPage_, &QLabel::linkActivated, this, &LoginPage::toRegisterPageClicked);

    // line edits
    connect(usernameEdit_, &LineEdit::textChanged, this, &LoginPage::onLineEditsChanged);

    connect(passwordEdit_, &LineEdit::textChanged, this, &LoginPage::onLineEditsChanged);
}

void LoginPage::sendLoginMessage()
{
    AnyMessagePtr<LoginMessage> loginMessage{new LoginMessage};
    loginMessage->setUsername(usernameEdit_->text());
    loginMessage->setPassword(passwordEdit_->text());

    emit loginRequested(static_cast<AbduMessagePtr>(loginMessage));
}

void LoginPage::onLineEditsChanged()
{
    nextButton_->setEnabled(!usernameEdit_->text().isEmpty()
                            && !passwordEdit_->text().isEmpty());
}

void LoginPage::setupUi()
{
    //
    header_ = new HeaderLabel{tr("Log In")};
    header_->setAlignment(Qt::AlignCenter);

    //
    usernameEdit_ = new LineEdit{tr("Username")};
    passwordEdit_ = new LineEdit{tr("Password")};

    //
    nextButton_ = new Button{tr("Next")};
    nextButton_->setEnabled(false);

    //
    toRegisterPage_ = new SecondaryLabel{tr("Do not have an account yet? "
                                            "<a href=\"to_register\" "
                                            "style=\""
                                            "color: #A4508B;"
                                            "text-decoration: underlying;"
                                            "\""
                                            ">Register</a>")};

    //
    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupLayout->addWidget(header_);
    groupLayout->addWidget(usernameEdit_);
    groupLayout->addWidget(passwordEdit_);
    groupLayout->addWidget(nextButton_);
    groupLayout->addWidget(toRegisterPage_);

    groupLayout->setAlignment(Qt::AlignCenter);
    groupLayout->setSpacing(15);

    QWidget *group = new QWidget;
    group->setLayout(groupLayout);
    group->setFixedWidth(600);

    backButton_ = new ImageButton{QPixmap{":/images/BackButton.png"}};

    //
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(backButton_);
    topLayout->addStretch();

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(group, 0, Qt::AlignCenter);

    setLayout(mainLayout);
}
