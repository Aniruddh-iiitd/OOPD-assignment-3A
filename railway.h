// railway.h
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <utility>

class RailwayException : public std::exception {
protected:
    std::string message;
public:
    explicit RailwayException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidTimeException : public RailwayException {
public:
    InvalidTimeException() : RailwayException("Invalid time provided! Time must be between 0-1439 minutes or departure must be after arrival.") {}
};

class PlatformConflictException : public RailwayException {
public:
    PlatformConflictException() : RailwayException("Platform already occupied in this time slot!") {}
};

class InvalidPlatformException : public RailwayException {
public:
    InvalidPlatformException() : RailwayException("Invalid platform number!") {}
};

