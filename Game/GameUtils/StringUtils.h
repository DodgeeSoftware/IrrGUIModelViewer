#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <algorithm>
#include <cstring>
#include <sstream>
#include <vector>
#include <cstdlib>

namespace Utils
{
    // ****************
    // * UTF8 Strings *
    // ****************

    //! Split strings according to a delimiter
    inline std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
    {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }
    //! Split strings according to a delimiter
    inline std::vector<std::string> split(const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }
    // Convert data types into c++ style strings
    //! Convert a long to a c++ style string
    inline std::string toString(long value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert an unsigned int to a c++ style string
    inline std::string toString(unsigned int value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert an int to a c++ style string
    inline std::string toString(int value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert a float to a c++ style string
    inline std::string toString(float value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert a double to a c++ style string
    inline std::string toString(double value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert a c++ style string to uppercase
    inline std::string toUpper(std::string text)
    {
        std::string uppercase(text);
        for (std::string::iterator p = uppercase.begin(); p != uppercase.end(); p++)
            *p = std::toupper(*p);
        return uppercase;
    }
    //! Convert a c++ style string to lowercase
    inline std::string toLower(std::string text)
    {
        std::string lowercase(text);
        for (std::string::iterator p = lowercase.begin(); p != lowercase.end(); p++)
            *p = std::tolower(*p);
        return lowercase;
    }
    //! Convert cstyle text to a long
    inline long toLong(const char* text)
    {
        return atol(text);
    }
    //! Convert cstyle text to a int
    inline int toInt(const char* text)
    {
        return atoi(text);
    }
    //! Convert cstyle text to a float
    inline float toFloat(const char* text)
    {
        return atof(text);
    }
    //! Convert cstyle text to a bool
    inline bool toBool(const char* text)
    {
        std::string lowercase(text);
        for (std::string::iterator p = lowercase.begin(); p != lowercase.end(); p++)
            *p = std::tolower(*p);
        if (lowercase == "true")
            return true;
        else
            return false;
    }

    // ************************
    // * WIDESTRING FUNCTIONS *
    // ************************

    //! Split wide strings according to a delimiter
    inline std::vector<std::wstring> &splitWideString(const std::wstring &s, wchar_t delim, std::vector<std::wstring> &elems)
    {
        // TODO: implement me
        std::vector<std::wstring> wideString;
        return wideString;
    }
    //! Split wide strings according to a delimiter
    inline std::vector<std::wstring> splitWideString(const std::wstring &s, wchar_t delim)
    {
        std::vector<std::wstring> wideString;
        return wideString;
    }
    //! Convert a double to a WideString
    inline std::wstring toWideString(double value)
    {
        std::wstringstream wideStringStream;
        wideStringStream << value;
        return wideStringStream.str().c_str();
    }
    //! Convert a float to a WideString
    inline std::wstring toWideString(float value)
    {
        std::wstringstream wideStringStream;
        wideStringStream << value;
        return wideStringStream.str().c_str();
    }
    //! Convert a long to a WideString
    inline std::wstring toWideString(long value)
    {
        std::wstringstream wideStringStream;
        wideStringStream << value;
        return wideStringStream.str().c_str();
    }
    //! Convert an int to a WideString
    inline std::wstring toWideString(int value)
    {
        std::wstringstream wideStringStream;
        wideStringStream << value;
        return wideStringStream.str().c_str();
    }
    //! Convert an Unsigned Int to a WideString
    inline std::wstring toWideString(unsigned int value)
    {
        std::wstringstream wideStringStream;
        wideStringStream << value;
        return wideStringStream.str().c_str();
    }
    //! Convert an Unsigned Char to a WideString
    inline std::wstring toWideString(unsigned char value)
    {
        std::wstringstream wideStringStream;
        wideStringStream << value;
        return wideStringStream.str().c_str();
    }
    //! Convert a Bool to a WideString
    inline std::wstring toWideString(bool value)
    {
        std::wstringstream wideStringStream;
        wideStringStream << (value == true) ? "TRUE" : "FALSE";
        return wideStringStream.str().c_str();
    }
    //! Convert a c style string to a widestring
    inline std::wstring toWideString(char* text)
    {
        // TODO: implement me
        return std::wstring();
        //return std::wstring(text.begin(), text.end());
    }
    //! Convert a c++ style string to a widestring
    inline std::wstring toWideString(std::string text)
    {
        return std::wstring(text.begin(), text.end());
    }
    //! Convert a c++ style string to uppercase
    inline std::wstring toUpper(std::wstring text)
    {
//        std::string uppercase(text);
//        for (std::string::iterator p = uppercase.begin(); p != uppercase.end(); p++)
//            *p = std::toupper(*p);
//        return uppercase;
        // TODO: Implement me
        return std::wstring();
    }
    //! Convert a c++ style string to lowercase
    inline std::wstring toLower(std::wstring text)
    {
//        std::string lowercase(text);
//        for (std::string::iterator p = lowercase.begin(); p != lowercase.end(); p++)
//            *p = std::tolower(*p);
//        return lowercase;
        // TODO: Implement me
        return std::wstring();
    }
    //! Convert cstyle text to a long
    inline long toLong(wchar_t* text)
    {
        //return atol(text);
        // TODO: implement me
        return 0;
    }
    //! Convert cstyle text to a int
    inline int toInt(wchar_t* text)
    {
        //return atoi(text);
        // TODO: implement me
        return 0;
    }
    //! Convert cstyle text to a float
    inline float toFloat(wchar_t* text)
    {
        //return atof(text);
        // TODO: implement me
        return 0;
    }
    //! Convert cstyle text to a bool
    inline bool toBool(wchar_t* text)
    {
//        std::string lowercase(text);
//        for (std::string::iterator p = lowercase.begin(); p != lowercase.end(); p++)
//            *p = std::tolower(*p);
//        if (lowercase == "true")
//            return true;
//        else
//            return false;
        // TODO: implement me
        return false;
    }
}

#endif // STRINGUTILS_H
