#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QFrame>

class QLabel;

class SideMenuButton;
class MainLabel;
class SecondaryLabel;

class SideMenu : public QFrame
{
    Q_OBJECT
public:
    explicit SideMenu(QWidget *parent);

signals:
    void lostFocus();

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    void focusOutEvent(QFocusEvent *event) override;

private slots:
    void startShowAnimation();
    void closeAnimation();

    void onLoginResult(bool success);

private:
    void setupUi();

private:
    QLabel    *avatar_   = nullptr;
    MainLabel *username_ = nullptr;

    SideMenuButton *logoutButton_ = nullptr;

    SecondaryLabel *appName_    = nullptr;
    SecondaryLabel *appVersion_ = nullptr;

    int normalWidth_ = 0;
};

#endif // SIDEMENU_H
