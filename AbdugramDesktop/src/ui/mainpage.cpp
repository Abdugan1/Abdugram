#include "ui/mainpage.h"
#include "ui/sidemenu.h"
#include "ui/sidepanel.h"
#include "ui/conversationside.h"

#include <QPropertyAnimation>
#include <QGraphicsBlurEffect>
#include <QSplitter>
#include <QHBoxLayout>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QDebug>

const auto BlurStart = 0.0;
const auto BlurEnd   = 5.0;

MainPage::MainPage(QWidget *parent)
    : QWidget{parent}
{
    setupUi();
    
    connect(sidePanel_, &SidePanel::selectionWasChanged, conversationSide_, &ConversationSide::setCurrentChatItem);
    connect(sidePanel_, &SidePanel::newChatItemAdded,    conversationSide_, &ConversationSide::updateCurrentChatIfAddedChatIsEqualToAdded);
}

void MainPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    sideMenu_->resize(sideMenu_->width(), this->geometry().height());
}

void MainPage::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        conversationSide_->unsetCurrentChatItem();
        sidePanel_->clearChatSelection();
    }
    QWidget::keyPressEvent(event);
}

void MainPage::setupUi()
{
    sideMenu_ = new SideMenu{this};

    connect(sideMenu_, &SideMenu::aboutToShow, this, &MainPage::makeMainWidgetVisuallyInactive);
    connect(sideMenu_, &SideMenu::aboutToClose, this, &MainPage::makeMainWidgetNormal);

    sidePanel_        = new SidePanel;
    connect(sidePanel_, &SidePanel::sideMenuRequested, sideMenu_, &SideMenu::show);

    conversationSide_ = new ConversationSide;

    splitter_ = new QSplitter;

    splitter_->addWidget(sidePanel_);
    splitter_->addWidget(conversationSide_);

    splitter_->setHandleWidth(1);

    const QList<int> sizes{width() * 1/3, width() * 2/3};
    splitter_->setSizes(sizes);

    blur_ = new QGraphicsBlurEffect;
    blur_->setBlurRadius(BlurStart);
    splitter_->setGraphicsEffect(blur_);

    QHBoxLayout *hLayout = new QHBoxLayout{this};
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);
    hLayout->addWidget(splitter_);

    setLayout(hLayout);
}

void MainPage::makeMainWidgetVisuallyInactive()
{
    QPropertyAnimation *blurAnimation = new QPropertyAnimation{blur_, "blurRadius"};
    blurAnimation->setStartValue(BlurStart);
    blurAnimation->setEndValue(BlurEnd);
    blurAnimation->setEasingCurve(QEasingCurve::OutQuint);
    blurAnimation->setDuration(300);

    blurAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainPage::makeMainWidgetNormal()
{
    QPropertyAnimation *blurAnimation = new QPropertyAnimation{blur_, "blurRadius"};
    blurAnimation->setStartValue(BlurEnd);
    blurAnimation->setEndValue(BlurStart);
    blurAnimation->setEasingCurve(QEasingCurve::OutQuint);
    blurAnimation->setDuration(300);

    blurAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}
