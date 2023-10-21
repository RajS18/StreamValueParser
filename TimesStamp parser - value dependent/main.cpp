#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <math.h>
int main() {
    std::ifstream file("test1.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening the CSV file." << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line);

    auto startTime = std::chrono::high_resolution_clock::now();
    double threshold = 1.0;  
    double currentTime = 0.0; 

    while (std::getline(file, line)) {
        double timestamp = std::stod(line);
        if (timestamp > threshold) {            
            double timeToWait = (threshold - currentTime) * 1000000;
            if (timeToWait > 0) {
                std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long long>(timeToWait)));
            }
            if(threshold+1<timestamp){
                std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long long>((timestamp - threshold)*1000000)));
                threshold = std::ceil(timestamp);
            }else{
                threshold++;
            }
            std::cout<<"----------------------------\n";
        }
        std::cout << "Timestamp: " << timestamp << std::endl;
        currentTime = timestamp;

    }
    file.close();
    return 0;
}
