# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libbitpulse_cli*         | RPC client functionality used by *bitpulse-cli* executable |
| *libbitpulse_common*      | Home for common functionality shared by different executables and libraries. Similar to *libbitpulse_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libbitpulse_consensus*   | Stable, backwards-compatible consensus functionality used by *libbitpulse_node* and *libbitpulse_wallet* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitpulseconsensus*    | Shared library build of static *libbitpulse_consensus* library |
| *libbitpulse_kernel*      | Consensus engine and support library used for validation by *libbitpulse_node* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitpulseqt*           | GUI functionality used by *bitpulse-qt* and *bitpulse-gui* executables |
| *libbitpulse_ipc*         | IPC functionality used by *bitpulse-node*, *bitpulse-wallet*, *bitpulse-gui* executables to communicate when [`--enable-multiprocess`](multiprocess.md) is used. |
| *libbitpulse_node*        | P2P and RPC server functionality used by *bitpulsed* and *bitpulse-qt* executables. |
| *libbitpulse_util*        | Home for common functionality shared by different executables and libraries. Similar to *libbitpulse_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libbitpulse_wallet*      | Wallet functionality used by *bitpulsed* and *bitpulse-wallet* executables. |
| *libbitpulse_wallet_tool* | Lower-level wallet functionality used by *bitpulse-wallet* executable. |
| *libbitpulse_zmq*         | [ZeroMQ](../zmq.md) functionality used by *bitpulsed* and *bitpulse-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. Exceptions are *libbitpulse_consensus* and *libbitpulse_kernel* which have external interfaces documented at [../shared-libraries.md](../shared-libraries.md).

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`libbitpulse_*_SOURCES`](../../src/Makefile.am) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libbitpulse_node* code lives in `src/node/` in the `node::` namespace
  - *libbitpulse_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libbitpulse_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libbitpulse_util* code lives in `src/util/` in the `util::` namespace
  - *libbitpulse_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

bitpulse-cli[bitpulse-cli]-->libbitpulse_cli;

bitpulsed[bitpulsed]-->libbitpulse_node;
bitpulsed[bitpulsed]-->libbitpulse_wallet;

bitpulse-qt[bitpulse-qt]-->libbitpulse_node;
bitpulse-qt[bitpulse-qt]-->libbitpulseqt;
bitpulse-qt[bitpulse-qt]-->libbitpulse_wallet;

bitpulse-wallet[bitpulse-wallet]-->libbitpulse_wallet;
bitpulse-wallet[bitpulse-wallet]-->libbitpulse_wallet_tool;

libbitpulse_cli-->libbitpulse_util;
libbitpulse_cli-->libbitpulse_common;

libbitpulse_common-->libbitpulse_consensus;
libbitpulse_common-->libbitpulse_util;

libbitpulse_kernel-->libbitpulse_consensus;
libbitpulse_kernel-->libbitpulse_util;

libbitpulse_node-->libbitpulse_consensus;
libbitpulse_node-->libbitpulse_kernel;
libbitpulse_node-->libbitpulse_common;
libbitpulse_node-->libbitpulse_util;

libbitpulseqt-->libbitpulse_common;
libbitpulseqt-->libbitpulse_util;

libbitpulse_wallet-->libbitpulse_common;
libbitpulse_wallet-->libbitpulse_util;

libbitpulse_wallet_tool-->libbitpulse_wallet;
libbitpulse_wallet_tool-->libbitpulse_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class bitpulse-qt,bitpulsed,bitpulse-cli,bitpulse-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Consensus* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libbitpulse_wallet* and *libbitpulse_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libbitpulse_consensus* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libbitpulse_util* should also be a standalone dependency that any library can depend on, and it should not depend on other internal libraries.

- *libbitpulse_common* should serve a similar function as *libbitpulse_util* and be a place for miscellaneous code used by various daemon, GUI, and CLI applications and libraries to live. It should not depend on anything other than *libbitpulse_util* and *libbitpulse_consensus*. The boundary between _util_ and _common_ is a little fuzzy but historically _util_ has been used for more generic, lower-level things like parsing hex, and _common_ has been used for bitpulse-specific, higher-level things like parsing base58. The difference between util and common is mostly important because *libbitpulse_kernel* is not supposed to depend on *libbitpulse_common*, only *libbitpulse_util*. In general, if it is ever unclear whether it is better to add code to *util* or *common*, it is probably better to add it to *common* unless it is very generically useful or useful particularly to include in the kernel.


- *libbitpulse_kernel* should only depend on *libbitpulse_util* and *libbitpulse_consensus*.

- The only thing that should depend on *libbitpulse_kernel* internally should be *libbitpulse_node*. GUI and wallet libraries *libbitpulseqt* and *libbitpulse_wallet* in particular should not depend on *libbitpulse_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libbitpulse_consensus*, *libbitpulse_common*, and *libbitpulse_util*, instead of *libbitpulse_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libbitpulseqt*, *libbitpulse_node*, *libbitpulse_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](`../../src/interfaces/`) abstract interfaces.

## Work in progress

- Validation code is moving from *libbitpulse_node* to *libbitpulse_kernel* as part of [The libbitpulsekernel Project #24303](https://github.com/bitcoin/bitcoin/issues/24303)
- Source code organization is discussed in general in [Library source code organization #15732](https://github.com/bitcoin/bitcoin/issues/15732)
