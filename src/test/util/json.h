// Copyright (c) 2023 The bitcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitpulsed_TEST_UTIL_JSON_H
#define bitpulsed_TEST_UTIL_JSON_H

#include <string>

#include <univalue.h>

UniValue read_json(const std::string& jsondata);

#endif // bitpulsed_TEST_UTIL_JSON_H
