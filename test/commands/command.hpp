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
#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <locale>
#include <string>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <bitcoin/explorer.hpp>

#define BX_USING_NAMESPACES()
using namespace bc; \
using namespace bc::client; \
using namespace bc::explorer; \
using namespace bc::explorer::commands; \
using namespace bc::explorer::config;
using namespace bc::system;

// Libbitcoin error messsages (see error.cpp).
#define BX_ERROR_MESSAGE(ec) \
    code(error::ec).message()

// Genesis block hash, transaction, address.
#define BX_FIRST_ADDRESS \
"1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa"
#define BX_FIRST_KEY \
"6191c3b590bfcfa0475e877c302da1e323497acf3b42c08d8fa28e364edf018b"
#define BX_GENESIS_BLOCK_HASH \
"000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"
#define BX_SATOSHIS_WORDS_TX_HASH \
"4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"
#define BX_SATOSHIS_WORDS_TX_BASE16 \
"01000000010000000000000000000000000000000000000000000000000000000000000000ffffffff4d04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73ffffffff0100f2052a01000000434104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac00000000"

#define BX_FIRST_TESTNET_ADDRESS \
"n3GNqMveyvaPvUbH469vDRadqpJMPc84JA"
#define BX_FIRST_TESTNET_KEY \
"1abf6c34c4370673aee3ce1c1e6c16de549cc6baa065ff3e4b23414b1dc2eca7"

// FIXME: v4 server(s) are required for network testing.
// Default network parameters, uses libbitcoin community node.
#define BX_MAINNET_HOST "mainnet.libbitcoin.net"
#define BX_MAINNET_PORT 8333
#define BX_TESTNET_HOST "testnet2.libbitcoin.net"
#define BX_TESTNET_PORT 28333
#define BX_NETWORK_RETRY 0
#define BX_NETWORK_TIMEOUT 5
#define BX_NETWORK_HANDSHAKE 15

// Libbitcoin Server (mainnet), uses libbitcoin community server.
#define BX_MAINNET_QUERY "tcp://mainnet.libbitcoin.net:9091"
#define BX_MAINNET_HEARTBEAT "tcp://mainnet.libbitcoin.net:9092"
#define BX_MAINNET_BLOCK "tcp://mainnet.libbitcoin.net:9093"
#define BX_MAINNET_TRANSACTION "tcp://mainnet.libbitcoin.net:9094"

// Libbitcoin Server (testnet), uses libbitcoin community server.
#define BX_TESTNET_QUERY "tcp://testnet2.libbitcoin.net:29091"
#define BX_TESTNET_HEARTBEAT "tcp://testnet2.libbitcoin.net:29092"
#define BX_TESTNET_BLOCK "tcp://testnet2.libbitcoin.net:29093"
#define BX_TESTNET_TRANSACTION "tcp://testnet2.libbitcoin.net:29094"

#define BX_DECLARE_COMMAND(extension) \
    std::stringstream output, error; \
    extension command

#define BX_DECLARE_PEER_COMMAND(extension) \
    BX_DECLARE_COMMAND(extension); \
    command.set_network_debug_file_setting({ "debug.log" }); \
    command.set_network_error_file_setting({ "error.log" }); \
    command.set_network_hosts_file_setting({ "hosts.cache" }); \
    command.set_network_connect_retries_setting(BX_NETWORK_RETRY); \
    command.set_network_connect_timeout_seconds_setting(BX_NETWORK_TIMEOUT); \
    command.set_network_channel_handshake_seconds_setting(BX_NETWORK_HANDSHAKE);

#define BX_DECLARE_CLIENT_COMMAND(extension) \
    BX_DECLARE_COMMAND(extension); \
    command.set_server_url_setting({ BX_MAINNET_QUERY }); \
    command.set_server_block_url_setting({ BX_MAINNET_BLOCK }); \
    command.set_server_transaction_url_setting({ BX_MAINNET_TRANSACTION }); \
    command.set_server_connect_retries_setting(BX_NETWORK_RETRY); \
    command.set_server_connect_timeout_seconds_setting(BX_NETWORK_TIMEOUT)

#define BX_DECLARE_CLIENT_TESTNET_COMMAND(extension) \
    BX_DECLARE_COMMAND(extension); \
    command.set_server_url_setting({ BX_TESTNET_QUERY }); \
    command.set_server_block_url_setting({ BX_TESTNET_BLOCK }); \
    command.set_server_transaction_url_setting({ BX_TESTNET_TRANSACTION }); \
    command.set_server_connect_retries_setting(BX_NETWORK_RETRY); \
    command.set_server_connect_timeout_seconds_setting(BX_NETWORK_TIMEOUT)

// serializer results
#define BX_SERIALIZE_COPY_ROUND_TRIP(serializer, value) \
    serializer original; \
    stringstream output, input(value); \
    input >> original; \
    serializer copy(original); \
    output << copy; \
    BOOST_REQUIRE_EQUAL(output.str(), value)

// console results
#define BX_REQUIRE_OKAY(value) \
    BOOST_REQUIRE_EQUAL(value, console_result::okay)
#define BX_REQUIRE_FAILURE(value) \
    BOOST_REQUIRE_EQUAL(value, console_result::failure)
#define BX_REQUIRE_INVALID(value) \
    BOOST_REQUIRE_EQUAL(value, console_result::invalid)

// stream results
#define BX_REQUIRE_ERROR(value) \
    BOOST_REQUIRE_EQUAL(error.str(), value); \
    BOOST_REQUIRE_EQUAL(output.str(), "")
#define BX_REQUIRE_OUTPUT(value) \
    BOOST_REQUIRE_EQUAL(output.str(), value); \
    BOOST_REQUIRE_EQUAL(error.str(), "")

// exceptions
#define BX_REQUIRE_THROW_INVALID_OPTION_VALUE(expression) \
    BOOST_REQUIRE_THROW(expression, po::invalid_option_value)

#endif
