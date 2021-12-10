#include "StringUtilities.h"
#include <cctype>

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#include <DbgHelp.h>
#else
#include <cxxabi.h> // __cxa_demangle()
#endif

#include <iomanip>

    namespace StringUtilities
    {
        std::string GetFilePathExtension(const std::string& FileName)
        {
            auto pos = FileName.find_last_of('.');
            if(pos != std::string::npos)
                return FileName.substr(pos + 1);
            return "";
        }

        std::string RemoveFilePathExtension(const std::string& FileName)
        {
            auto pos = FileName.find_last_of('.');
            if(pos != std::string::npos)
                return FileName.substr(0, pos);
            return FileName;
        }

        std::string GetFileName(const std::string& FilePath)
        {
            auto pos = FilePath.find_last_of('/');
            if(pos != std::string::npos)
                return FilePath.substr(pos + 1);

            pos = FilePath.find_last_of("\\");
            if(pos != std::string::npos)
                return FilePath.substr(pos + 1);

            return FilePath;
        }

        std::string GetFileLocation(const std::string& FilePath)
        {
            auto pos = FilePath.find_last_of('/');
            if(pos != std::string::npos)
                return FilePath.substr(0, pos + 1);

            pos = FilePath.find_last_of("\\");
            if(pos != std::string::npos)
                return FilePath.substr(0, pos + 1);

            return FilePath;
        }
    
        std::string RemoveString(const std::string& string,const std::string& toErase)
        {
            std::string newString = string;
            EraseSubStr(newString, toErase);
            return newString;
        }
    
        std::string RemoveCharacters(const std::string& string,const std::string& toErase)
        {
            std::string newString = string;
            
            for(size_t i = 0; i < toErase.length(); i++)
                EraseSubStr(newString, std::string(1, toErase[i]));
            return newString;
        }

    
       void EraseSubStr(std::string& string, const std::string& toErase)
       {
           // Search for the substring in string
           size_t pos = string.find(toErase);
           if (pos != std::string::npos)
           {
               // If found then erase it from string
               string.erase(pos, toErase.length());
           }
       }

        std::string RemoveName(const std::string& FilePath)
        {
            auto pos = FilePath.find_last_of('/');
            if(pos != std::string::npos)
                return FilePath.substr(0, pos + 1);

            pos = FilePath.find_last_of("\\");
            if(pos != std::string::npos)
                return FilePath.substr(0, pos + 1);

            return FilePath;
        }

        bool IsHiddenFile(const std::string& path)
        {
            if(path != ".." && path != "." && path[0] == '.')
            {
                return true;
            }

            return false;
        }

        std::vector<std::string> SplitString(const std::string& string, const std::string& delimiters)
        {
            size_t start = 0;
            size_t end = string.find_first_of(delimiters);

            std::vector<std::string> result;

            while(end <= std::string::npos)
            {
                std::string token = string.substr(start, end - start);
                if(!token.empty())
                    result.push_back(token);

                if(end == std::string::npos)
                    break;

                start = end + 1;
                end = string.find_first_of(delimiters, start);
            }

            return result;
        }

        std::vector<std::string> SplitString(const std::string& string, const char delimiter)
        {
            return SplitString(string, std::string(1, delimiter));
        }

        std::vector<std::string> Tokenize(const std::string& string)
        {
            return SplitString(string, " \t\n");
        }

        std::vector<std::string> GetLines(const std::string& string)
        {
            return SplitString(string, "\n");
        }

        const char* FindToken(const char* str, const std::string& token)
        {
            const char* t = str;
            while((t = strstr(t, token.c_str())))
            {
                bool left = str == t || isspace(t[-1]);
                bool right = !t[token.size()] || isspace(t[token.size()]);
                if(left && right)
                    return t;

                t += token.size();
            }
            return nullptr;
        }

        const char* FindToken(const std::string& string, const std::string& token)
        {
            return FindToken(string.c_str(), token);
        }

        int32_t FindStringPosition(const std::string& string, const std::string& search, uint32_t offset)
        {
            const char* str = string.c_str() + offset;
            const char* found = strstr(str, search.c_str());
            if(found == nullptr)
                return -1;
            return (int32_t)(found - str) + offset;
        }

        std::string StringRange(const std::string& string, uint32_t start, uint32_t length)
        {
            return string.substr(start, length);
        }

        std::string RemoveStringRange(const std::string& string, uint32_t start, uint32_t length)
        {
            std::string result = string;
            return result.erase(start, length);
        }

        std::string GetBlock(const char* str, const char** outPosition)
        {
            const char* end = strstr(str, "}");
            if(!end)
                return std::string(str);

            if(outPosition)
                *outPosition = end;
            const uint32_t length = static_cast<uint32_t>(end - str + 1);
            return std::string(str, length);
        }

        std::string GetBlock(const std::string& string, uint32_t offset)
        {
            const char* str = string.c_str() + offset;
            return StringUtilities::GetBlock(str);
        }

        std::string GetStatement(const char* str, const char** outPosition)
        {
            const char* end = strstr(str, ";");
            if(!end)
                return std::string(str);

            if(outPosition)
                *outPosition = end;
            const uint32_t length = static_cast<uint32_t>(end - str + 1);
            return std::string(str, length);
        }

        bool StringContains(const std::string& string, const std::string& chars)
        {
            return string.find(chars) != std::string::npos;
        }
    
        bool StringContainsChars(const std::string& string, const std::string& chars)
        {
            for(size_t i = 0; i < chars.length(); i++)
            {
                if(!StringContains(string, std::string(1, chars[i])))
                {
                    return false;
                }
            }
                   
            return true;
        }

        bool StartsWith(const std::string& string, const std::string& start)
        {
            return string.find(start) == 0;
        }

        int32_t NextInt(const std::string& string)
        {
            for(uint32_t i = 0; i < string.size(); i++)
            {
                if(isdigit(string[i]))
                    return atoi(&string[i]);
            }
            return -1;
        }

        bool StringEquals(const std::string& string1, const std::string& string2)
        {
            return strcmp(string1.c_str(), string2.c_str()) == 0;
        }

        std::string StringReplace(std::string str, char ch1, char ch2)
        {
            for(int i = 0; i < str.length(); ++i)
            {
                if(str[i] == ch1)
                    str[i] = ch2;
            }

            return str;
        }

        std::string StringReplace(std::string str, char ch)
        {
            for(int i = 0; i < str.length(); ++i)
            {
                if(str[i] == ch)
                {
                    str = std::string(str).substr(0, i) + std::string(str).substr(i + 1, str.length());
                }
            }

            return str;
        }

        std::string& BackSlashesToSlashes(std::string& string)
        {
            size_t len = string.length();
            for(size_t i = 0; i < len; i++)
            {
                if(string[i] == '\\')
                {
                    string[i] = '/';
                }
            }
            return string;
        }

        std::string& SlashesToBackSlashes(std::string& string)
        {
            size_t len = string.length();
            for(size_t i = 0; i < len; i++)
            {
                if(string[i] == '/')
                {
                    string[i] = '\\';
                }
            }
            return string;
        }

        std::string& RemoveSpaces(std::string& string)
        {
            std::string::iterator endIterator = std::remove(string.begin(), string.end(), ' ');
            string.erase(endIterator, string.end());
            string.erase(std::remove_if(string.begin(),
                             string.end(),
                             [](unsigned char x)
                             {
                                 return std::isspace(x);
                             }),
                string.end());

            return string;
        }

        std::string& RemoveCharacter(std::string& string, const char character)
        {
            std::string::iterator endIterator = std::remove(string.begin(), string.end(), character);
            string.erase(endIterator, string.end());
            string.erase(std::remove_if(string.begin(),
                             string.end(),
                             [](unsigned char x)
                             {
                                 return std::isspace(x);
                             }),
                string.end());

            return string;
        }

        std::string Demangle(const std::string& string)
        {
            if(string.empty())
                return {};

#if defined(LUMOS_PLATFORM_WINDOWS)
            char undecorated_name[1024];
            if(!UnDecorateSymbolName(
                   string.c_str(), undecorated_name, sizeof(undecorated_name),
                   UNDNAME_COMPLETE))
            {
                return string;
            }
            else
            {
                return std::string(undecorated_name);
            }
#else
            char* demangled = nullptr;
            int status = -1;
            demangled = abi::__cxa_demangle(string.c_str(), nullptr, nullptr, &status);
            std::string ret = status == 0 ? std::string(demangled) : string;
            free(demangled);
            return ret;
#endif
        }

        std::string BytesToString(uint64_t bytes)
        {
            static const float gb = 1024 * 1024 * 1024;
            static const float mb = 1024 * 1024;
            static const float kb = 1024;

            std::stringstream result;
            if(bytes > gb)
                result << std::fixed << std::setprecision(2) << (float)bytes / gb << " gb";
            else if(bytes > mb)
                result << std::fixed << std::setprecision(2) << (float)bytes / mb << " mb";
            else if(bytes > kb)
                result << std::fixed << std::setprecision(2) << (float)bytes / kb << " kb";
            else
                result << std::fixed << std::setprecision(2) << (float)bytes << " bytes";

            return result.str();
        }
    
        std::string ReadFileIntoString(const std::string& path)
        {
            std::ifstream input_file(path);
            if (!input_file.is_open()) {
                std::cerr << "Could not open the file - '"
                     << path << "'" << std::endl;
            }
            return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
        }
    }

