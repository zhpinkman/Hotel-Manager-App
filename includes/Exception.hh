#pragma once

#include <exception>
#include <string>

#define NOT_FOUND "Not Found"
#define BAD_REQUEST "Bad Request"
#define PERMISSION_DENIED "Permission Denied"

class Exception : public std::exception
{
public:
  Exception(const std::string _msg) : msg(_msg) {}
  virtual ~Exception() throw() {}

  virtual const char *what() const throw() { return msg.c_str(); }

private:
  std::string msg;
};

class NotFoundException : public Exception
{
public:
  NotFoundException() : Exception(NOT_FOUND) {}
};

class BadRequestException : public Exception
{
public:
  BadRequestException() : Exception(BAD_REQUEST) {}
};

class PermissionDeniedException : public Exception
{
public:
  PermissionDeniedException() : Exception(PERMISSION_DENIED) {}
};
