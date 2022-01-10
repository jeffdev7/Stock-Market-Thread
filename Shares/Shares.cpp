#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <ctime>
#include <mutex>

using std::string;
using std::thread;
using std::ctime;
using std::mutex;
using std::cout;
using std::cin;
using std::endl;

string GetTime() 
{
    auto timeNow = std::chrono::system_clock::now();
    time_t sleepTime = std::chrono::system_clock::to_time_t(timeNow);
    return ctime(&sleepTime);
}

double currValue = 100;
mutex activeLock;

void GetMoney(int id, double increase)
{

    std::lock_guard<mutex> lock(activeLock); //block the currValue from being accessed by more than one thread at a time; and stricts access to the entire scope of the function once one of the other threads tries to execute
    std::this_thread::sleep_for(std::chrono::seconds(3));
    cout << "\tYield around $ " << increase << " on " << GetTime();

    if ((currValue - increase) >= 0) 
    {
        currValue += increase;
        cout << "\tNew value of the share is $" << currValue << "\n"<<endl;
    }

    if ((currValue + increase) > 235)
    {
        cout << "It seems a good time to sell it\n";
        cout << "Currently value is $" << currValue << "\n" <<endl;

    }  
}

int main()
{
    thread threads[10];
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(GetMoney, i, 15);
    }
    for (int i = 0; i < 10; ++i) {
        threads[i].join();
    }

    return 0;  
}