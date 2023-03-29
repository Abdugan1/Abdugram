#ifndef REGEXES_H
#define REGEXES_H

#include <QRegularExpression>

namespace ui {

namespace regex {
    extern const QRegularExpression UsernameRegex;
    extern const QRegularExpression PasswordRegex;
    extern const QRegularExpression NameRegex;
    extern const QRegularExpression EmailRegex;
    extern const QRegularExpression PhoneRegex;
} // !regex

} // !ui

#endif // REGEXES_H
