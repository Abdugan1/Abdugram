#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QScopedPointer>

class Widget;

#include "ui/components/settingswindowprivate.h"
//class SettingsWindowPrivate;
class SettingsWindow : public QWidget
{
    Q_OBJECT

    Q_DECLARE_PRIVATE(SettingsWindow);
public:
    explicit SettingsWindow(QWidget *parent = nullptr);

    void openSettings();
    void closeSettings();

protected:
    void mousePressEvent(QMouseEvent *event) override;

protected:
    const QScopedPointer<SettingsWindowPrivate> d_ptr;
};

#endif // SETTINGSWINDOW_H
