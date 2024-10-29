#include <iostream>
#include <thread>
#include <mutex>

std::mutex accessCook;
std::mutex accessDilivery;

void dilivery(std::string dish) {
    accessDilivery.lock();
    std::cout << "\n...Courier take order " << dish << "..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << "\n...Courier return..." << std::endl;    
    accessDilivery.unlock();
}

void restaurant(std::string orderedDish) {
    std::this_thread::sleep_for(std::chrono::seconds((rand() % 11) + 5));
    std::cout << "\n***Dish order " << orderedDish << " is cooked***" << std::endl;
    accessCook.lock();
    std::thread* courir = new std::thread(dilivery, orderedDish);
    courir->join();
    delete courir;
    accessCook.unlock();
}

int main() {
    int count = 10;
    std::thread** restaurantOrders = new std::thread * [count];
    for (int i = 0; i < count; ++i) {
        int temp_time = (rand() % 6) + 5;
        int choiceDishes = rand() % 5;
        std::this_thread::sleep_for(std::chrono::seconds(temp_time));
        std::string dishes[]{ "pizza","soup","steak","salad","sushi" };
        std::string orderedDish = dishes[choiceDishes];        
        std::cout << "\n*New order : " << orderedDish << std::endl;
        restaurantOrders[i] = new std::thread(restaurant, orderedDish);
    }
    for (int i = 0; i < count;) {
        if (restaurantOrders[i]->joinable()) {
            restaurantOrders[i]->join();
            ++i;
        }
        else {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    std::cout << "\nAll work done for this day!" << std::endl;
    for (int i = 0; i < count; ++i) {
        delete restaurantOrders[i];
    }   
}
