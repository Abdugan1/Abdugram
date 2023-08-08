#include "ui/styles/style.h"

#include "ui/components/colorrepository.h"

#include <QPainter>
#include <QStyleOption>
#include <QDebug>

Style::Style()
    : QCommonStyle{}
{
}

void Style::drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    qDebug() << "primitive:" << pe;
    QCommonStyle::drawPrimitive(pe, opt, p, w);
}


void Style::drawControl(ControlElement element,
                        const QStyleOption *opt,
                        QPainter *p,
                        const QWidget *w) const
{
    qDebug() << element;
    switch (element) {
    case CE_ScrollBarSubLine:

        break;
    case CE_ScrollBarSubPage:
        break;

    case CE_ScrollBarAddPage:
        break;
    case CE_ScrollBarSlider:

        break;
    default:
        break;
    }
    QCommonStyle::drawControl(element, opt, p, w);
}

void Style::drawComplexControl(ComplexControl cc,
                               const QStyleOptionComplex *opt,
                               QPainter *p,
                               const QWidget *w) const
{
    qDebug() << "cc:" << cc;
    QCommonStyle::drawComplexControl(cc, opt, p, w);
}
