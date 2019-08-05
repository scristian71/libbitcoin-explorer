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
#include <bitcoin/explorer/commands/ec-multiply-secrets.hpp>

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/config/ec_private.hpp>


namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

console_result ec_multiply_secrets::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& secrets = get_secrets_argument();

    ec_secret product(null_hash);
    for (auto const& secret: secrets)
    {
        // Initialize product on first pass.
        if (product == null_hash)
        {
            product = secret;
            continue;
        }

        // Elliptic curve function (INTEGER * INTEGER) % curve-order.
        if (!system::ec_multiply(product, secret))
        {
            error << BX_EC_MULITPLY_SECRETS_OUT_OF_RANGE << std::endl;
            return console_result::failure;
        }
    }

    // We don't use bc::ec_private serialization (WIF) here.
    output << config::ec_private(product) << std::endl;
    return console_result::okay;
}


} //namespace commands
} //namespace explorer
} //namespace libbitcoin
