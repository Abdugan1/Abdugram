#include "ui/components/titlebar.h"

#include "ui/components/colorrepository.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QPainter>
#include <QStyleOptionButton>
#include <QDebug>

#include <FramelessHelper/Widgets/framelesswidgetshelper.h>

FRAMELESSHELPER_USE_NAMESPACE

SystemButton::SystemButton()
    : QPushButton{}
{
    setFocusPolicy(Qt::NoFocus);
    setIconSize(QSize{12, 12});

    setFixedSize(32, 20);

    hoverColor_ = QColor{255, 255, 255, 30};
}

void SystemButton::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);

    QStyleOptionButton opt;
    initStyleOption(&opt);

    const auto hovered = opt.state & QStyle::State_MouseOver;

    QPixmap pixmap = (hovered ? hoverIcon_ : defaultIcon_).pixmap(iconSize());

    const auto r = rect();
    const auto bw = r.width();
    const auto bh = r.height();
    const auto pw = pixmap.width();
    const auto ph = pixmap.height();

    const auto x = bw / 2 - pw / 2;
    const auto y = bh / 2 - ph / 2;

    painter.setPen(Qt::NoPen);

    if (hovered) {
        painter.setBrush(hoverColor_);
        painter.drawRect(r);
    }

    painter.drawPixmap(x, y, pixmap);
}

QIcon SystemButton::defaultIcon() const
{
    return defaultIcon_;
}

void SystemButton::setDefaultIcon(const QIcon &newDefaultIcon)
{
    defaultIcon_ = newDefaultIcon;
}

QIcon SystemButton::hoverIcon() const
{
    return hoverIcon_;
}

void SystemButton::setHoverIcon(const QIcon &newHoverIcon)
{
    hoverIcon_ = newHoverIcon;
}

QColor SystemButton::hoverColor() const
{
    return hoverColor_;
}

void SystemButton::setHoverColor(const QColor &newHoverColor)
{
    hoverColor_ = newHoverColor;
}

TitleBar::TitleBar(QWidget *parent)
    : Widget{parent}
{
    setupUi();
}

void TitleBar::setupUi()
{
    minimizeButton_ = new SystemButton{};
    minimizeButton_->setDefaultIcon(QIcon{":/images/minimize.png"});
    minimizeButton_->setHoverIcon(QIcon{":/images/minimize_hover.png"});
    connect(minimizeButton_, &SystemButton::clicked, parentWidget(), &QWidget::showMinimized);

    maximizeButton_ = new SystemButton{};
    maximizeButton_->setDefaultIcon(QIcon{":/images/maximize.png"});
    maximizeButton_->setHoverIcon(QIcon{":/images/maximize_hover.png"});
    connect(maximizeButton_, &SystemButton::clicked, this, [this]() {
        auto p = parentWidget();
        if (p->isMaximized()) {
            p->showNormal();
            maximizeButton_->setDefaultIcon(QIcon{":/images/maximize.png"});
            maximizeButton_->setHoverIcon(QIcon{":/images/maximize_hover.png"});
        } else {
            p->showMaximized();
            maximizeButton_->setDefaultIcon(QIcon{":/images/show_normal.png"});
            maximizeButton_->setHoverIcon(QIcon{":/images/show_normal_hover.png"});
        }
    });

    closeButton_ = new SystemButton{};
    closeButton_->setDefaultIcon(QIcon{":/images/close.png"});
    closeButton_->setHoverIcon(QIcon{":/images/close_hover.png"});
    closeButton_->setHoverColor(Colors.value(colornames::beautyRedColor));
    connect(closeButton_, &SystemButton::clicked, parentWidget(), &QWidget::close);

    auto hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);
    hLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum});
    hLayout->addWidget(minimizeButton_);
    hLayout->addWidget(maximizeButton_);
    hLayout->addWidget(closeButton_);

    auto framelessHelper = FramelessWidgetsHelper::get(parentWidget());
    framelessHelper->setSystemButton(minimizeButton_, Global::SystemButtonType::Minimize);
    framelessHelper->setSystemButton(maximizeButton_, Global::SystemButtonType::Maximize);
    framelessHelper->setSystemButton(closeButton_,    Global::SystemButtonType::Close   );

    setLayout(hLayout);
    setBackgroundColor(Colors.value(colornames::backgroundLighterHelper2));
}
