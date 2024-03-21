// Copyright (c) 2020-2022 The Bitpulse Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitpulse_TEST_UTIL_INDEX_H
#define bitpulse_TEST_UTIL_INDEX_H

class BaseIndex;
namespace util {
class SignalInterrupt;
} // namespace util

/** Block until the index is synced to the current chain */
void IndexWaitSynced(const BaseIndex& index, const util::SignalInterrupt& interrupt);

#endif // bitpulse_TEST_UTIL_INDEX_H
