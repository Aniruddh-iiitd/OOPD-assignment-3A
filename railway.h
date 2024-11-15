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

class Platform {
private:
    int platformNumber;
    std::map<int, std::pair<int, bool>> timeSlots; 
    
    bool isValidTime(int timeInMinutes) const {
        return timeInMinutes >= 0 && timeInMinutes < 1440;
    }
    
    bool isTimeSlotAvailable(int arrivalTime, int departureTime, bool isStoppage) const {

        int newBlockedUntil = isStoppage ? departureTime + 30 : arrivalTime + 10;

        for (const auto& slot : timeSlots) {
            int existingArrival = slot.first;
            int existingDeparture = slot.second.first;
            bool existingIsStoppage = slot.second.second;

            int existingBlockedUntil = existingIsStoppage ? existingDeparture + 30 : existingArrival + 10;

            if ((arrivalTime >= existingArrival && arrivalTime < existingBlockedUntil) || 
                (newBlockedUntil > existingArrival && arrivalTime < existingArrival)) {
                return false;
            }
        }
        return true;
    }

public:
    explicit Platform(int number) : platformNumber(number) {
        if (number <= 0) {
            throw InvalidPlatformException();
        }
    }

    void scheduleTrain(int arrivalTime, int departureTime, bool isStoppage) {
        if (!isValidTime(arrivalTime) || !isValidTime(departureTime) || departureTime <= arrivalTime) {
            throw InvalidTimeException();
        }
        
        if (!isTimeSlotAvailable(arrivalTime, departureTime, isStoppage)) {
            throw PlatformConflictException();
        }

        timeSlots[arrivalTime] = {departureTime, isStoppage};
    }

    int getPlatformNumber() const { 
        return platformNumber; 
    }
    
    bool isAvailable(int arrivalTime, int departureTime, bool isStoppage) const {
        if (!isValidTime(arrivalTime) || !isValidTime(departureTime) || departureTime <= arrivalTime) {
            return false;
        }
        return isTimeSlotAvailable(arrivalTime, departureTime, isStoppage);
    }
};

class Line {
private:
    int lineNumber;
    std::vector<std::shared_ptr<Platform>> platforms;

public:
    explicit Line(int number) : lineNumber(number) {
        if (number <= 0) {
            throw RailwayException("Invalid line number!");
        }
    }

    void addPlatform(int platformNumber) {
        auto it = std::find_if(platforms.begin(), platforms.end(),
            [platformNumber](const auto& platform) { return platform->getPlatformNumber() == platformNumber; });
        
        if (it == platforms.end()) {
            platforms.push_back(std::make_shared<Platform>(platformNumber));
        }
    }

    bool scheduleTrain(int platformNumber, int arrivalTime, int departureTime, bool isStoppage) {
        auto it = std::find_if(platforms.begin(), platforms.end(),
            [platformNumber](const auto& platform) { return platform->getPlatformNumber() == platformNumber; });
            
        if (it == platforms.end()) {
            throw InvalidPlatformException();
        }
        
        (*it)->scheduleTrain(arrivalTime, departureTime, isStoppage);
        return true;
    }

    int getLineNumber() const { 
        return lineNumber; 
    }
    
    size_t getPlatformCount() const { 
        return platforms.size(); 
    }
};

template<typename T>
class Station {
private:
    T stationId;
    std::string stationName;
    std::vector<std::shared_ptr<Line>> lines;

    bool isValidStationName(const std::string& name) const {
        return !name.empty() && name.length() <= 50;
    }

public:
    Station(T id, const std::string& name) : stationId(id), stationName(name) {
        if (!isValidStationName(name)) {
            throw RailwayException("Invalid station name!");
        }
    }

    void addLine(int lineNumber) {
        auto it = std::find_if(lines.begin(), lines.end(),
            [lineNumber](const auto& line) { return line->getLineNumber() == lineNumber; });
            
        if (it == lines.end()) {
            lines.push_back(std::make_shared<Line>(lineNumber));
        }
    }

    void addPlatformToLine(int lineNumber, int platformNumber) {
        auto it = std::find_if(lines.begin(), lines.end(),
            [lineNumber](const auto& line) { return line->getLineNumber() == lineNumber; });
            
        if (it == lines.end()) {
            throw RailwayException("Line not found!");
        }
        
        (*it)->addPlatform(platformNumber);
    }

    void scheduleTrain(int lineNumber, int platformNumber, int arrivalTime, int departureTime, bool isStoppage) {
        auto it = std::find_if(lines.begin(), lines.end(),
            [lineNumber](const auto& line) { return line->getLineNumber() == lineNumber; });
            
        if (it == lines.end()) {
            throw RailwayException("Line not found!");
        }
        
        (*it)->scheduleTrain(platformNumber, arrivalTime, departureTime, isStoppage);
    }

    T getId() const { 
        return stationId; 
    }
    
    std::string getName() const { 
        return stationName; 
    }
    
    size_t getLineCount() const { 
        return lines.size(); 
    }
};