#include "hellopage.h"
#include "button.h"
#include "mainlabel.h"
#include "secondarylabel.h"

#include <QBoxLayout>

inline QSpacerItem *createHSpacer()
{
    return new QSpacerItem{1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum};
}

inline QSpacerItem *createVSpacer()
{
    return new QSpacerItem{1, 1, QSizePolicy::Maximum, QSizePolicy::Expanding};
}

HelloPage::HelloPage(QWidget *parent)
    : QWidget{parent}
{
    setupUi();

    connect(startButton_, &Button::clicked,
            this,         &HelloPage::startMessagingClicked);
}

void HelloPage::setupUi()
{
    appNameLabel_ = new MainLabel{tr("Abdugram Desktop")};
    welcomeLabel_ = new SecondaryLabel{tr("Welcome to the official Abdugram Desktop app.\n"
                                          "It's fast and secure.")};
    welcomeLabel_->setAlignment(Qt::AlignCenter);

    startButton_ = new Button{tr("Start Messaging")};

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addSpacerItem(createVSpacer());
    vLayout->addWidget(appNameLabel_, 0, Qt::AlignCenter);
    vLayout->addWidget(welcomeLabel_, 0, Qt::AlignCenter);
    vLayout->addWidget(startButton_,  0, Qt::AlignCenter);
    vLayout->addSpacerItem(createVSpacer());

    this->setLayout(vLayout);
}
