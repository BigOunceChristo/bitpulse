// Copyright (c) 2011-2020 The Bitpulse Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitpulse_QT_bitpulseADDRESSVALIDATOR_H
#define bitpulse_QT_bitpulseADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class BitpulseAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BitpulseAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Bitpulse address widget validator, checks for a valid bitpulse address.
 */
class BitpulseAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BitpulseAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // bitpulse_QT_bitpulseADDRESSVALIDATOR_H
