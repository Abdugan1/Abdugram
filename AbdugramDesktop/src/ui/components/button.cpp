#include "ui/components/button.h"

#include "ui/components/colorrepository.h"

#include "ui/effects/rippleanimation.h"

#include <QStyleOptionButton>
#include <QPainter>
#include <QDebug>

Button::Button(const QString &text, const QIcon &icon, QWidget *parent)
    : QPushButton{icon, text, parent}
{
    init();
}

Button::Button(const QString &text, QWidget *parent)
    : QPushButton{text, parent}
{
    init();
}

void Button::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};

    drawBackground(&painter);
    drawText(&painter);

    if (!icon().isNull())
        drawIcon(&painter);

    rippleAnimation_->drawRipple(&painter);
}

void Button::init()
{
    setFocusPolicy(Qt::NoFocus);
    setCursor(Qt::PointingHandCursor);
    setIconSize(QSize{15, 15});

    setContentsMargins(DefaultLeftMargin, DefaultTopMargin, DefaultRightMargin, DefaultBottomMargin);

    textColor_ = Colors.value(colornames::mainLabelColor);

    rippleAnimation_ = new RippleAnimation{this};
}

void Button::drawBackground(QPainter *painter)
{
    QStyleOptionButton opt;
    initStyleOption(&opt);

    painter->save();

    QColor bgColor;
    if (backgroundColor_ == Qt::transparent) {
        bgColor = opt.state & QStyle::State_MouseOver ? QColor{255, 255, 255, 30}
                                                      : backgroundColor_;
    } else {
        bgColor = opt.state & QStyle::State_MouseOver ? backgroundColor_.lighter(130)
                                                      : backgroundColor_;
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawRect(rect());

    painter->restore();
}

void Button::drawIcon(QPainter *painter)
{
    painter->save();

    const auto iconSize = this->iconSize();

    const auto x = contentsMargins().left();
    const auto y = height() / 2 - iconSize.width() / 2;

    painter->drawPixmap(x, y, icon().pixmap(iconSize));

    painter->restore();
}

void Button::drawText(QPainter *painter)
{
    painter->save();

    const auto fm = fontMetrics();
    const auto m  = contentsMargins();
    const auto t  = text();

    int x = 0;
    if (textAlignment_ & Qt::AlignLeft) {
        // Only when left align icon size is needed
        x = icon().isNull() ? m.left() : m.left() + iconSize().width() + iconTextSpacing_;
    } else if (textAlignment_ & Qt::AlignHCenter) {
        x = (width() - fm.horizontalAdvance(t)) / 2;
    } else if (textAlignment_ & Qt::AlignRight) {
        x = width() - fm.horizontalAdvance(t) - m.right();
    }

    const int y = height() / 2 + fm.ascent() / 2;

    painter->setPen(textColor_);
    painter->drawText(x, y, text());

    painter->restore();
}

int Button::iconTextSpacing() const
{
    return iconTextSpacing_;
}

void Button::setIconTextSpacing(int newIconTextSpacing)
{
    iconTextSpacing_ = newIconTextSpacing;
}

Qt::Alignment Button::textAlignment() const
{
    return textAlignment_;
}

void Button::setTextAlignment(const Qt::Alignment &newTextAlignment)
{
    textAlignment_ = newTextAlignment;
}

QColor Button::backgroundColor() const
{
    return backgroundColor_;
}

void Button::setBackgroundColor(const QColor &newBackgroundColor)
{
    backgroundColor_ = newBackgroundColor;
}

QColor Button::textColor() const
{
    return textColor_;
}

void Button::setTextColor(const QColor &newTextColor)
{
    textColor_ = newTextColor;
}

QSize Button::sizeHint() const
{
    return QSize{150, 33};
}
