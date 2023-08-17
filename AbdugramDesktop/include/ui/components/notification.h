#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "ui/components/widget.h"

#include <sql_common/data_structures/message.h>

class QLabel;

class QState;
class QStateMachine;
class QFinalState;

class QTimer;

class SystemButton;
class MainLabel;
class SecondaryLabel;

class Notification : public Widget
{
    Q_OBJECT
public:
    enum {
        Width = 300,
        Height = 80
    };

    explicit Notification(const Message &message);

    bool disappearing() const;
    void setDisappearing(bool newDisappearing);

    void setAppearPosition(const QPoint &pos);
    void setPosition(const QPoint &pos);

    static void playSound();

    Message message() const;

signals:
    void mouseEntered();
    void mouseLeaved();

    void moved();
    void closed();
    void pressed(const Message &message);

protected:
    void showEvent(QShowEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void setupUi();
    void setupStates();

private:
    Message message_;

    QLabel         *avatar_ = nullptr;
    MainLabel      *username_ = nullptr;
    SecondaryLabel *messageText_ = nullptr;

    SystemButton *closeButton_ = nullptr;

    QStateMachine *stateMachine_ = nullptr;

    QState *isNotShowedYet_    = nullptr;
    QState *movingState_       = nullptr;
    QState *showedState_       = nullptr;
    QState *disappearingState_ = nullptr;
    QFinalState *closedState_  = nullptr;

    QTimer *disappearTimer_ = nullptr;
    bool disappearing_ = true;
};

#endif // NOTIFICATION_H
