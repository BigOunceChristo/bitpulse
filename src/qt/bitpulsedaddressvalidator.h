// Copyright (c) 2011-2020 The bitcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitpulse_QT_bitpulseADDRESSVALIDATOR_H
#define bitpulse_QT_bitpulseADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class bitpulseAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit bitpulseAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** bitpulse address widget validator, checks for a valid bitpulse address.
 */
class bitpulseAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit bitpulseAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // bitpulse_QT_bitpulseADDRESSVALIDATOR_H
