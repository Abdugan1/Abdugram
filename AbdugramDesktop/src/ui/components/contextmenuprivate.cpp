#include "ui/components/contextmenuprivate.h"
#include "ui/components/contextmenu.h"

#include "ui/components/colorrepository.h"

#include <QProxyStyle>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QApplication>
#include <QDebug>

const int ItemHeight = 37;

class ContextMenuStyle : public QProxyStyle
{
    Q_OBJECT

public:
    QSize sizeFromContents(ContentsType ct,
                           const QStyleOption *opt,
                           const QSize &contentsSize,
                           const QWidget *w) const override;
};

QSize ContextMenuStyle::sizeFromContents(ContentsType ct,
                                         const QStyleOption *opt,
                                         const QSize &contentsSize,
                                         const QWidget *w) const
{
    if (ct == QStyle::CT_MenuItem) {
        QSize size = qApp->style()->sizeFromContents(ct, opt, contentsSize, w);
        return QSize{size.width(), ItemHeight};
    }
    return QCommonStyle::sizeFromContents(ct, opt, contentsSize, w);
}


ContextMenuPrivate::ContextMenuPrivate(ContextMenu *q)
    : q_ptr{q}
{

}

void ContextMenuPrivate::init()
{
    Q_Q(ContextMenu);

    backgroundColor = Colors.value(colornames::backgroundLighterHelper3);
    textColor       = Colors.value(colornames::mainLabelColor);
    highlightColor  = QColor{255, 255, 255, 25};

    canClose = true;

    cornerRadius = 5;

    itemHeight = ItemHeight;

    leftMargin = 10;
    spacing    = 10;

    iconSize = QSize{18, 18};

    q->setAttribute(Qt::WA_TranslucentBackground);
    q->setStyle(new ContextMenuStyle);

    stateMachine = new ContextMenuStateMachine{q};
    QObject::connect(stateMachine, &ContextMenuStateMachine::closed, [this, q]() {
        canClose = true;
        q->close();
    });

    stateMachine->start();
}

void ContextMenuPrivate::openMenu(const QPoint &pos)
{
    Q_Q(ContextMenu);

    canClose = false;

    stateMachine->updatePropertyAssignments();

    q->move(pos);
    q->show();

    emit stateMachine->open();
}

void ContextMenuPrivate::closeMenu()
{
    stateMachine->updatePropertyAssignments();

    emit stateMachine->close();
}

ContextMenuStateMachine::ContextMenuStateMachine(ContextMenu *contextMenu)
    : QStateMachine{contextMenu}
    , contextMenu_{contextMenu}
    , openedState_{new QState}
    , closedState_{new QState}
{
    addState(openedState_);
    addState(closedState_);

    setInitialState(closedState_);

    auto closedToOpenedSizeAnimation = new QPropertyAnimation{contextMenu_, "size"};
    closedToOpenedSizeAnimation->setDuration(100);
    closedToOpenedSizeAnimation->setEasingCurve(QEasingCurve::OutCubic);

    auto openedToClosedSizeAnimation = new QPropertyAnimation{contextMenu_, "size"};
    openedToClosedSizeAnimation->setDuration(40);
    openedToClosedSizeAnimation->setEasingCurve(QEasingCurve::InCubic);

    QObject::connect(openedToClosedSizeAnimation, &QPropertyAnimation::finished,
                     this,                        &ContextMenuStateMachine::closed);

    auto closedToOpenedTransition = closedState_->addTransition(this, &ContextMenuStateMachine::open, openedState_);
    closedToOpenedTransition->addAnimation(closedToOpenedSizeAnimation);

    auto openedToClosedTransition = openedState_->addTransition(this, &ContextMenuStateMachine::close, closedState_);
    openedToClosedTransition->addAnimation(openedToClosedSizeAnimation);

    updatePropertyAssignments();
}

void ContextMenuStateMachine::updatePropertyAssignments()
{
    const QPoint topLeft = contextMenu_->geometry().topLeft();
//    closedState_->assignProperty(contextMenu_, "visible", false);
    closedState_->assignProperty(contextMenu_,  "size", QSize{0, 0});

    const auto sizeHint = contextMenu_->sizeHint();
//    openedState_->assignProperty(contextMenu_, "visible", true);
    openedState_->assignProperty(contextMenu_,  "size", sizeHint);
}

#include "contextmenuprivate.moc"
