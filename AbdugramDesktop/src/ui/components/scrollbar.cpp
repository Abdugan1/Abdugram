#include "ui/components/scrollbar.h"

#include <QProxyStyle>
#include <QStyleOptionSlider>
#include <QPainter>

class ScrollBarStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit ScrollBarStyle(QStyle *style = nullptr);

    QRect subControlRect(ComplexControl cc,
                         const QStyleOptionComplex *opt,
                         SubControl sc,
                         const QWidget *widget) const override;

    int pixelMetric(PixelMetric metric,
                    const QStyleOption *option,
                    const QWidget *widget) const override;


    int arrowHeight() const;
    void setArrowHeight(int newArrowHeight);

private:
    int arrowHeight_ = 0;
};

ScrollBarStyle::ScrollBarStyle(QStyle *style)
    : QProxyStyle{style}
{
}

QRect ScrollBarStyle::subControlRect(ComplexControl cc,
                                     const QStyleOptionComplex *opt,
                                     SubControl sc,
                                     const QWidget *widget) const
{
    if (cc == CC_ScrollBar || sc == QStyle::SC_ScrollBarGroove)
    {
        QRect rect = QProxyStyle::subControlRect(cc, opt, sc, widget);
        // Exclude the top and bottom arrows area.
        rect.setTop(rect.top() - arrowHeight_);
        rect.setBottom(rect.bottom() + arrowHeight_);
        return rect;
    }

    // The rect of top and bottom arrows.
    if (sc == QStyle::SC_ScrollBarAddLine || sc == QStyle::SC_ScrollBarSubLine) {
        return QRect();
    }

    return QProxyStyle::subControlRect(cc, opt, sc, widget);
}

int ScrollBarStyle::pixelMetric(PixelMetric metric,
                                const QStyleOption *option,
                                const QWidget *widget) const
{
    switch (metric) {
    case PM_ScrollBarExtent:
        return 6;
    default:
        return QProxyStyle::pixelMetric(metric, option, widget);
    }
}

int ScrollBarStyle::arrowHeight() const
{
    return arrowHeight_;
}

void ScrollBarStyle::setArrowHeight(int newArrowHeight)
{
    arrowHeight_ = newArrowHeight;
}


ScrollBar::ScrollBar(Qt::Orientation orientation, QWidget *parent)
    : QScrollBar{orientation, parent}
{
    auto scrollBarStyle = new ScrollBarStyle;
    setStyle(scrollBarStyle);

    QStyleOptionSlider newScrollbar;
    newScrollbar.initFrom(this);
    scrollBarStyle->setArrowHeight(this->style()->subControlRect(QStyle::CC_ScrollBar,
                                                       &newScrollbar,
                                                       QStyle::SC_ScrollBarAddLine,
                                                                 this).width());
}

void ScrollBar::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor{0x60, 0x5f, 0x5f});

    const auto r = extent() / 2.0;
    painter.drawRoundedRect(handleRect(), r, r);
}

QRect ScrollBar::handleRect() const
{
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    return style()->subControlRect(QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarSlider, this);
}

int ScrollBar::extent() const
{
    return style()->pixelMetric(QStyle::PM_ScrollBarExtent);
}

#include "scrollbar.moc"
