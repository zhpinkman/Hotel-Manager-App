#pragma once

#include "Exception.hpp"

#include <cstdlib>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Request {

  enum class Methods {
    GET,
    POST,
  };

  using ParamsMap = std::unordered_map<std::string, std::string>;
  using UrlType = std::vector<std::string>;

  template <char Delimiter = ' '>
  static std::vector<std::string> splitString(const std::string input) {
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

  Request(const std::string &rawRequest) {
    const auto parsedRequest = splitString(rawRequest);

    if (!parsedRequest.size())
      throw new BadRequestException();

    constexpr std::size_t MethodIndex = 0;

    if (parsedRequest[MethodIndex] == "GET")
      method = Methods::GET;
    else if (parsedRequest[MethodIndex] == "POST")
      method = Methods::POST;
    else
      throw new BadRequestException();

    std::size_t i = MethodIndex + 1;
    for (; parsedRequest[i] != "?"; ++i)
      url.push_back(parsedRequest[i]);

    ++i;
    while (i < parsedRequest.size())
    {
      params.emplace(parsedRequest[i], parsedRequest[i + 1]);
      i += 2;
    }
  }

  Methods getMethod() const { return method; }

  const UrlType &getRequestUrl() const { return url; }

  UrlType &getRequestUrl() { return url; }

  const ParamsMap &getRequestParams() const { return params; }

  ParamsMap &getRequestParams() { return params; }
};