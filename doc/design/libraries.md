# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libbitpulsed_cli*         | RPC client functionality used by *bitpulsed-cli* executable |
| *libbitpulsed_common*      | Home for common functionality shared by different executables and libraries. Similar to *libbitpulsed_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libbitpulsed_consensus*   | Stable, backwards-compatible consensus functionality used by *libbitpulsed_node* and *libbitpulsed_wallet* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitpulsedconsensus*    | Shared library build of static *libbitpulsed_consensus* library |
| *libbitpulsed_kernel*      | Consensus engine and support library used for validation by *libbitpulsed_node* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitpulsedqt*           | GUI functionality used by *bitpulsed-qt* and *bitpulsed-gui* executables |
| *libbitpulsed_ipc*         | IPC functionality used by *bitpulsed-node*, *bitpulsed-wallet*, *bitpulsed-gui* executables to communicate when [`--enable-multiprocess`](multiprocess.md) is used. |
| *libbitpulsed_node*        | P2P and RPC server functionality used by *bitpulsed* and *bitpulsed-qt* executables. |
| *libbitpulsed_util*        | Home for common functionality shared by different executables and libraries. Similar to *libbitpulsed_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libbitpulsed_wallet*      | Wallet functionality used by *bitpulsed* and *bitpulsed-wallet* executables. |
| *libbitpulsed_wallet_tool* | Lower-level wallet functionality used by *bitpulsed-wallet* executable. |
| *libbitpulsed_zmq*         | [ZeroMQ](../zmq.md) functionality used by *bitpulsed* and *bitpulsed-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. Exceptions are *libbitpulsed_consensus* and *libbitpulsed_kernel* which have external interfaces documented at [../shared-libraries.md](../shared-libraries.md).

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`libbitpulsed_*_SOURCES`](../../src/Makefile.am) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libbitpulsed_node* code lives in `src/node/` in the `node::` namespace
  - *libbitpulsed_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libbitpulsed_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libbitpulsed_util* code lives in `src/util/` in the `util::` namespace
  - *libbitpulsed_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

bitpulsed-cli[bitpulsed-cli]-->libbitpulsed_cli;

bitpulsed[bitpulsed]-->libbitpulsed_node;
bitpulsed[bitpulsed]-->libbitpulsed_wallet;

bitpulsed-qt[bitpulsed-qt]-->libbitpulsed_node;
bitpulsed-qt[bitpulsed-qt]-->libbitpulsedqt;
bitpulsed-qt[bitpulsed-qt]-->libbitpulsed_wallet;

bitpulsed-wallet[bitpulsed-wallet]-->libbitpulsed_wallet;
bitpulsed-wallet[bitpulsed-wallet]-->libbitpulsed_wallet_tool;

libbitpulsed_cli-->libbitpulsed_util;
libbitpulsed_cli-->libbitpulsed_common;

libbitpulsed_common-->libbitpulsed_consensus;
libbitpulsed_common-->libbitpulsed_util;

libbitpulsed_kernel-->libbitpulsed_consensus;
libbitpulsed_kernel-->libbitpulsed_util;

libbitpulsed_node-->libbitpulsed_consensus;
libbitpulsed_node-->libbitpulsed_kernel;
libbitpulsed_node-->libbitpulsed_common;
libbitpulsed_node-->libbitpulsed_util;

libbitpulsedqt-->libbitpulsed_common;
libbitpulsedqt-->libbitpulsed_util;

libbitpulsed_wallet-->libbitpulsed_common;
libbitpulsed_wallet-->libbitpulsed_util;

libbitpulsed_wallet_tool-->libbitpulsed_wallet;
libbitpulsed_wallet_tool-->libbitpulsed_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class bitpulsed-qt,bitpulsed,bitpulsed-cli,bitpulsed-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Consensus* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libbitpulsed_wallet* and *libbitpulsed_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libbitpulsed_consensus* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libbitpulsed_util* should also be a standalone dependency that any library can depend on, and it should not depend on other internal libraries.

- *libbitpulsed_common* should serve a similar function as *libbitpulsed_util* and be a place for miscellaneous code used by various daemon, GUI, and CLI applications and libraries to live. It should not depend on anything other than *libbitpulsed_util* and *libbitpulsed_consensus*. The boundary between _util_ and _common_ is a little fuzzy but historically _util_ has been used for more generic, lower-level things like parsing hex, and _common_ has been used for bitpulsed-specific, higher-level things like parsing base58. The difference between util and common is mostly important because *libbitpulsed_kernel* is not supposed to depend on *libbitpulsed_common*, only *libbitpulsed_util*. In general, if it is ever unclear whether it is better to add code to *util* or *common*, it is probably better to add it to *common* unless it is very generically useful or useful particularly to include in the kernel.


- *libbitpulsed_kernel* should only depend on *libbitpulsed_util* and *libbitpulsed_consensus*.

- The only thing that should depend on *libbitpulsed_kernel* internally should be *libbitpulsed_node*. GUI and wallet libraries *libbitpulsedqt* and *libbitpulsed_wallet* in particular should not depend on *libbitpulsed_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libbitpulsed_consensus*, *libbitpulsed_common*, and *libbitpulsed_util*, instead of *libbitpulsed_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libbitpulsedqt*, *libbitpulsed_node*, *libbitpulsed_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](`../../src/interfaces/`) abstract interfaces.

## Work in progress

- Validation code is moving from *libbitpulsed_node* to *libbitpulsed_kernel* as part of [The libbitpulsedkernel Project #24303](https://github.com/bitcoin/bitcoin/issues/24303)
- Source code organization is discussed in general in [Library source code organization #15732](https://github.com/bitcoin/bitcoin/issues/15732)
