#include "ui/components/settingswindow.h"
#include "ui/components/settingswindowprivate.h"
#include "ui/components/roundwidget.h"

#include <QMouseEvent>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget{parent}
    , d_ptr{new SettingsWindowPrivate{this}}
{
    d_ptr->init();
}

void SettingsWindow::openSettings()
{
    Q_D(SettingsWindow);
    d->open();
}

void SettingsWindow::closeSettings()
{
    Q_D(SettingsWindow);
    d->close();
}

void SettingsWindow::mousePressEvent(QMouseEvent *event)
{
    Q_D(SettingsWindow);

    if (!d->background->geometry().contains(event->pos())) {
        closeSettings();
    }

    QWidget::mousePressEvent(event);
}
