//
// OSSE CONFIG
//
#ifndef OSSE_CONFIG
#define OSSE_CONFIG

#include <map>
#include <regex>
#include <string>



// OSSE CONFIG MACROS
#ifndef CONFIG_REGEX
#define CONFIG_REGEX R"(^\s*([A-Za-z_][A-Za-z0-9_-]*)\s*:\s*(.+)$)"
#endif // CONFIG_REGEX



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
            static Config load(std::string &path);



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
