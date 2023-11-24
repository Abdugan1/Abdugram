#ifndef DRAWER_H
#define DRAWER_H

#include "ui/components/overlaywidget.h"

class QLabel;

class QState;

class Button;
class MainLabel;
class SecondaryLabel;
class Widget;

class Drawer : public OverlayWidget
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset NOTIFY offsetChanged)
    Q_PROPERTY(qreal overlayOpacity READ overlayOpacity WRITE setOverlayOpacity NOTIFY overlayOpacityChanged FINAL)
public:
    explicit Drawer(QWidget *parent = nullptr);

    int offset() const;
    void setOffset(int newOffset);

    qreal overlayOpacity() const;
    void setOverlayOpacity(qreal newOverlayOpacity);

signals:
    void settingsRequested();

    void aboutToShow();
    void aboutToClose();

    void offsetChanged();

    void overlayOpacityChanged();

public slots:
    void openDrawer();
    void closeDrawer();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onSyncFinished();

private:
    void setupUi();
    void setupStates();

private:
    enum {
        DrawerWidth = 270
    };

    QLabel    *avatar_   = nullptr;
    MainLabel *username_ = nullptr;
    
    Button *logoutButton_   = nullptr;
    Button *settingsButton_ = nullptr;

    SecondaryLabel *appName_    = nullptr;
    SecondaryLabel *appVersion_ = nullptr;

    int   offset_ = 0;
    qreal overlayOpacity_ = 0.0;

    QState *closedState_ = nullptr;
    QState *showedState_ = nullptr;
    QState *showingState_ = nullptr;
    QState *closingState_ = nullptr;
};

#endif // DRAWER_H
