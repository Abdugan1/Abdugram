#include "ui/components/colorrepository.h"

namespace colornames {

const QString backgroundColor          = "backgroundColor";
const QString backgroundLighterHelper1 = "backgroundLighterHelper1";
const QString backgroundLighterHelper2 = "backgroundLighterHelper2";
const QString backgroundLighterHelper3 = "backgroundLighterHelper3";
const QString backgroundLighterHelper4 = "backgroundLighterHelper4";
const QString backgroundLighterHelper5 = "backgroundLighterHelper5";
const QString decorationColor          = "decorationColor";
const QString headerColor              = "headerColor";
const QString mainLabelColor           = "mainLabelColor";
const QString secondaryLabelColor      = "secondaryLabelColor";
const QString headerLabelColor         = "headerLabelColor";
const QString helperColor              = "helperColor";
const QString beautyRedColor           = "beautyRedColor";
const QString pinkyRedColor            = "pinkyReadColor";

} // colornames

const QHash<QString, QColor> Colors {
    {colornames::backgroundColor         , QColor{"#181818"}},
    {colornames::backgroundLighterHelper1, QColor{"#1e1e1e"}},
    {colornames::backgroundLighterHelper2, QColor{"#232323"}},
    {colornames::backgroundLighterHelper3, QColor{"#282828"}},
    {colornames::backgroundLighterHelper4, QColor{"#2f2f2f"}},
    {colornames::backgroundLighterHelper5, QColor{"#333333"}},
    {colornames::decorationColor         , QColor{"#A4508B"}},
    {colornames::headerColor             , QColor{"#FFFFFF"}},
    {colornames::mainLabelColor          , QColor{"#FFFFFF"}},
    {colornames::secondaryLabelColor     , QColor{"#828282"}},
    {colornames::headerLabelColor        , QColor{"#FFFFFF"}},
    {colornames::helperColor             , QColor{"#554450"}},
    {colornames::beautyRedColor          , QColor{"#F64650"}},
    {colornames::pinkyRedColor           , QColor{"#ffcfcb"}},
};
