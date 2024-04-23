// Copyright (c) 2018-2022 The bitpulse Core Developers
// This project is derived from the Bitcoin Core Project, originally licensed under the MIT license.
// See the accompanying file COPYING or http://www.opensource.org/licenses/mit-license.php for details.


#ifndef bitpulse_QT_TEST_UTIL_H
#define bitpulse_QT_TEST_UTIL_H

#include <chrono>

#include <qglobal.h>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

/**
 * Press "Ok" button in message box dialog.
 *
 * @param text - Optionally store dialog text.
 * @param msec - Number of milliseconds to pause before triggering the callback.
 */
void ConfirmMessage(QString* text, std::chrono::milliseconds msec);

#endif // bitpulse_QT_TEST_UTIL_H
