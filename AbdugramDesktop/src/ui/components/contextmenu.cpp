#include "ui/components/contextmenu.h"
#include "ui/components/contextmenuprivate.h"

#include <QCloseEvent>
#include <QPainter>
#include <QStyleOptionMenuItem>
#include <QPainterPath>
#include <QDebug>

ContextMenu::ContextMenu(QWidget *parent)
    : QMenu{parent}
    , d_ptr{new ContextMenuPrivate{this}}
{
    d_ptr->init();
}

ContextMenu::~ContextMenu()
{

}

void ContextMenu::openMenu(const QPoint &pos)
{
    Q_D(ContextMenu);
    d->openMenu(pos);
}

void ContextMenu::closeMenu()
{
    Q_D(ContextMenu);
    d->closeMenu();
}

void ContextMenu::closeEvent(QCloseEvent *event)
{
    Q_D(ContextMenu);
    if (d->canClose) {
        event->accept();
    } else {
        event->ignore();
        closeMenu();
    }
}

void ContextMenu::paintEvent(QPaintEvent *event)
{
    Q_D(ContextMenu);

    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(d->backgroundColor);

    QPainterPath background;
    background.addRoundedRect(rect(), d->cornerRadius, d->cornerRadius);

    painter.setClipping(true);
    painter.setClipPath(background);

    painter.drawRect(rect());

    painter.setPen(d->textColor);

    const auto actions = this->actions();
    for (const auto action : actions) {
        const QRect   actionGeometry = this->actionGeometry(action);

        QStyleOptionMenuItem option;
        initStyleOption(&option, action);

        if (option.state & QStyle::State_Selected) {
            painter.fillRect(actionGeometry, d->highlightColor);
        }

        if (!action->icon().isNull()) {
            const QPixmap icon = action->icon().pixmap(d->iconSize);
            QPoint iconDrawPoint = actionGeometry.topLeft();
            iconDrawPoint.rx() += d->leftMargin;
            iconDrawPoint.ry() = actionGeometry.center().y() - d->iconSize.height() / 2;
            painter.drawPixmap(iconDrawPoint, icon);
        }

        QPoint textDrawPoint = actionGeometry.bottomLeft();
        textDrawPoint.rx() += d->leftMargin + d->iconSize.width() + d->spacing;
        textDrawPoint.ry() = actionGeometry.center().y() + option.fontMetrics.ascent() / 2;

        painter.drawText(textDrawPoint, action->text());

    }
}
