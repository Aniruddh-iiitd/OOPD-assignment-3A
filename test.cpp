#include "railway.h"
#include <iostream>
#include <limits>
#include <string>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getIntInput(const std::string& prompt, int min = 1, int max = std::numeric_limits<int>::max()) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            clearInputBuffer();
            return value;
        }
        std::cout << "Invalid input! Please enter a number between " << min << " and " << max << std::endl;
        clearInputBuffer();
    }
}

int getTimeInput(const std::string& timeType) {
    int hours, minutes;
    while (true) {
        std::cout << "\nEnter " << timeType << " time:\n";
        hours = getIntInput("Enter hours (0-23): ", 0, 23);
        minutes = getIntInput("Enter minutes (0-59): ", 0, 59);
        return hours * 60 + minutes;
    }
}

void testStringStation() {
    std::cout << "\n=== Testing String-based Station ID ===\n";
    try {
        Station<std::string> station("NDLS", "New Delhi Railway Station");
        std::cout << "Created station: " << station.getName() << " (ID: " << station.getId() << ")\n";

        station.addPlatformToLine(1, 1);
        station.addPlatformToLine(1, 2);
        std::cout << "Added platforms 1 and 2 to line 1\n";
        
        std::cout << "\nScheduling trains...\n";
        station.scheduleTrain(1, 1, 480, 510, true);
        std::cout << "Scheduled stoppage train on platform 1 from 8:00 AM to 8:30 AM\n";
        
        station.scheduleTrain(1, 2, 490, 500, false); 
        std::cout << "Scheduled through train on platform 2 from 8:10 AM to 8:20 AM\n";

        try {
            station.scheduleTrain(1, 1, 500, 520, true);
            std::cout << "ERROR: This should have caused a PlatformConflictException\n";
        } catch (const PlatformConflictException& e) {
            std::cout << "Caught platform conflict: " << e.what() << std::endl;
        }
    } catch (const RailwayException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void testIntStation() {
    std::cout << "\n=== Testing Integer-based Station ID ===\n";
    try {
        Station<int> station(12345, "Mumbai Central");
        std::cout << "Created station: " << station.getName() << " (ID: " << station.getId() << ")\n";
        
        try {
            station.addPlatformToLine(1, 1);
            station.scheduleTrain(1, 1, 1500, 1530, true);
            std::cout << "ERROR: This should have caused an InvalidTimeException\n";
        } catch (const InvalidTimeException& e) {
            std::cout << "Caught invalid time exception: " << e.what() << std::endl;
        }
    } catch (const RailwayException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

