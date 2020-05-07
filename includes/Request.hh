#pragma once

#include "Exception.hh"

#include <cstdlib>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

template <typename InvalidFormatExceptionType,
          typename InvalidParamAccessExceptionType>
struct Request
{
  enum class Methods
  {
    GET,
    POST,
    DELETE,
  };

  using ParamsMap = std::unordered_map<std::string, std::string>;
  using UrlType = std::vector<std::string>;

  template <char Delimiter = ' '>
  static std::vector<std::string> splitString(const std::string input)
  {
    std::vector<std::string> parsedRequest;
    std::stringstream ss(input);
    std::string str;
    while (getline(ss, str, Delimiter))
      parsedRequest.push_back(str);

    return parsedRequest;
  }

private:
  Methods method;
  UrlType url;
  ParamsMap params;

public:
  Request() = delete;

  Request(const std::string &rawRequest)
  {
    const auto parsedRequest = splitString(rawRequest);

    if (!parsedRequest.size())
      throw new BadRequestException();

    constexpr std::size_t MethodIndex = 0;

    if (parsedRequest[MethodIndex] == "GET")
      method = Methods::GET;
    else if (parsedRequest[MethodIndex] == "POST")
      method = Methods::POST;
    else if (parsedRequest[MethodIndex] == "DELETE")
      method = Methods::DELETE;
    else
      throw new BadRequestException();

    std::size_t i = MethodIndex + 1;
    for (; i < parsedRequest.size() && parsedRequest[i] != "?"; ++i)
      url.push_back(parsedRequest[i]);

    ++i;
    while (i < parsedRequest.size())
    {
      if ((i + 1) >= parsedRequest.size())
        throw new BadRequestException();

      params.emplace(parsedRequest[i], parsedRequest[i + 1]);
      i += 2;
    }
  }

  Methods getMethod() const { return method; }

  const UrlType &getRequestUrl() const { return url; }

  UrlType &getRequestUrl() { return url; }

  const ParamsMap &getRequestParams() const { return params; }

  ParamsMap &getRequestParams() { return params; }

  const std::string &getParam(const std::string &paramKey) const
  {
    if (params.find(paramKey) == params.end())
      throw new InvalidFormatExceptionType();

    return params.at(paramKey);
  }
};