#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex depotAccess;
bool depotStatus = false;

void trainTravel(char trainName, int departTime) {
    std::this_thread::sleep_for(std::chrono::seconds(departTime));    
    if (depotStatus) {
        std::cout << "\n\nTrain " << trainName << " wait for free place " << std::endl;
        std::cout << "\nEnter : ";
    }
    std::lock_guard<std::mutex> guard(depotAccess);
    depotStatus = true;
    std::cout << "\nTrain " << trainName << " deart on station. Travel time" << departTime << std::endl;
    std::string temp;
    while (temp != "depart") {
        std::cout << "\nWaiting for depart : ";
        std::cin >> temp;
    }
    std::cout << "\nTrain " << trainName << " left the station" << std::endl;
    depotStatus = false;       
}

int main() {
    int departTime[3];
    char trainName[3];    
    for (int i = 0; i < 3; ++i) {
        char temp = 'A' + i;
        trainName[i] = temp;
        std::cout << "\nEnter travel time for train " << trainName[i] << " : ";
        std::cin >> departTime[i];
    }
    std::vector<std::thread> trains;
    for (int i = 0; i < 3; ++i) {
        trains.push_back(std::thread(trainTravel, trainName[i], departTime[i]));
    }
    for (int i = 0; i < 3;) {
        if (trains[i].joinable()) {
            trains[i].join();
            ++i;
        }
        else {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } 
}
