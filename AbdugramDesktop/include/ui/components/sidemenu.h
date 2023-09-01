#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QWidget>

class QLabel;

class QState;

class Button;
class MainLabel;
class SecondaryLabel;
class Widget;

class SideMenu : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset NOTIFY offsetChanged)
    Q_PROPERTY(qreal overlayOpacity READ overlayOpacity WRITE setOverlayOpacity NOTIFY overlayOpacityChanged FINAL)
public:
    explicit SideMenu(QWidget *parent = nullptr);

    int offset() const;
    void setOffset(int newOffset);

    qreal overlayOpacity() const;
    void setOverlayOpacity(qreal newOverlayOpacity);

signals:
    void aboutToShow();
    void aboutToClose();

    void offsetChanged();

    void overlayOpacityChanged();

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private slots:
    void startShowAnimation();
    void closeAnimation();

    void onSyncFinished();

private:
    void setupUi();
    void setupStates();

private:
    enum {
        DrawerWidth = 270
    };

    Widget *background_ = nullptr;

    QLabel    *avatar_   = nullptr;
    MainLabel *username_ = nullptr;
    
    Button *logoutButton_ = nullptr;

    SecondaryLabel *appName_    = nullptr;
    SecondaryLabel *appVersion_ = nullptr;

    int   offset_ = 0;
    qreal overlayOpacity_ = 0.0;

    QState *closedState_ = nullptr;
    QState *showedState_ = nullptr;
};

#endif // SIDEMENU_H
