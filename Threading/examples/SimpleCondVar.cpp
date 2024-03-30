#include <condition_variable>
#include <iostream>
#include <format>
#include <mutex>
#include <random>
#include <thread>

using namespace std;

int shared = 0;
mutex mut;
condition_variable cv;
bool ready = false;

static void output(string msg, int data)
{
    cout << format("{:10s} {:3d}\n", msg, data);
}

static void consumer(int n)
{
    unique_lock<mutex> ul(mut);
    while (n-- > 0)
    {
        cv.wait(ul, []() { return ready; });
        output("received:", shared);
        ready = false;
        cv.notify_one();
    }
}

static void producer(int n)
{
    int min = 1, max = 1000;
    random_device randev;
    default_random_engine eng(randev());
    uniform_int_distribution dist(min, max);
	unique_lock<mutex> ul(mut);
    while (n-- > 0)
    {
        shared = dist(eng);
        output("produced:", shared);
        ready = true;
        cv.notify_one();
        cv.wait(ul, []() { return !ready; });
    }
}

int main()
{
    int times = 10;
    jthread t1(consumer, times);
    jthread t2(producer, times);
    return 0;
}
