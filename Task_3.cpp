#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex accessCook;
std::mutex accessDilivery;

void dilivery(std::string dish) {
    std::lock_guard<std::mutex> guard(accessDilivery);
    std::cout << "\n...Courier take order " << dish << "..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << "\n...Courier return..." << std::endl;       
}

void restaurant(std::string orderedDish) {
    std::lock_guard<std::mutex> guard(accessCook);
    std::this_thread::sleep_for(std::chrono::seconds((rand() % 11) + 5));
    std::cout << "\n***Dish order " << orderedDish << " is cooked***" << std::endl;    
    std::thread courir (dilivery, orderedDish);
    courir.join();    
}

int main() {
    int count = 10;
    std::vector<std::thread> restaurantOrders;
    for (int i = 0; i < count; ++i) {
        int temp_time = (rand() % 6) + 5;
        int choiceDishes = rand() % 5;
        std::this_thread::sleep_for(std::chrono::seconds(temp_time));
        std::string dishes[]{ "pizza","soup","steak","salad","sushi" };
        std::string orderedDish = dishes[choiceDishes];        
        std::cout << "\n*New order : " << orderedDish << std::endl;
        restaurantOrders.push_back(std::thread(restaurant, orderedDish));
    }
    for (int i = 0; i < count;) {
        if (restaurantOrders[i].joinable()) {
            restaurantOrders[i].join();
            ++i;
        }
        else {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    std::cout << "\nAll work done for this day!" << std::endl;  
}
