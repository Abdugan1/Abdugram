#include "ui/components/problemwidget.h"
#include "ui/components/secondarylabel.h"

#include <QBoxLayout>
#include <QMovie>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

const QString Connecting = QObject::tr("Connecting...");
const QString ReconnectInText = QObject::tr("Reconnecting in %1 s...");
const QString TryNowLink = QObject::tr("<a href=\"reconnect\" "
                                       "style=\""
                                       "color: #A4508B;"
                                       "text-decoration: underline;"
                                       "\""
                                       ">"
                                       "Try now"
                                       "</a>");

ProblemWidget::ProblemWidget(QWidget *parent)
    : QWidget{parent}
{
    init();
}

void ProblemWidget::setTextToConnecting()
{
    reconnectLink_->setVisible(false);
    text_->setFixedWidth(text_->fontMetrics().horizontalAdvance(Connecting));
    text_->setText(Connecting);
    setFixedSize(layout()->sizeHint());
}

void ProblemWidget::setRemainingTime(int remainingSeconds)
{
    reconnectLink_->setVisible(true);
    text_->setFixedWidth(text_->fontMetrics().horizontalAdvance(ReconnectInText.arg("XX")));
    text_->setText(ReconnectInText.arg(QString::number(remainingSeconds)));
    setFixedSize(layout()->sizeHint());
}

void ProblemWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor{0x18, 0x18, 0x18 /*"#181818"*/});
    painter.drawRoundedRect(rect(), height() / 2, height() / 2);

    QWidget::paintEvent(event);
}

void ProblemWidget::init()
{
    busyIndicator_ = new QLabel;
    busyIndicator_->resize(30, 18);
    QMovie *gif = new QMovie{":/images/busy.gif"};
    gif->setParent(busyIndicator_);
    gif->setScaledSize(busyIndicator_->size());
    busyIndicator_->setMovie(gif);
    gif->start();

    text_ = new SecondaryLabel;
    text_->setObjectName("small-font");

    reconnectLink_ = new SecondaryLabel{TryNowLink};
    reconnectLink_->setObjectName("small-font");
    connect(reconnectLink_, &QLabel::linkActivated, this, &ProblemWidget::reconnectNowClicked);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(busyIndicator_);
    hLayout->addWidget(text_);
    hLayout->addWidget(reconnectLink_);
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

    setTextToConnecting();
}
