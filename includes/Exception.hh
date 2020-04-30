#pragma once

#include <exception>
#include <string>

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
  NotFoundException() : Exception("Not Found") {}
};

class BadRequestException : public Exception
{
public:
  BadRequestException() : Exception("Bad Request") {}
};

class PermissionDeniedException : public Exception
{
public:
  PermissionDeniedException() : Exception("Permission Denied") {}
};

class NotEnoughRoomException : public Exception
{
public:
  NotEnoughRoomException() : Exception("Not Enough Room") {}
};

class NotEnoughCreditException : public Exception
{
public:
  NotEnoughCreditException() : Exception("Not Enough Credit") {}
};
