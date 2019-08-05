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
#include <bitcoin/explorer/config/language.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace bc::system;
using namespace po;

// DRY
static auto language_en = "en";
static auto language_es = "es";
static auto language_fr = "fr";
static auto language_it = "it";
static auto language_ja = "ja";
static auto language_ko = "ko";
static auto language_zh_Hans = "zh_Hans";
static auto language_zh_Hant = "zh_Hant";
static auto language_any = "any";

language::language()
  : value_(wallet::language::all)
{
}

language::language(const std::string& token)
{
    std::stringstream(token) >> *this;
}

language::language(wallet::dictionary_list& languages)
  : value_(languages)
{
}

language::language(const language& other)
  : value_(other.value_)
{
}

language::operator const wallet::dictionary_list() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, language& argument)
{
    std::string text;
    input >> text;

    argument.value_.clear();

    if (text == language_any)
        argument.value_.assign(wallet::language::all.begin(),
            wallet::language::all.end());
    else if(text == language_en)
        argument.value_.push_back(&wallet::language::en);
    else if (text == language_es)
        argument.value_.push_back(&wallet::language::es);
    else if (text == language_fr)
        argument.value_.push_back(&wallet::language::fr);
    else if (text == language_it)
        argument.value_.push_back(&wallet::language::it);
    else if (text == language_ja)
        argument.value_.push_back(&wallet::language::ja);
    else if (text == language_ko)
        argument.value_.push_back(&wallet::language::ko);
    else if (text == language_zh_Hans)
        argument.value_.push_back(&wallet::language::zh_Hans);
    else if (text == language_zh_Hant)
        argument.value_.push_back(&wallet::language::zh_Hant);
    else
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(text));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const language& argument)
{
    std::string text;

    if (argument.value_.size() > 1)
        text = language_any;
    else if(argument.value_.front() == &wallet::language::en)
        text = language_en;
    else if (argument.value_.front() == &wallet::language::es)
        text = language_es;
    else if (argument.value_.front() == &wallet::language::fr)
        text = language_fr;
    else if (argument.value_.front() == &wallet::language::it)
        text = language_it;
    else if (argument.value_.front() == &wallet::language::ja)
        text = language_ja;
    else if (argument.value_.front() == &wallet::language::ko)
        text = language_ko;
    else if (argument.value_.front() == &wallet::language::zh_Hans)
        text = language_zh_Hans;
    else if (argument.value_.front() == &wallet::language::zh_Hant)
        text = language_zh_Hant;
    else
    {
        BITCOIN_ASSERT_MSG(false, "Unexpected encoding value.");
    }

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
