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

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(fetch_history__invoke)

// These amounts may change at any time, making these particular tests fragile.

// Vector: github.com/spesmilo/sx/blob/master/README.md
#define BX_FETCH_HISTORY_DEMO1_KEY "a0e0be1350a3d3eaa3f381e3aa78f64d16e712c1bfffc7d7ca3b9b5f7409adf8" // 134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz
#define BX_FETCH_HISTORY_DEMO1_INFO \
"transfers\n" \
"{\n" \
"    transfer\n" \
"    {\n" \
"        received\n" \
"        {\n" \
"            hash 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3\n" \
"            height 247683\n" \
"            index 1\n" \
"        }\n" \
"        spent\n" \
"        {\n" \
"            hash b7354b8b9cc9a856aedaa349cffa289ae9917771f4e06b2386636b3c073df1b5\n" \
"            height 247742\n" \
"            index 0\n" \
"        }\n" \
"        value 100000\n" \
"    }\n" \
"}\n"

// Vector: github.com/spesmilo/sx/blob/master/README.md
#define BX_FETCH_HISTORY_DEMO2_KEY "0550bf9055a9a10e453f7ee6cf584ab61307f64a62aa0b3dba11068cf4ac7efe" // 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe
#define BX_FETCH_HISTORY_DEMO2_INFO \
"transfers\n" \
"{\n" \
"    transfer\n" \
"    {\n" \
"        received\n" \
"        {\n" \
"            hash b7354b8b9cc9a856aedaa349cffa289ae9917771f4e06b2386636b3c073df1b5\n" \
"            height 247742\n" \
"            index 0\n" \
"        }\n" \
"        value 90000\n" \
"    }\n" \
"}\n"

#define BX_FETCH_HISTORY_TESTNET_DEMO_KEY "1abf6c34c4370673aee3ce1c1e6c16de549cc6baa065ff3e4b23414b1dc2eca7" // n3GNqMveyvaPvUbH469vDRadqpJMPc84JA
#define BX_FETCH_HISTORY_TESTNET_DEMO_INFO \
"transfers\n" \
"{\n" \
"    transfer\n" \
"    {\n" \
"        received\n" \
"        {\n" \
"            hash 0aadaf5f3a267a409a24c5adfc50ceb7a28943910da02247be7608c5934a3217\n" \
"            height 1225908\n" \
"            index 1\n" \
"        }\n" \
"        value 50000000\n" \
"    }\n" \
"    transfer\n" \
"    {\n" \
"        received\n" \
"        {\n" \
"            hash 6106cf34a6b0fd1d4f81bc7644237adb1f40a7da0cafff7c90212c053e63ee6e\n" \
"            height 1119229\n" \
"            index 1\n" \
"        }\n" \
"        value 881771\n" \
"    }\n" \
"    transfer\n" \
"    {\n" \
"        received\n" \
"        {\n" \
"            hash d9d587c9f77996e5618141a564d46f3bb7c92a7cdd8cbe9142bc43eb18a63887\n" \
"            height 554588\n" \
"            index 0\n" \
"        }\n" \
"        value 13999000\n" \
"    }\n" \
"    transfer\n" \
"    {\n" \
"        received\n" \
"        {\n" \
"            hash 6ec6b313788063402c7404b00433b7a30bb511fb2f73429097e0cbc4dea3be33\n" \
"            height 466228\n" \
"            index 0\n" \
"        }\n" \
"        value 2000000\n" \
"    }\n" \
"    transfer\n" \
"    {\n" \
"        received\n" \
"        {\n" \
"            hash 99845fd840ad2cc4d6f93fafb8b072d188821f55d9298772415175c456f3077d\n" \
"            height 280589\n" \
"            index 0\n" \
"        }\n" \
"        value 50000\n" \
"    }\n" \
"}\n"

BOOST_AUTO_TEST_CASE(fetch_history__invoke__mainnet_sx_demo1_info__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::fetch_history);
    command.set_hash_argument({ BX_FETCH_HISTORY_DEMO1_KEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_HISTORY_DEMO1_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_history__invoke__mainnet_sx_demo2_info__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::fetch_history);
    command.set_format_option({ "info" });
    command.set_hash_argument({ BX_FETCH_HISTORY_DEMO2_KEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_HISTORY_DEMO2_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_history__invoke__testnet_demo_info__okay_output)
{
    BX_DECLARE_CLIENT_TESTNET_COMMAND(bc::explorer::commands::fetch_history);
    command.set_format_option({ "info" });
    command.set_hash_argument({ BX_FETCH_HISTORY_TESTNET_DEMO_KEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_HISTORY_TESTNET_DEMO_INFO);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
