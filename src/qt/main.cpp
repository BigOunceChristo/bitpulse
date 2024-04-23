// Copyright (c) 2018-2022 The bitpulse Core Developers
// This project is derived from the Bitcoin Core Project, originally licensed under the MIT license.
// See the accompanying file COPYING or http://www.opensource.org/licenses/mit-license.php for details.


#include <qt/bitpulse.h>

#include <common/url.h>
#include <compat/compat.h>
#include <util/translation.h>

#include <QApplication>
#include <QCoreApplication>
#include <QString>

#include <functional>
#include <string>

/** Translate string to current locale using Qt. */
extern const std::function<std::string(const char*)> G_TRANSLATION_FUN = [](const char* psz) {
    return QCoreApplication::translate("bitpulse-core", psz).toStdString();
};
UrlDecodeFn* const URL_DECODE = urlDecode;

const std::function<std::string()> G_TEST_GET_FULL_NAME{};

MAIN_FUNCTION
{
    QApplication app(argc, argv);

    // Apply global stylesheet
    QString styleSheet = "QPushButton { background-color: blue; color: white; }";
    app.setStyleSheet(styleSheet);

    return GuiMain(argc, argv);
}
