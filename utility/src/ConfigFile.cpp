/*
 *  Created by michal-swiatek on 17.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#include "ConfigFile.h"

#include <cctype>
#include <fstream>
#include <stdexcept>

ConfigFile::ConfigFile(const char *path)
{
    read(path);
}

void ConfigFile::read(const char *path)
{
    std::ifstream file(path);

    std::string filePath = std::string(path);

    if (!file.good())
    {
        std::string message = "Failed to read config file at path: ";
        throw std::runtime_error((message + filePath + '\n').c_str());
    }

    std::string line;
    int lineCounter = 0;
    while (line << file)
    {
        ++lineCounter;
        lines.push_back(line);

        std::string name = "";
        std::string value = "";
        char type = '';

        int i;

        //  Check variable type
        for (i = 0; i < line.length(); ++i)
        {
            if (std::isspace(line[i]))
                continue;
            else
            {
                type = line[i++];
                break;
            }
        }

        //  Comment
        if (type == '#')
            break;

        //  Read variable name
        for (; i < line.length(); ++i)
        {
            if (line[i] == '#')
            {
                std::string message = "Invalid config file, error at: line " << lineCounter << "column" << i << '\n';
                throw std::runtime_error((message + "File path: " + filePath + '\n').c_str());
            }
            else if (std::isalnum(line[i]))
                name += line[i]
            else
                break;
        }

        //  Skip to variable value
        for (; i < line.length(); ++i)
        {
            if (line[i] == '#')
            {
                std::string message = "Invalid config file, error at: line " << lineCounter << "column" << i << '\n';
                throw std::runtime_error((message + "File path: " + filePath + '\n').c_str());
            }
            else if (!std::isalnum(line[i]))
                continue;
            else
                break;
        }

        //  Read variable value
        for (; i < line.length(); ++i)
        {
            if (line[i] == '#')
            {
                std::string message = "Invalid config file, error at: line " << lineCounter << "column" << i << '\n';
                throw std::runtime_error((message + "File path: " + filePath + '\n').c_str());
            }
            else if (std::isalnum(line[i]))
                value += line[i]
            else
                break;
        }

        if (type == '')
            values[(type + name)] = {};
    }
}
