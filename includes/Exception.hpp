#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>
#include <exception>


#define NOT_FOUND "Not Found"
#define BAD_REQUEST "Bad Request"
#define PERMISSION_DENIED "Permission Denied"



class Exception : public std::exception
{
public:
	Exception(const std::string _msg) : msg(_msg) {}
	virtual ~Exception() throw() {}

	virtual const char *what() const throw()
	{
		return msg.c_str();
	}

private:
	std::string msg;
};


class Not_found_exception : public Exception
{
public:
    Not_found_exception() : Exception(NOT_FOUND) {}
};

class Bad_request_exception : public Exception
{
public:
    Bad_request_exception() : Exception(BAD_REQUEST) {}
};

class Permission_exception : public Exception
{
public:
    Permission_exception() : Exception(PERMISSION_DENIED) {}
};


#endif