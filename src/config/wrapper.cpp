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
#include <bitcoin/explorer/config/wrapper.hpp>

#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace bc::system;
using namespace bc::system::config;
using namespace po;

wrapper::wrapper()
  : value_()
{
}

wrapper::wrapper(const std::string& wrapped)
{
    std::stringstream(wrapped) >> *this;
}

wrapper::wrapper(const data_chunk& wrapped)
  : wrapper(encode_base16(wrapped))
{
}

wrapper::wrapper(const wallet::wrapped_data& wrapped)
  : value_(wrapped)
{
}

wrapper::wrapper(const wallet::payment_address& address)
  : wrapper(encode_base16(address.to_payment()))
{
}

wrapper::wrapper(uint8_t version, const data_chunk& payload)
  : wrapper(wallet::wrapped_data{ version, payload, 0 })
{
}

wrapper::wrapper(const wrapper& other)
  : value_(other.value_)
{
}

const data_chunk wrapper::to_data() const
{
    return wrap(value_);
}

wrapper::operator const wallet::wrapped_data&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, wrapper& argument)
{
    std::string hexcode;
    input >> hexcode;

    // The checksum is validated here.
    if (!unwrap(argument.value_, base16(hexcode)))
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const wrapper& argument)
{
    // The checksum is calculated here (value_ checksum is ignored).
    const auto bytes = wrap(argument.value_);
    output << base16(bytes);
    return output;
}

} // namespace explorer
} // namespace config
} // namespace libbitcoin
