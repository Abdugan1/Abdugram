#include "ui/pages/registrationpage.h"

#include "ui/components/fieldlineedit.h"
#include "ui/components/headerlabel.h"
#include "ui/components/secondarylabel.h"
#include "ui/components/welcomebutton.h"
#include "ui/components/iconbutton.h"
#include "ui/components/phonelineedit.h"
#include "ui/components/passwordlineedit.h"
#include "ui/components/regexes.h"

#include "net/networkhandler.h"

#include <QEvent>
#include <QBoxLayout>
#include <QGridLayout>
#include <QRegularExpressionValidator>
#include <QTimer>
#include <QDebug>

class PasswordToolTipShower : public QObject
{
    Q_OBJECT
private:
    std::shared_ptr<ToolTip> toolTip_ = nullptr;

public:
    explicit PasswordToolTipShower(QWidget *parent, std::shared_ptr<ToolTip> toolTip)
        : QObject{parent}
        , toolTip_{toolTip}
    {
        parent->installEventFilter(this);
    }

    bool eventFilter(QObject *watched, QEvent *event) override
    {
        switch (event->type()) {
        case QEvent::FocusIn:
            toolTip_->appear();
            break;
        case QEvent::FocusOut:
            toolTip_->disappear();
            break;
        default:
            break;
        }
        return QObject::eventFilter(watched, event);
    }
};

class UsernameToolTipShower : public QObject
{
    Q_OBJECT
private:
    FieldLineEdit *usernameEdit_ = nullptr;
    std::shared_ptr<ToolTip> toolTip_ = nullptr;
    QTimer checkIsFreeTimer_;
public:
    explicit UsernameToolTipShower(FieldLineEdit *usernameEdit, std::shared_ptr<ToolTip> toolTip)
        : QObject{usernameEdit}
        , usernameEdit_{usernameEdit}
        , toolTip_{toolTip}
    {
        checkIsFreeTimer_.setSingleShot(true);
        checkIsFreeTimer_.setInterval(200);

        usernameEdit->installEventFilter(this);

        connect(usernameEdit, &FieldLineEdit::textChanged, this, &UsernameToolTipShower::onTextChanged);

        connect(&checkIsFreeTimer_, &QTimer::timeout, this, &UsernameToolTipShower::onCheckIsFreeTimeout);

        connect(networkHandler(), &NetworkHandler::isUsernameFreeReply, this, &UsernameToolTipShower::onIsUsernameFreeReply);
    }

    bool eventFilter(QObject *watched, QEvent *event) override
    {
        return QObject::eventFilter(watched, event);
    }

private slots:
    void onTextChanged()
    {
        if (!usernameEdit_->text().isEmpty()) {
            checkIsFreeTimer_.start();
        } else {
            checkIsFreeTimer_.stop();
            usernameEdit_->showValidInputState();
            toolTip_->disappear();
        }
    }

    void onCheckIsFreeTimeout()
    {
        if (usernameEdit_->hasAcceptableInput())
            networkHandler()->sendIsUsernameFree(usernameEdit_->text());
    }

    void onIsUsernameFreeReply(bool isFree)
    {
        if (isFree) {
            usernameEdit_->showValidInputState();
            toolTip_->disappear();
        } else {
            usernameEdit_->showInvalidInputState();
            toolTip_->appear();
        }
    }
};

RegistrationPage::RegistrationPage(QWidget *parent)
    : Widget{parent}
{
    setupUi();
    
    connect(nextButton_, &WelcomeButton::clicked,
            this,        &RegistrationPage::sendRegisterMessage);
    
    connect(backButton_, &IconButton::clicked,
            this,        &RegistrationPage::backButtonClicked);

    connect(toLoginPageLabel_, &QLabel::linkActivated,
            this,              &RegistrationPage::toLoginPageClicked);

    // line edits
    connect(firstNameEdit_,       &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);

    connect(usernameEdit_,        &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);

    connect(emailEdit_,           &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);

    connect(phoneNumberEdit_,     &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);

    connect(passwordEdit_,        &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);

    connect(confirmPasswordEdit_, &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);

    //
}

void RegistrationPage::sendRegisterMessage()
{
    const QString firstName = firstNameEdit_->text();
    const QString username  = usernameEdit_->text();
    const QString email     = emailEdit_->text();
    const QString phone     = phoneNumberEdit_->getPhone();
    const QString password  = passwordEdit_->text();

    networkHandler()->sendRegisterRequest(firstName, username,  email,
                                          phone,     password);
}

void RegistrationPage::onLineEditsChanged()
{
    nextButton_->setEnabled(firstNameEdit_->isValid()
                            && usernameEdit_->isValid()
                            && emailEdit_->isValid()
                            && phoneNumberEdit_->isValid()
                            && passwordEdit_->isValid()
                            && (confirmPasswordEdit_->text() == passwordEdit_->text()));
}

void RegistrationPage::showEvent(QShowEvent *event)
{
    Widget::showEvent(event);
    firstNameEdit_->setFocus();
}

void RegistrationPage::setupUi()
{
    //
    tellUsAboutLabel_ = new HeaderLabel{tr("Tell Us About You")};
    tellUsAboutLabel_->setAlignment(Qt::AlignCenter);

    pageInfo_         = new SecondaryLabel{tr("Please enter your information "
                                              "in corresponding forms")};
    pageInfo_->setAlignment(Qt::AlignCenter);

    //
    QVBoxLayout *labelsLayout = new QVBoxLayout;
    labelsLayout->addWidget(tellUsAboutLabel_);
    labelsLayout->addWidget(pageInfo_);

    labelsLayout->setSpacing(6);

    // Line edits configuration
    firstNameEdit_ = new FieldLineEdit{tr("First Name")};
    firstNameEdit_->setValidator(new QRegularExpressionValidator{ui::regex::NameRegex});

    usernameEdit_ = new ToolTipLineEdit{tr("Username")};
    usernameEdit_->setValidator(new QRegularExpressionValidator{ui::regex::UsernameRegex});

    auto usernameAlreadyExistToolTip = std::shared_ptr<ToolTip>(new ToolTip{usernameEdit_});
    usernameAlreadyExistToolTip->setType(ToolTip::Critical);
    usernameAlreadyExistToolTip->setText(tr("Username already exists"));

    auto usernameToolTipShower = new UsernameToolTipShower{usernameEdit_, usernameAlreadyExistToolTip};

    emailEdit_ = new FieldLineEdit{tr("Email")};
    emailEdit_->setValidator(new QRegularExpressionValidator{ui::regex::EmailRegex});

    phoneNumberEdit_ = new PhoneLineEdit;

    passwordEdit_ = new ToolTipLineEdit{tr("Password")};
    passwordEdit_->setValidator(new QRegularExpressionValidator{ui::regex::PasswordRegex});
    passwordEdit_->setEchoMode(QLineEdit::Password);

    confirmPasswordEdit_ = new FieldLineEdit{tr("Confirm Password")};
    confirmPasswordEdit_->setEchoMode(QLineEdit::Password);

    auto showHidePasswordButton = new IconButton{QPixmap{":/images/show_password.png"}};
    showHidePasswordButton->setFixedSize(QSize{25, 25});
    connect(showHidePasswordButton, &IconButton::clicked, this, [this, showHidePasswordButton]() {
        passwordEdit_->setEchoMode(passwordEdit_->echoMode() == QLineEdit::Password ? QLineEdit::Normal
                                                                                    : QLineEdit::Password);
        confirmPasswordEdit_->setEchoMode(confirmPasswordEdit_->echoMode() == QLineEdit::Password ? QLineEdit::Normal
                                                                                                  : QLineEdit::Password);
        showHidePasswordButton->setIcon(passwordEdit_->echoMode() == QLineEdit::Password ? QPixmap{":/images/show_password.png"}
                                                                                         : QPixmap{":/images/hide_password.png"});
    });

    auto passwordToolTip = std::shared_ptr<ToolTip>(new ToolTip{passwordEdit_});
    passwordToolTip->setText(tr("8 to 32 characters.\n"
                                "Capital letter.\n"
                                "Special character."));

    auto passwordToolTipShower = new PasswordToolTipShower{passwordEdit_, passwordToolTip};

    auto passwordLayout = new QHBoxLayout;
    passwordLayout->setContentsMargins(0, 0, 0, 0);
    passwordLayout->setSpacing(0);
    passwordLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum});
    passwordLayout->addWidget(showHidePasswordButton);
    passwordEdit_->setLayout(passwordLayout);

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setHorizontalSpacing(50);
    gLayout->setHorizontalSpacing(23);

    gLayout->addWidget(firstNameEdit_,       0, 0);
    gLayout->addWidget(usernameEdit_,        0, 1);
    gLayout->addWidget(emailEdit_,           2, 0, 1, 2);
    gLayout->addWidget(phoneNumberEdit_,     3, 0, 1, 2);
    gLayout->addWidget(passwordEdit_,        4, 0);
    gLayout->addWidget(confirmPasswordEdit_, 4, 1);

    //
    nextButton_ = new WelcomeButton{tr("Next")};
    nextButton_->setEnabled(false);
    nextButton_->setShortcut(QKeySequence{Qt::Key_Return});

    //
    toLoginPageLabel_ = new SecondaryLabel{tr("Already have an account? "
                                              "<a href=\"to_login\""
                                              "style = \""
                                              "color: #A4508B;"
                                              "text-decoration: underlying;"
                                              "\""
                                              ">Login</a>")};

    // Group
    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupLayout->addLayout(labelsLayout);
    groupLayout->addLayout(gLayout);
    groupLayout->addWidget(nextButton_);
    groupLayout->addWidget(toLoginPageLabel_);

    groupLayout->setAlignment(Qt::AlignCenter);
    groupLayout->setSpacing(15);

    QWidget *group = new QWidget;
    group->setLayout(groupLayout);
    group->setFixedWidth(550);

    // Back button
    backButton_ = new IconButton{QPixmap{":/images/back_button.png"}};

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

#include "registrationpage.moc"
