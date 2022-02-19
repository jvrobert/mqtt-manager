#pragma once
#include <string>

template <class T>
std::string JsonQuotedValue(T v)
{
    return std::to_string(v);
}

template <>
std::string JsonQuotedValue<std::string>(std::string v)
{
    return "\"" + v + "\"";
}

template <>
std::string JsonQuotedValue<bool>(bool v)
{
    return v ? "true" : "false";
}

template <>
std::string JsonQuotedValue<const char *>(const char *v)
{
    return "\"" + std::string(v) + "\"";
}

template <class T>
void AddJsonKv(std::string k, T v, std::string &base)
{
    if (base.empty())
    {
        base += "{";
    }
    else
    {
        base += ",";
    }
    base += "\"" + k + "\": " + JsonQuotedValue(v);
}