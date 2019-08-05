/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/commands/stealth-shared.hpp>

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>


// This is nearly the same as ec-multiply + sha256.
// Pass either (ephem_secret, scan_pubkey) or (scan_secret, ephem_pubkey).
namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result stealth_shared::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& secret = get_secret_argument();
    const auto& pubkey = get_pubkey_argument();

    ec_compressed product(pubkey);
    if (!system::ec_multiply(product, secret))
    {
        error << BX_STEALTH_SHARED_OUT_OF_RANGE << std::endl;
        return console_result::failure;
    }

    const auto hash = sha256_hash(product);

    output << config::ec_private(hash) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
