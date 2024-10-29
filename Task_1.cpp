#include <iostream>
#include <thread>
#include <mutex>
#include <map>

std::multimap<int, std::string> results;
std::mutex accsessResults;

void swimmer(int speed, std::string name) {    
    int distanceCovered = 0;
    int second = 0;
    while (100 != distanceCovered) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        distanceCovered += speed;
        second++;
        if (distanceCovered > 100) {
            distanceCovered = 100;
        }
        std::cout << "\nSwimmer " << name << " cover " << distanceCovered << " meters" << std::endl;
    }
    accsessResults.lock();
    results.insert(std::pair<int, std::string>(second, name));
    accsessResults.unlock();
}

int main() {
    {        
        const int count = 6;
        int speed [count];
        std::string names [count];
        for (int i = 0; i < count; ++i) {
            int temp_speed;
            std::string temp_str;
            std::cout << "\nEnter " << i + 1 << " swimmer name and speed : ";
            std::cin >> temp_str >> temp_speed;
            speed[i] = (temp_speed);
            names[i] = (temp_str);
        }
        std::thread** swimmers = new std::thread * [count];
        for (int i = 0; i < count; ++i) {
            swimmers[i] = new std::thread(swimmer, speed[i], names[i]);
        }
        for (int i = 0; i < count;) {
            if (swimmers[i]->joinable()) {
                swimmers[i]->join();
                ++i;
            }
            else {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        for (int i = 0; i < count; ++i) {
            delete swimmers[i];
        }        
    }
    accsessResults.lock();
    std::cout << "\nResul is : ";
    for (std::multimap<int, std::string >::iterator iter = results.begin(); iter != results.end(); ++iter) {
        std::cout << "Name is : " << iter->second << " Result is : " << iter->first << std::endl;
    }
    accsessResults.unlock();        
}
