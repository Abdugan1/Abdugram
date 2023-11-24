#ifndef ROUNDWIDGET_H
#define ROUNDWIDGET_H

#include <QWidget>

class RoundWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoundWidget(QWidget *parent = nullptr);

    float opacity() const;
    void setOpacity(float newOpacity);
    int cornerRadius() const;
    void setCornerRadius(int newCornerRadius);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

signals:
    void opacityChanged();
    void cornerRadiusChanged();
    void backgroundColorChanged();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    float opacity_ = 1.0f;
    int   cornerRadius_ = 0;
    QColor backgroundColor_ = Qt::white;
    Q_PROPERTY(float opacity READ opacity WRITE setOpacity NOTIFY opacityChanged FINAL)
    Q_PROPERTY(int cornerRadius READ cornerRadius WRITE setCornerRadius NOTIFY cornerRadiusChanged FINAL)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged FINAL)
};

#endif // ROUNDWIDGET_H
