// Copyright (c) 2023 The bitcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitpulsed_UTIL_BATCHPRIORITY_H
#define bitpulsed_UTIL_BATCHPRIORITY_H

/**
 * On platforms that support it, tell the kernel the calling thread is
 * CPU-intensive and non-interactive. See SCHED_BATCH in sched(7) for details.
 *
 */
void ScheduleBatchPriority();

#endif // bitpulsed_UTIL_BATCHPRIORITY_H
