#ifndef UTILS_YAML_READ_DATA_
#define UTILS_YAML_READ_DATA_

#include <string>

#include "gambit/Core/yaml_parser.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"

#include "yaml-cpp/yaml.h"

namespace Gambit
{
  namespace Data
  {
    /**
     * @brief Read data from a yaml file
     *
     * @param runOptions Options object possibly containing directory and
     * file name of a yaml
     * @param key Key of relevant data entry in yaml
     *
     * @returns Data entry read from yaml
     */
    template<typename T>
    T read_yaml(safe_ptr<Options> runOptions, std::string key,
                std::string default_dir, std::string default_file)
    {
      const auto data_dir = runOptions->getValueOrDef<std::string>(default_dir, "data_dir");
      const auto data_file = runOptions->getValueOrDef<std::string>(default_file, "data_file");
      const auto data_yaml = data_dir + "/" + data_file;
      IniParser::IniFile parser;

      try
      {
        parser.readFile(data_yaml);
        return parser.getValue<T>(key);
      }
      catch (const std::exception &e)
      {
        std::ostringstream os;
        os << "error: " << e.what()
           << "\n when reading" << key
           << " from " << data_yaml;
        utils_error().raise(LOCAL_INFO, os.str());
      }
      catch ( ... )
      {
        std::ostringstream os;
        os << "error w/o rtti when reading" << key
           << " from " << data_yaml;
        utils_error().raise(LOCAL_INFO, os.str());
      }

      throw std::runtime_error("unreachable code in " + LOCAL_INFO);
    }
  }  // end namespace Data
}  // end namespace Gambit

#endif  // UTILS_YAML_READ_DATA_
