// Copyright (c) 2021 The Bitpulse Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitpulse_IPC_CAPNP_PROTOCOL_H
#define bitpulse_IPC_CAPNP_PROTOCOL_H

#include <memory>

namespace ipc {
class Protocol;
namespace capnp {
std::unique_ptr<Protocol> MakeCapnpProtocol();
} // namespace capnp
} // namespace ipc

#endif // bitpulse_IPC_CAPNP_PROTOCOL_H
