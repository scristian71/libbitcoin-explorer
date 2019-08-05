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
#include <bitcoin/explorer/config/hashtype.hpp>

#include <exception>
#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace bc::system;
using namespace po;

// DRY
static auto hashtype_all = "all";
static auto hashtype_none = "none";
static auto hashtype_single = "single";

hashtype::hashtype()
  : hashtype(machine::sighash_algorithm::all)
{
}

hashtype::hashtype(const std::string& token)
{
    std::stringstream(token) >> *this;
}

hashtype::hashtype(const machine::sighash_algorithm& value)
  : value_(value)
{
}

hashtype::hashtype(const hashtype& other)
  : value_(other.value_)
{
}

hashtype::operator machine::sighash_algorithm() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, hashtype& argument)
{
    std::string text;
    input >> text;

    if (text == hashtype_all)
        argument.value_ = machine::sighash_algorithm::all;
    else if (text == hashtype_none)
        argument.value_ = machine::sighash_algorithm::none;
    else if (text == hashtype_single)
        argument.value_ = machine::sighash_algorithm::single;
    else
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(text));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const hashtype& argument)
{
    std::string value;

    switch (argument.value_)
    {
        case machine::sighash_algorithm::all:
            value = hashtype_all;
            break;
        case machine::sighash_algorithm::none:
            value = hashtype_none;
            break;
        case machine::sighash_algorithm::single:
            value = hashtype_single;
            break;
        default:
            BITCOIN_ASSERT_MSG(false, "Unexpected signature hash type value.");
    }

    return output;
}

} // namespace explorer
} // namespace config
} // namespace libbitcoin
