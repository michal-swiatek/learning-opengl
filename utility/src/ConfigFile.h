/*
 *  Created by michal-swiatek on 17.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <any>
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

class ConfigFile
{
public:
    ConfigFile(const char* path);

    void read(const char* path);    //  Reads all the lines and loads the values
    void load(const char* path);    //  Loads only values
    void save(const char* path, bool replace);  //  Replaces values if lines vector is not empty

    template <typename T>
    const std::optional<T>& getValue(const std::string& name)
    {
        const auto& value = values[name];

        if (value)
            return std::any_cast<T>(*value);
        else
            return {};
    }

    template <typename T>
    void addValue(const std::string& name, const T& value)
    {
        values[name] = value;
    }

private:
    std::unordered_map<std::string, std::optional<std::any> > values;
    std::vector<std::string> lines;
};

#endif //CONFIGFILE_H
