#ifndef STYLE_H
#define STYLE_H

#include <QCommonStyle>
#include <QProxyStyle>

class Style : public QCommonStyle
{
    Q_OBJECT
public:
    explicit Style();

    void drawPrimitive(PrimitiveElement pe,
                       const QStyleOption *opt,
                       QPainter *p,
                       const QWidget *w) const override;

    void drawControl(ControlElement element,
                     const QStyleOption *opt,
                     QPainter *p,
                     const QWidget *w) const override;

    void drawComplexControl(ComplexControl cc,
                            const QStyleOptionComplex *opt,
                            QPainter *p,
                            const QWidget *widget) const override;
};

#endif // STYLE_H
