#include "ui/components/settingswindowprivate.h"
#include "ui/components/settingswindow.h"
#include "ui/components/roundwidget.h"
#include "ui/components/iconbutton.h"
#include "ui/components/mainlabel.h"
#include "ui/components/secondarylabel.h"

#include "ui/components/colorrepository.h"

#include <QPropertyAnimation>
#include <QStateMachine>
#include <QSignalTransition>
#include <QLabel>
#include <QBoxLayout>

SettingsWindowPrivate::SettingsWindowPrivate(SettingsWindow *q)
    : QObject{q}
    , q_ptr{q}
{

}

void SettingsWindowPrivate::init()
{
    Q_Q(SettingsWindow);

    background = new RoundWidget;
    background->setBackgroundColor(Colors.value(colornames::backgroundLighterHelper3));
    background->setCornerRadius(12);
    background->setFixedSize(300, 300);

    title = new MainLabel(tr("Settings"));
    title->setBold(true);

    closeButton = new IconButton(QPixmap(":images/close.png"));

    auto titleBarLayout = new QHBoxLayout;
    titleBarLayout->setContentsMargins(8, 4, 4, 4);
    titleBarLayout->addWidget(title);
    titleBarLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum));
    titleBarLayout->addWidget(closeButton);

    avatar = new QLabel;
    avatar->setPixmap(QPixmap(":/images/bear_64.png"));

    name = new MainLabel("Firstname Lastname");
    name->setBold(true);

    phoneNumber = new MainLabel("+7 777 777 77 77");
    username = new SecondaryLabel("username");

    auto textInfoLayout = new QVBoxLayout;
    textInfoLayout->setContentsMargins(0, 0, 0, 0);
    textInfoLayout->setSpacing(4);
    textInfoLayout->addWidget(name);
    textInfoLayout->addWidget(phoneNumber);
    textInfoLayout->addWidget(username);

    auto infoLayout = new QHBoxLayout;
    infoLayout->setSpacing(20);
    infoLayout->setAlignment(Qt::AlignLeft);
    infoLayout->addWidget(avatar);
    infoLayout->addLayout(textInfoLayout);

    auto backgroundLayout = new QVBoxLayout;
    backgroundLayout->addLayout(titleBarLayout);
    backgroundLayout->addLayout(infoLayout);
    // temp spacing
    backgroundLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Expanding));

    background->setLayout(backgroundLayout);

    auto layout = new QHBoxLayout;
    layout->addWidget(background, 0, Qt::AlignCenter);

    q->hide();
    q->setLayout(layout);

    auto stateMachine = new QStateMachine{q};

    openedState = new QState{stateMachine};
    closedState = new QState{stateMachine};

    auto openedToClosedGeometryAnimation = new QPropertyAnimation{background, "geometry"};
    openedToClosedGeometryAnimation->setDuration(100);
    openedToClosedGeometryAnimation->setEasingCurve(QEasingCurve::InCubic);

    auto openedToClosedOpacityAnimation = new QPropertyAnimation{background, "opacity"};
    openedToClosedOpacityAnimation->setDuration(100);
    openedToClosedOpacityAnimation->setEasingCurve(QEasingCurve::InCubic);


    auto closedToOpenedGeometryAnimation = new QPropertyAnimation{background, "geometry"};
    closedToOpenedGeometryAnimation->setDuration(100);
    closedToOpenedGeometryAnimation->setEasingCurve(QEasingCurve::OutCubic);

    auto closedToOpenedOpacityAnimation = new QPropertyAnimation{background, "opacity"};
    closedToOpenedOpacityAnimation->setDuration(100);
    closedToOpenedOpacityAnimation->setEasingCurve(QEasingCurve::OutCubic);

    auto openedToClosedTransition = openedState->addTransition(this, &SettingsWindowPrivate::closeSignal, closedState);
    openedToClosedTransition->addAnimation(openedToClosedOpacityAnimation);
    openedToClosedTransition->addAnimation(openedToClosedGeometryAnimation);

    auto closedToOpenedTransition = closedState->addTransition(this, &SettingsWindowPrivate::openSignal,  openedState);
    closedToOpenedTransition->addAnimation(closedToOpenedGeometryAnimation);
    closedToOpenedTransition->addAnimation(closedToOpenedOpacityAnimation);

    updateStateValues();

    stateMachine->setInitialState(closedState);
    stateMachine->start();

    QObject::connect(openedToClosedGeometryAnimation, &QPropertyAnimation::finished, q, &SettingsWindow::close);
}

void SettingsWindowPrivate::open()
{
    Q_Q(SettingsWindow);
    q->show();
    updateStateValues();
    emit openSignal();
}

void SettingsWindowPrivate::close()
{
    updateStateValues();
    emit closeSignal();
}

void SettingsWindowPrivate::updateStateValues()
{
    Q_Q(SettingsWindow);
    openedState->assignProperty(background, "opacity", 1.0);

    const QMargins margins(16, 16, 16, 16);
    const QRect fullRect = q->rect().marginsRemoved(margins);
    const QSize preferredSize = background->size();

    const QRect openedRect(QPoint(fullRect.center().x() - preferredSize.width() / 2,
                                  fullRect.center().y() - preferredSize.height() / 2),
                           preferredSize);

    openedState->assignProperty(background, "geometry", openedRect);


    const QRect closedRect(QPoint(fullRect.center().x() + preferredSize.width() / 2,
                                  fullRect.center().y() - preferredSize.height() / 2),
                           QSize(0, 0));

    closedState->assignProperty(background, "opacity", 0.0);
    closedState->assignProperty(background, "geometry", closedRect);
}
