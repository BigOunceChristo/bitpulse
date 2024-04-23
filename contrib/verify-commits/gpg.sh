#!/bin/sh
# Copyright (c) 2014-2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C
INPUT=$(cat /dev/stdin)
if [ "$bitpulsed_VERIFY_COMMITS_ALLOW_SHA1" = 1 ]; then
    printf '%s\n' "$INPUT" | gpg --trust-model always "$@" 2>/dev/null
    exit $?
else
	# Note how we've disabled SHA1 with the --weak-digest option, disabling
	# signatures - including selfsigs - that use SHA1. While you might think that
	# collision attacks shouldn't be an issue as they'd be an attack on yourself,
	# in fact because what's being signed is a commit object that's
	# semi-deterministically generated by untrusted input (the pull-req) in theory
	# an attacker could construct a pull-req that results in a commit object that
	# they've created a collision for. Not the most likely attack, but preventing
	# it is pretty easy so we do so as a "belt-and-suspenders" measure.
	for LINE in $(gpg --version); do
		case "$LINE" in
			"gpg (GnuPG) 1.4.1"*|"gpg (GnuPG) 2.0."*)
				echo "Please upgrade to at least gpg 2.1.10 to check for weak signatures" > /dev/stderr
                                printf '%s\n' "$INPUT" | gpg --trust-model always "$@" 2>/dev/null
                                exit $?
				;;
			# We assume if you're running 2.1+, you're probably running 2.1.10+
			# gpg will fail otherwise
			# We assume if you're running 1.X, it is either 1.4.1X or 1.4.20+
			# gpg will fail otherwise
		esac
	done
        printf '%s\n' "$INPUT" | gpg --trust-model always --weak-digest sha1 "$@" 2>/dev/null
        exit $?
fi
