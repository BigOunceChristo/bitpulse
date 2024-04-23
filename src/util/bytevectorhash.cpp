// Copyright (c) 2018-2022 The bitpulsed Core Developers
// This project is derived from the Bitcoin Core Project, originally licensed under the MIT license.
// See the accompanying file COPYING or http://www.opensource.org/licenses/mit-license.php for details.


#include <crypto/siphash.h>
#include <random.h>
#include <util/bytevectorhash.h>

#include <vector>

ByteVectorHash::ByteVectorHash() :
    m_k0(GetRand<uint64_t>()),
    m_k1(GetRand<uint64_t>())
{
}

size_t ByteVectorHash::operator()(const std::vector<unsigned char>& input) const
{
    return CSipHasher(m_k0, m_k1).Write(input).Finalize();
}
