#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QFrame>

class QLabel;

class SideMenuButton;
class MainLabel;
class SecondaryLabel;

class SideMenu : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset NOTIFY offsetChanged)
public:
    explicit SideMenu(QWidget *parent);

    bool eventFilter(QObject *watched, QEvent *event) override;

    int offset() const;
    void setOffset(int newOffset);

signals:
    void aboutToShow();
    void aboutToClose();

    void offsetChanged();

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void startShowAnimation();
    void closeAnimation();

    void onSyncFinished();

private:
    void setupUi();

private:
    QWidget *background_ = nullptr;

    QLabel    *avatar_   = nullptr;
    MainLabel *username_ = nullptr;

    SideMenuButton *logoutButton_ = nullptr;

    SecondaryLabel *appName_    = nullptr;
    SecondaryLabel *appVersion_ = nullptr;

    int menuWidth_ = 0;
    int offset_ = 0;
};

#endif // SIDEMENU_H
