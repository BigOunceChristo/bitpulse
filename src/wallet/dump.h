// Copyright (c) 2020-2021 The bitcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitpulsed_WALLET_DUMP_H
#define bitpulsed_WALLET_DUMP_H

#include <util/fs.h>

#include <string>
#include <vector>

struct bilingual_str;
class ArgsManager;

namespace wallet {
class WalletDatabase;

bool DumpWallet(const ArgsManager& args, WalletDatabase& db, bilingual_str& error);
bool CreateFromDump(const ArgsManager& args, const std::string& name, const fs::path& wallet_path, bilingual_str& error, std::vector<bilingual_str>& warnings);
} // namespace wallet

#endif // bitpulsed_WALLET_DUMP_H
