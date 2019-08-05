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
#include <bitcoin/explorer/commands/input-validate.hpp>

#include <iostream>
#include <bitcoin/system.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

console_result message_validate::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& address = get_payment_address_argument();
    const auto& sign = get_signature_argument();
    const auto& message = get_message_argument();

    if (!verify_message(message, address, sign))
    {
        // We do not return a failure here, as this is a validity test.
        output << BX_MESSAGE_VALIDATE_INDEX_INVALID_SIGNATURE << std::endl;
        return console_result::invalid;
    }

    output << BX_MESSAGE_VALIDATE_INDEX_VALID_SIGNATURE << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
