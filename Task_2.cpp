#include <iostream>
#include <thread>
#include <mutex>

std::mutex depotAccess;
bool depotStatus = false;

void trainTravel(char trainName, int departTime) {
    std::this_thread::sleep_for(std::chrono::seconds(departTime));    
    if (depotStatus) {
        std::cout << "\n\nTrain " << trainName << " wait for free place " << std::endl;
        std::cout << "\nEnter : ";
    }
    depotAccess.lock();
    depotStatus = true;
    std::cout << "\nTrain " << trainName << " deart on station. Travel time" << departTime << std::endl;
    std::string temp;
    while (temp != "depart") {
        std::cout << "\nWaiting for depart : ";
        std::cin >> temp;
    }
    std::cout << "\nTrain " << trainName << " left the station" << std::endl;
    depotStatus = false;
    depotAccess.unlock();     
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
    std::thread** trains = new std::thread * [3];
    for (int i = 0; i < 3; ++i) {
        trains[i] = new std::thread(trainTravel, trainName[i], departTime[i]);
    }
    for (int i = 0; i < 3;) {
        if (trains[i]->joinable()) {
            trains[i]->join();
            ++i;
        }
        else {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    
    delete [] trains;
   
}

