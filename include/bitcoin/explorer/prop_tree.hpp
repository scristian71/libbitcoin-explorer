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
#ifndef BX_PROPERTY_TREE_HPP
#define BX_PROPERTY_TREE_HPP

#include <map>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

class base2;
class header;
class input;
class output;
class transaction;

/**
 * A tuple to represent settings and serialized values.
 */
typedef std::map<std::string, std::string> settings_list;

/**
 * Create a property tree array of property tree elements.
 * The child elements of Value contain no arrays.
 * @param      <Values>  The array element type.
 * @param[in]  name      The name of the list elements.
 * @param[in]  values    The enumerable with elements of type Values.
 * @param[in]  json      Use json array formating.
 * @returns              A new property tree containing the list.
 */
template <typename Values>
pt::ptree prop_tree_list(const std::string& name, const Values& values,
    bool json);

/**
 * Create a property tree array of property tree elements.
 * The child elements of Value contain arrays.
 * @param      <Values>  The array element type.
 * @param[in]  name      The name of the list elements.
 * @param[in]  values    The enumerable with elements of type Values.
 * @param[in]  json      Use json array formating.
 * @returns              A new property tree containing the list.
 */
template <typename Values>
pt::ptree prop_tree_list_of_lists(const std::string& name,
    const Values& values, bool json);

/**
 * Create a property tree array of value elements.
 * @param      <Values>  The array element type.
 * @param[in]  name      The name of the list elements.
 * @param[in]  values    The enumerable with elements of type Values.
 * @param[in]  json      Use json array formating.
 * @returns              A new property tree containing the list.
 */
template <typename Values>
pt::ptree prop_value_list(const std::string& name, const Values& values,
    bool json);

/**
 * Generate a property list for a block header.
 * @param[in]  header  The header.
 * @return             A property list.
 */
BCX_API pt::ptree prop_list(const header& header);

/**
 * Generate a property tree for a block header.
 * @param[in]  header  The header.
 * @return             A property tree.
 */
BCX_API pt::ptree prop_tree(const header& header);

/**
 * Generate a property tree for a set of headers.
 * @param[in]  headers  The set of headers.
 * @return              A property tree.
 */
BCX_API pt::ptree prop_tree(const std::vector<header>& headers);

/**
* Generate a property list for a history row.
* @param[in]  row  The history row.
* @return          A property list.
*/
BCX_API pt::ptree prop_list(const client::history& row);

/**
 * Generate a property tree for a history row.
 * @param[in]  row  The history row.
 * @return          A property tree.
 */
BCX_API pt::ptree prop_tree(const client::history& row);

/**
 * Generate a property tree for a set of history rows.
 *
 * @param[in]  rows  The set of history rows.
 * @param[in]  json  Use json array formatting.
 * @return           A property tree.
 */
BCX_API pt::ptree prop_tree(const client::history::list& rows, bool json);

/**
 * Generate a property list from balance rows for an address.
 * This doesn't require array formatting because it summarizes the rows.
 * @param[in]  rows             The set of balance rows.
 * @param[in]  balance_address  The script hash for the balance rows.
 * @return                      A property list.
 */
BCX_API pt::ptree prop_list(const client::history::list& rows,
    const system::hash_digest& script_hash);

/**
 * Generate a property tree from balance rows for an address.
 * This doesn't require array formatting because it summarizes the rows.
 * @param[in]  rows             The set of balance rows.
 * @param[in]  balance_address  The script hash for the balance rows.
 * @return                      A property tree.
 */
BCX_API pt::ptree prop_tree(const client::history::list& rows,
    const system::hash_digest& script_hash);

/**
 * Generate a property list from balance rows for an address.
 * This doesn't require array formatting because it summarizes the rows.
 * @param[in]  rows             The set of balance rows.
 * @param[in]  balance_address  The payment address for the balance rows.
 * @return                      A property list.
 */
BCX_API pt::ptree prop_list(const client::history::list& rows,
    const system::wallet::payment_address& balance_address);

/**
 * Generate a property tree from balance rows for an address.
 * This doesn't require array formatting because it summarizes the rows.
 * @param[in]  rows             The set of balance rows.
 * @param[in]  balance_address  The payment address for the balance rows.
 * @return                      A property tree.
 */
BCX_API pt::ptree prop_tree(const client::history::list& rows,
    const system::wallet::payment_address& balance_address);

/**
 * Generate a property list for a transaction input.
 * @param[in]  tx_input  The input.
 * @return               A property list.
 */
BCX_API pt::ptree prop_list(const tx_input_type& tx_input);

/**
 * Generate a property tree for a transaction input.
 * @param[in]  tx_input  The input.
 * @return               A property tree.
 */
BCX_API pt::ptree prop_tree(const tx_input_type& tx_input);

/**
 * Generate a property tree for a set of transaction inputs.
 * @param[in]  tx_inputs  The set of transaction inputs.
 * @param[in]  json       Use json array formatting.
 * @return                A property tree.
 */
BCX_API pt::ptree prop_tree(const tx_input_type::list& tx_inputs, bool json);

/**
 * Generate a property list for an input.
 * @param[in]  input  The input.
 * @return            A property list.
 */
BCX_API pt::ptree prop_list(const explorer::config::input& input);

/**
 * Generate a property tree for an input.
 * @param[in]  input  The input.
 * @return            A property tree.
 */
BCX_API pt::ptree prop_tree(const explorer::config::input& input);

/**
 * Generate a property tree for a set of inputs.
 * @param[in]  inputs  The set of inputs.
 * @param[in]  json    Use json array formatting.
 * @return             A property tree.
 */
BCX_API pt::ptree prop_tree(
    const std::vector<explorer::config::input>& inputs, bool json);

/**
 * Generate a property list for a transaction output.
 * @param[in]  tx_output  The transaction output.
 * @return                A property list.
 */
BCX_API pt::ptree prop_list(const tx_output_type& tx_output);

/**
 * Generate a property tree for a transaction output.
 * @param[in]  tx_output  The transaction output.
 * @return                A property tree.
 */
BCX_API pt::ptree prop_tree(const tx_output_type& tx_output);

/**
 * Generate a property tree for a set of transaction outputs.
 * @param[in]  tx_outputs  The set of transaction outputs.
 * @param[in]  json        Use json array formatting.
 * @return                 A property tree.
 */
BCX_API pt::ptree prop_tree(const tx_output_type::list& tx_outputs,
    bool json);

/**
 * Generate a property list for a point value.
 * @param[in]  point  The point value.
 * @return            A property list.
 */
BCX_API pt::ptree prop_list(const system::chain::point_value& point);

/**
 * Generate a property tree for points value.
 * @param[in]  info  The points value.
 * @param[in]  json  Use json array formatting.
 * @return           A property tree.
 */
BCX_API pt::ptree prop_tree(const system::chain::points_value& values,
    bool json);

/**
 * Generate a property list for a transaction.
 * @param[in]  transaction  The transaction.
 * @param[in]  json         Use json array formatting.
 * @return                  A property list.
 */
BCX_API pt::ptree prop_list(const transaction& transaction, bool json);

/**
 * Generate a property tree for a transaction.
 * @param[in]  transaction  The transaction.
 * @param[in]  json         Use json array formatting.
 * @return                  A property tree.
 */
BCX_API pt::ptree prop_tree(const transaction& transaction, bool json);

/**
 * Generate a property tree for a set of transactions.
 * @param[in]  transactions  The set of transactions.
 * @param[in]  json          Use json array formatting.
 * @return                   A property tree.
 */
BCX_API pt::ptree prop_tree(const std::vector<transaction>& transactions,
    bool json);

/**
 * Create a property tree for the settings command.
 * @param[in]  settings   The list of settings.
 * @returns               A new property tree containing the settings.
 */
BCX_API pt::ptree prop_tree(const settings_list& settings);

} // namespace config
} // namespace explorer
} // namespace libbitcoin

#include <bitcoin/explorer/impl/prop_tree.ipp>

#endif
