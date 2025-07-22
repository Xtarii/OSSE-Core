//
// OSSE CONFIG
//
#ifndef OSSE_CONFIG
#define OSSE_CONFIG

#include "Defaults.h"
#include <map>
#include <regex>
#include <string>
#include <vector>



// OSSE CONFIG MACROS
#ifndef CONFIG_REGEX
#define CONFIG_REGEX R"(^\s*([A-Za-z_][A-Za-z0-9_-]*)\s*:\s*(.+)$)"
#endif // CONFIG_REGEX



/**
 * Configuration List
 *
 * A list of config options stored as
 * an array instead of a map.
 */
typedef std::vector<std::string> CONFIG_LIST;



namespace OSSE {
    /**
     * OpenSource Search Engine Configuration
     *
     * An instance with configuration settings
     * for the OSSE functions and components.
     */
    struct Config {
        private:
            /**
             * Configuration settings map
             */
            std::map<std::string, std::string> settings;



        public:
            /**
             * Loads configuration file
             *
             * Loads a `.osse` file, example `default.osse`
             * containing settings for `OSSE` functions and components.
             *
             * @param path File path
             * @return Configuration object
             */
            static Config load(std::string path);

            /**
             * Loads configuration list
             *
             * Loads a ```.list``` file, example ```tags.list```
             * containing an array of configuration options.
             *
             * @param path File path
             * @return Configuration list object
             */
            static CONFIG_LIST loadConfigList(std::string path);

            /**
             * Gets configuration settings value
             *
             * @param config Configuration
             * @param settings Settings Object
             * @return Settings value
             */
            static std::string getValue(Config* config, const OSSE_CONFIG_TYPE &settings);

            /**
             * Gets configuration regex object
             *
             * @param config Configuration
             * @param settings Settings Object
             * @param flag Regex flag
             * @return Regex
             */
            static std::regex getRegex(
                Config* config,
                const OSSE_CONFIG_TYPE &settings,
                std::regex_constants::syntax_option_type flag = std::regex::icase
            );



            /**
             * Gets config settings value
             *
             * @param setting Settings name
             * @return Settings value
             */
            std::string operator[](std::string setting);
            /**
             * Gets config settings value
             *
             * @param setting Settings name
             * @return Settings value
             */
            std::string operator[](const char* setting);



            /**
             * Gets setting as regex rule
             *
             * @param setting Setting name
             * @param flag Regex flag
             * @return Regex rule
             */
            std::regex getRegexSettings(
                std::string setting,
                std::regex_constants::syntax_option_type flag
            );

            /**
             * Gets setting as regex rule
             *
             * @param setting Setting name
             * @return Regex rule
             */
            std::regex getRegexSettings(std::string setting);
    };
}

#endif // OSSE_CONFIG
