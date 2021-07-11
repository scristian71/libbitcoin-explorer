.template 0
###############################################################################
# Copyright (c) 2011-2019 libbitcoin developers (see COPYING).
#
# GSL generate libbitcoin-explorer source files.
# This file contains no localizable resources.
#
# This is a code generator built using the iMatix GSL code generation
# language. See https://github.com/imatix/gsl for details.
###############################################################################
.endtemplate
.template 1
.echo "Generating include/bitcoin/explorer/command.hpp..."
.output "../include/bitcoin/explorer/command.hpp"
.copyleft()
#ifndef BX_COMMAND_HPP
#define BX_COMMAND_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
.primitives()
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {

#define BX_PROGRAM_NAME "bx"
#define BX_HELP_VARIABLE "help"
#define BX_CONFIG_VARIABLE "config"
BC_DECLARE_CONFIG_DEFAULT_PATH("libbitcoin" / BX_PROGRAM_NAME ".cfg")

/**
 * Base class for definition of each Bitcoin Explorer command.
 */
class BCX_API command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "not-implemented";
    }

    /**
     * Destructor.
     */
    virtual ~command()
    {
    }

    /**
     * The symbolic (not localizable) command name, lower case.
     * @return  Example: "fetch-transaction"
     */
    virtual const char* name()
    {
        return symbol();
    }

    /**
     * The localizable command category name, upper case.
     * @return  Example: "ONLINE"
     */
    virtual const char* category()
    {
        return "not-implemented";
    }

    /**
     * The localizable command description.
     * @return  Example: "Get transactions by hash."
     */
    virtual const char* description()
    {
        return "not-implemented";
    }

    /**
     * Declare whether the command has been obsoleted.
     * @return  True if the command is obsolete
     */
    virtual bool obsolete()
    {
        return false;
    }

    /**
     * Determines if STDIN is required to be raw.
     * @return  True if the type of the STDIN argument is primitive::raw.
     */
    virtual bool requires_raw_input()
    {
        return false;
    }

    /**
     * Determines if STDOUT is required to be raw.
     * @return  True if the type of the STDOUT argument is primitive::raw.
     */
    virtual bool requires_raw_output()
    {
        return false;
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual system::console_result invoke(std::ostream& output,
        std::ostream& error)
    {
        return system::console_result::failure;
    }

    /**
     * Load command argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
    {
        return argument_metadata_;
    }

    /**
     * Load environment variable definitions.
     * @param[out] definitions  The defined program argument definitions.
     */
    virtual void load_environment(system::options_metadata& definitions)
    {
        using namespace po;
        definitions.add_options()
        (
            /* This composes with the command line options. */
            BX_CONFIG_VARIABLE,
            value<boost::filesystem::path>()
                ->composing()->default_value(config_default_path()),
            "$(config_description)"
        );
    }

    /**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input      The input stream for loading the parameters.
     * @param[in]  variables  The loaded variables.
     */
    BCX_API virtual void load_fallbacks(std::istream& input,
        po::variables_map& variables)
    {
    }

    /**
     * Load command option definitions.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded option definitions.
     */
    virtual system::options_metadata& load_options()
    {
        return option_metadata_;
    }

    /**
     * Load configuration setting definitions.
     * @param[out] definitions  The defined program argument definitions.
     */
    virtual void load_settings(system::options_metadata& definitions)
    {
        using namespace po;
        definitions.add_options()
.for configuration
.   is_last_configuration = last()
.   for setting where !(configuration.section = "general" & setting.name = "network")
.       is_last_setting = is_last_configuration & last()
.       identifiers = section + "." + name
.       variable = "setting_.$(section:lower,c).$(name:lower,c)"
.       expression = value_semantic(!true(), !true(), type,\
            is_xml_true(required), is_xml_true(multiple), variable, default)
        (
            "$(identifiers)",
            $(expression),
            "$(description)"
        )$(is_last_setting ?? ";")
.   endfor
.endfor
    }

    /**
     * Load streamed value as parameter fallback.
     * @param[in]  input      The input stream for loading the parameter.
     * @param[in]  variables  The loaded variables.
     */
    virtual void load_stream(std::istream& input, po::variables_map& variables)
    {
    }

    /**
     * Set variable defaults from configuration variable values.
     * @param[in]  variables  The loaded variables.
     */
    virtual void set_defaults_from_config(po::variables_map& variables)
    {
    }

    /**
     * Write the help for this command to the specified stream.
     * @param[out] output  The output stream.
     */
    virtual void write_help(std::ostream& output)
    {
        const auto& options = get_option_metadata();
        const auto& arguments = get_argument_metadata();
        system::config::printer help(options, arguments, BX_PROGRAM_NAME,
            description(), name());
        help.initialize();
        help.commandline(output);
    }

    /* Properties */

    /**
     * Get command line argument metadata.
     */
    virtual system::arguments_metadata& get_argument_metadata()
    {
        return argument_metadata_;
    }

    /**
     * Get command line option metadata.
     */
    virtual system::options_metadata& get_option_metadata()
    {
        return option_metadata_;
    }

.for configuration
.   for setting
.       is_vector = is_xml_true(multiple)
.       setting_type = normalize_type(!true(), !true(), type)
.       vectored_type = vectored_type(setting_type, is_vector)
.       pluralized_name = pluralize(name, is_vector)
.       pluralized_setting = pluralize("setting", is_vector)
    /**
     * Get the value of the $(section:c).$(name) $(pluralized_setting).
     */
    virtual $(vectored_type) get_$(section:c)_$(pluralized_name:c)_setting() const
    {
        return setting_.$(section:c).$(pluralized_name:c);
    }

    /**
     * Set the value of the $(section:c).$(name) $(pluralized_setting).
     */
    virtual void set_$(section:c)_$(pluralized_name:c)_setting($(vectored_type) value)
    {
        setting_.$(section:c).$(pluralized_name:c) = value;
    }

.   endfor
.endfor
protected:

    /**
     * This base class is abstract but not pure virtual, so prevent direct
     * construction here.
     */
    command()
    {
    }

private:

    /**
     * Command line argument metadata.
     */
    system::arguments_metadata argument_metadata_;

    /**
     * Command line option metadata.
     */
    system::options_metadata option_metadata_;

    /**
     * Environment variable bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct environment
    {
        environment()
        {
        }

.# There is no reason to expose the config path, as the config has been read.
.#      boost::filesystem::path config;
    } environment_;

    /**
     * Configuration setting file bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct setting
    {
.for configuration
        struct $(section:c)
        {
            $(section:c)()
.   for setting
.       is_vector = is_xml_true(multiple)
.       pluralized_name = pluralize(name, is_vector)
              $(if_else(first(), ":", " ")) $(pluralized_name:c)()$(!last() ?? ",")
.   endfor
            {
            }

.   for setting
.       is_vector = is_xml_true(multiple)
.       setting_type = normalize_type(!true(), !true(), type)
.       vectored_type = vectored_type(setting_type, is_vector)
.       pluralized_name = pluralize(name, is_vector)
            $(vectored_type) $(pluralized_name:c);
.   endfor
        } $(section:c);

.endfor
        setting()
.for configuration
          $(if_else(first(), ":", " ")) $(section:c)()$(!last() ?? ",")
.endfor
        {
        }
    } setting_;
};

} // namespace explorer
} // namespace libbitcoin

#endif
.endtemplate
