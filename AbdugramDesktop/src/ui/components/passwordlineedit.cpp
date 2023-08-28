#include "ui/components/passwordlineedit.h"
#include "ui/components/secondarylabel.h"

#include "ui/components/colorrepository.h"

#include <QPainter>
#include <QBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QStateMachine>
#include <QSignalTransition>
#include <QTimer>
#include <QDebug>

ToolTip::ToolTip(ToolTipLineEdit *lineEdit)
    : QWidget{} // specially default constructor!!
    , icon_{new QLabel}
    , text_{new SecondaryLabel{}}
    , lineEdit_{lineEdit}
{
    setParameters();

    QHBoxLayout *frameLayout = new QHBoxLayout;
    frameLayout->setSizeConstraint(QLayout::SetNoConstraint);
    frameLayout->setContentsMargins(10, 10, 10, 10);
    frameLayout->setSpacing(15);
    frameLayout->addWidget(icon_);
    frameLayout->addWidget(text_, 1, Qt::AlignLeft | Qt::AlignVCenter);

    setLayout(frameLayout);
    setWindowFlag(Qt::ToolTip);
    setAttribute(Qt::WA_TranslucentBackground);

    QFont f = font();
    f.setPointSizeF(f.pointSize() - 0.5);
    setFont(f);

    auto stateMachine = new QStateMachine{this};
    hideState_ = new QState{stateMachine};
    showState_ = new QState{stateMachine};

    const int duration = 100;
    auto showAnimation = new QPropertyAnimation{this, "size"};
    showAnimation->setDuration(duration);
    showAnimation->setEasingCurve(QEasingCurve::OutCubic);

    auto hideAnimation = new QPropertyAnimation{this, "size"};
    hideAnimation->setDuration(duration);
    hideAnimation->setEasingCurve(QEasingCurve::InCubic);

    auto hideToShow = hideState_->addTransition(this, &ToolTip::shouldAppear, showState_);
    hideToShow->addAnimation(showAnimation);

    auto showToHide = showState_->addTransition(this, &ToolTip::shouldDisappear,  hideState_);
    showToHide->addAnimation(hideAnimation);

    connect(hideAnimation, &QPropertyAnimation::finished, this, &ToolTip::hide);

    stateMachine->setInitialState(hideState_);
    stateMachine->start();
}

void ToolTip::setParameters()
{
    switch (type_) {
    case Types::Information:
        setIcon(QPixmap{":/images/information.png"});
        setBackgroundColor(Colors.value(colornames::backgroundLighterHelper2));
        setStrokeColor(Colors.value(colornames::backgroundLighterHelper4));
        setTextColor(Colors.value(colornames::secondaryLabelColor));
        break;
    case Types::Critical:
        setIcon(QPixmap{":/images/critical.png"});
        setBackgroundColor(Colors.value(colornames::pinkyRedColor));
        setStrokeColor(Colors.value(colornames::beautyRedColor));
        setTextColor(Colors.value(colornames::beautyRedColor));
        break;
    }
}

void ToolTip::setIcon(const QPixmap &pixmap)
{
    icon_->setPixmap(pixmap);
}

void ToolTip::setTextColor(const QColor &color)
{
    QPalette p = text_->palette();
    p.setColor(QPalette::WindowText, color);
    text_->setPalette(p);
}

void ToolTip::setBackgroundColor(const QColor &color)
{
    backgroundColor_ = color;
}

void ToolTip::setStrokeColor(const QColor &color)
{
    strokeColor_ = color;
}

ToolTip::Types ToolTip::type() const
{
    return type_;
}

void ToolTip::setType(Types newType)
{
    type_ = newType;
    setParameters();
}

void ToolTip::appear()
{
    const int spacing = 5;
    QPoint pos = lineEdit_->mapToGlobal(lineEdit_->rect().bottomLeft());
    pos.ry() += spacing;
    move(pos);

    updateStates();
    show();
    emit shouldAppear();
}

void ToolTip::disappear()
{
    updateStates();
    emit shouldDisappear();
}

void ToolTip::setText(const QString &text)
{
    text_->setText(text);
}

void ToolTip::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);

    const qreal penWidth = 0.5;
    painter.setPen(QPen{strokeColor_, penWidth});
    painter.setBrush(backgroundColor_);

    QRectF r = rect();
    r = r.marginsRemoved(QMarginsF{penWidth / 2, penWidth / 2, penWidth / 2, penWidth / 2});
    painter.drawRoundedRect(r, Radius, Radius);
}

void ToolTip::updateStates()
{
    const QSize hideSize = QSize{0, 0};
    const QSize showSize = QSize{lineEdit_->size().width(), sizeHint().height()};

    hideState_->assignProperty(this, "size", hideSize);
    showState_->assignProperty(this, "size", showSize);
}

ToolTipLineEdit::ToolTipLineEdit(const QString &placeholder, QWidget *parent)
    : FieldLineEdit{placeholder, parent}
{
}

