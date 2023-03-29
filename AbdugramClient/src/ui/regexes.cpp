#include "regexes.h"

namespace ui {

namespace regex {
    const QRegularExpression UsernameRegex = QRegularExpression{"^[a-zA-Z0-9]([\\._-](?![\\._-])|[a-zA-Z0-9]){1,18}[a-zA-Z0-9]$"};
    const QRegularExpression PasswordRegex = QRegularExpression{"^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$"};
    const QRegularExpression NameRegex     = QRegularExpression{"^[a-zA-Z](-(?![-])|[a-zA-Z]){0,32}[a-zA-Z]$"};
    const QRegularExpression EmailRegex    = QRegularExpression{"^((([!#$%&'*+\\-/=?^_`{|}~\\w])|([!#$%&'*+\\-/=?^_`{|}~\\w][!#$%&'*+\\-/=?^_`{|}~\\.\\w]{0,}[!#$%&'*+\\-/=?^_`{|}~\\w]))[@]\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*)$"};
    const QRegularExpression PhoneRegex    = QRegularExpression{"\\d{3}[ ]{0,1}\\d{3}[ ]{0,1}\\d{2}[ ]{0,1}\\d{2}"};
} // !regex

} // !ui
