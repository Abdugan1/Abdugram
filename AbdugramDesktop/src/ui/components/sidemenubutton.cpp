#include "ui/components/sidemenubutton.h"

#include "ui/components/colorrepository.h"

#include "ui/effects/rippleanimation.h"

#include <QStyleOptionButton>
#include <QPainter>
#include <QDebug>

SideMenuButton::SideMenuButton(const QString &text, const QIcon &icon, QWidget *parent)
    : QPushButton{icon, text, parent}
{
    init();
}

void SideMenuButton::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};

    drawBackground(&painter);
    drawIcon(&painter);
    drawText(&painter);

    rippleAnimation_->drawRipple(&painter);
}

void SideMenuButton::init()
{
    setFocusPolicy(Qt::NoFocus);
    setCursor(Qt::PointingHandCursor);
    setIconSize(QSize{15, 15});

    textColor_ = Colors.value(colornames::mainLabelColor);

    rippleAnimation_ = new RippleAnimation{this};
}

void SideMenuButton::drawBackground(QPainter *painter)
{
    QStyleOptionButton opt;
    initStyleOption(&opt);

    if (!(opt.state & QStyle::State_MouseOver))
        return;

    painter->save();

    const auto bgColor = QColor{255, 255, 255, 30};

    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawRect(rect());

    painter->restore();
}

void SideMenuButton::drawIcon(QPainter *painter)
{
    painter->save();

    const auto iconSize = this->iconSize();

    const auto x = LeftMargin;
    const auto y = height() / 2 - iconSize.width() / 2;

    painter->drawPixmap(x, y, icon().pixmap(iconSize));

    painter->restore();
}

void SideMenuButton::drawText(QPainter *painter)
{
    painter->save();

    const auto x = LeftMargin + iconSize().width() + IconTextSpace;
    const auto y = height() / 2 + fontMetrics().ascent() / 2;

    painter->setPen(textColor_);
    painter->drawText(x, y, text());

    painter->restore();
}

QColor SideMenuButton::textColor() const
{
    return textColor_;
}

void SideMenuButton::setTextColor(const QColor &newTextColor)
{
    textColor_ = newTextColor;
}

QSize SideMenuButton::sizeHint() const
{
    return QSize{150, 33};
}
