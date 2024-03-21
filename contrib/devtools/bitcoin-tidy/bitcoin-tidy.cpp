// Copyright (c) 2023 Bitpulse Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "logprintf.h"

#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

class BitpulseModule final : public clang::tidy::ClangTidyModule
{
public:
    void addCheckFactories(clang::tidy::ClangTidyCheckFactories& CheckFactories) override
    {
        CheckFactories.registerCheck<bitpulse::LogPrintfCheck>("bitpulse-unterminated-logprintf");
    }
};

static clang::tidy::ClangTidyModuleRegistry::Add<BitpulseModule>
    X("bitpulse-module", "Adds bitpulse checks.");

volatile int BitpulseModuleAnchorSource = 0;
