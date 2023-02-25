#include "problemwidget.h"
#include "secondarylabel.h"

#include <QBoxLayout>
#include <QMovie>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

ProblemWidget::ProblemWidget(QWidget *parent)
    : QWidget{parent}
{
    init("");
}

ProblemWidget::ProblemWidget(const QString &text, QWidget *parent)
    : QWidget{parent}
{
    init(text);
}

void ProblemWidget::setText(const QString &text)
{
    text_->setText(text);
}

void ProblemWidget::setSizeByTemplateText(const QString &text)
{
    QString oldText = text_->text();
    text_->setText(text);
    resize(layout()->sizeHint());
    text_->setText(oldText);
}

void ProblemWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor{0x18, 0x18, 0x18 /*"#181818"*/});
    painter.drawRoundedRect(rect(), height() / 2, height() / 2);

    QWidget::paintEvent(event);
}

void ProblemWidget::init(const QString &text)
{
    busyIndicator_ = new QLabel;
    busyIndicator_->resize(30, 18);
    QMovie *gif = new QMovie{":/images/busy.gif"};
    gif->setParent(busyIndicator_);
    gif->setScaledSize(busyIndicator_->size());
    busyIndicator_->setMovie(gif);
    gif->start();

    text_ = new SecondaryLabel{text};
    text_->setObjectName("small-font");

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(busyIndicator_);
    hLayout->addWidget(text_);
    int vm = 3;
    int hm = 15;
    hLayout->setContentsMargins(hm, vm, hm, vm);
    hLayout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    setLayout(hLayout);
    resize(hLayout->sizeHint());

    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setColor(QColor{0x82, 0x82, 0x82, int(255 * 0.5)});
    shadow->setOffset(0, 0);

    setGraphicsEffect(shadow);
}
