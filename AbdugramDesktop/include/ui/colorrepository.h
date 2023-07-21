#ifndef COLORREPOSITORY_H
#define COLORREPOSITORY_H

#include <QHash>
#include <QColor>

namespace colornames {
extern const QString backgroundColor         ;
extern const QString backgroundLighterHelper1;
extern const QString backgroundLighterHelper2;
extern const QString backgroundLighterHelper3;
extern const QString backgroundLighterHelper4;
extern const QString backgroundLighterHelper5;
extern const QString decorationColor         ;
extern const QString headerColor             ;
extern const QString mainLabelColor          ;
extern const QString secondaryLabelColor     ;
extern const QString headerLabelColor        ;
extern const QString helperColor             ;
} // colornames

extern const QHash<QString, QColor> Colors;

#endif // COLORREPOSITORY_H
