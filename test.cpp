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

template<typename T>
void interactiveStationManagement(T stationId, const std::string& stationName) {
    try {
        Station<T> station(stationId, stationName);
        std::cout << "\nStation created successfully!\n";

        while (true) {
            std::cout << "\n=== Station Management Menu ===\n";
            std::cout << "1. Add platform to line\n";
            std::cout << "2. Schedule train\n";
            std::cout << "3. Add new line\n";
            std::cout << "4. Exit\n";

            int choice = getIntInput("Enter your choice (1-4): ", 1, 4);

            switch (choice) {
                case 1: {
                    int lineNum = getIntInput("Enter line number: ");
                    int platformNum = getIntInput("Enter platform number: ");
                    try {
                        station.addPlatformToLine(lineNum, platformNum);
                        std::cout << "Platform " << platformNum << " added to line " << lineNum << " successfully!\n";
                    } catch (const RailwayException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    break;
                }
                case 2: {
                    int lineNum = getIntInput("Enter line number: ");
                    int platformNum = getIntInput("Enter platform number: ");
                    
                    char stopType;
                    do {
                        std::cout << "Is this a stoppage (s) or through train (t)? ";
                        std::cin >> stopType;
                        clearInputBuffer();
                    } while (stopType != 's' && stopType != 't');

                    int arrivalTime = getTimeInput("arrival");
                    int departureTime = (stopType == 's') ? getTimeInput("departure") : arrivalTime + 10;

                    try {
                        station.scheduleTrain(lineNum, platformNum, arrivalTime, departureTime, stopType == 's');
                        std::cout << "Train scheduled successfully!\n";
                    } catch (const RailwayException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    break;
                }
                case 3: {
                    int lineNum = getIntInput("Enter line number: ");
                    try {
                        station.addLine(lineNum);
                        std::cout << "Line " << lineNum << " added successfully!\n";
                    } catch (const RailwayException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    break;
                }
                case 4:
                    return;
            }
        }
    } catch (const RailwayException& e) {
        std::cout << "Error creating station: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== Railway System Test Program ===\n\n";
    testStringStation();
    testIntStation();
    
    std::cout << "\n=== Interactive Testing ===\n";
    std::cout << "Select station ID type:\n";
    std::cout << "1. String ID\n";
    std::cout << "2. Integer ID\n";
    
    int choice = getIntInput("Enter (1-2): ", 1, 2);
    
    std::string stationName;
    std::cout << "Please enter station name : ";
    std::getline(std::cin, stationName);
    
    if (choice == 1) {
        int stationId = getIntInput("Enter station ID (int): ");
        interactiveStationManagement(stationId, stationName);
    } else {
        std::string stationId;
        std::cout << "Enter station ID (str): ";
        std::getline(std::cin, stationId);
        interactiveStationManagement(stationId, stationName);
    }
    
    std::cout << "\nTest program completed successfully!\n";
    return 0;
}