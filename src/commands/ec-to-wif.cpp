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
#include <bitcoin/explorer/commands/ec-to-wif.hpp>

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

console_result ec_to_wif::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& secret = get_ec_private_key_argument();
    const auto& uncompressed = get_uncompressed_option();
    const auto& wif_version = get_version_option();

    // Payment address version is unused in this scenario.
    const uint8_t payment_version = 0;

    // ec_private requires a composite version.
    const auto version = ec_private::to_version(payment_version, wif_version);

    output << ec_private(secret, version, !uncompressed) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
