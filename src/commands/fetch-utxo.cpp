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

#include <bitcoin/explorer/commands/fetch-utxo.hpp>

#include <iostream>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/callback_state.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/config/algorithm.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::client;
using namespace bc::explorer::config;
using namespace bc::system;
using namespace bc::system::chain;

console_result fetch_utxo::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& encoding = get_format_option();
    const auto algorithm = get_algorithm_option();
    const auto satoshi = get_satoshi_argument();
    const hash_digest& key = get_hash_argument();
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

    auto on_done = [&state, json](const code& ec, const points_value& unspent)
    {
        if (!state.succeeded(ec))
            return;

        state.output(property_tree(unspent, json));
    };

    client.blockchain_fetch_unspent_outputs(on_done, key, satoshi, algorithm);
    client.wait();

    return state.get_result();
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
