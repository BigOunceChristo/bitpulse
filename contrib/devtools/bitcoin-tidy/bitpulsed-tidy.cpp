// Copyright (c) 2023 Bitcoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "logprintf.h"

#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

class bitpulsedModule final : public clang::tidy::ClangTidyModule
{
public:
    void addCheckFactories(clang::tidy::ClangTidyCheckFactories& CheckFactories) override
    {
        CheckFactories.registerCheck<bitpulsed::LogPrintfCheck>("bitpulsed-unterminated-logprintf");
    }
};

static clang::tidy::ClangTidyModuleRegistry::Add<bitpulsedModule>
    X("bitpulsed-module", "Adds bitpulsed checks.");

volatile int bitpulsedModuleAnchorSource = 0;
