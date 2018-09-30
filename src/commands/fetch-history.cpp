/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/commands/fetch-history.hpp>

#include <iostream>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::chain;
using namespace bc::client;
using namespace bc::explorer::config;

// When you restore your wallet, you should use fetch_history().
// But for updating the wallet, use the [new] scan() method-
// which is faster because you avoid pulling the entire history.
// We can eventually increase privacy and performance (fewer calls to scan())
// by 'mining' addresses with the same prefix, allowing us to fetch the
// prefix group. Obelisk will eventually support privacy enhanced history for
// address scan by prefix.
console_result fetch_history::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto& address = get_payment_address_argument();
    const auto connection = get_connection(*this);

    obelisk_client client(connection.retries);
    if (!client.connect(connection))
    {
        display_connection_failure(error, connection.server);
        return console_result::failure;
    }

    callback_state state(error, output, encoding);

    // This enables json-style array formatting.
    const auto json = encoding == encoding_engine::json;

    auto on_done = [&state, &address, json](const code& ec,
        const history::list& rows)
    {
        if (!state.succeeded(ec))
            return;

        state.output(prop_tree(rows, json));
    };

    // This does not include unconfirmed transactions.
    client.blockchain_fetch_history4(on_done, address.hash());
    client.wait();

    return state.get_result();
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
