#ifndef SETTINGSWINDOWPRIVATE_H
#define SETTINGSWINDOWPRIVATE_H

#include <QObject>
#include <QtGlobal>

class QState;
class QLabel;

class RoundWidget;
class IconButton;
class MainLabel;
class SecondaryLabel;

class SettingsWindow;
class SettingsWindowPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(SettingsWindow);
public:
    SettingsWindowPrivate(SettingsWindow *q);

    void init();

    void open();
    void close();

    void updateStateValues();

    SettingsWindow *const q_ptr;

signals:
    void openSignal();
    void closeSignal();

public:
    RoundWidget *background = nullptr;
    MainLabel *title = nullptr;
    IconButton *closeButton = nullptr;

    QLabel *avatar = nullptr;
    MainLabel *name = nullptr;
    MainLabel *phoneNumber = nullptr;
    SecondaryLabel *username = nullptr;

    QState *openedState = nullptr;
    QState *closedState = nullptr;
};

#endif // SETTINGSWINDOWPRIVATE_H
