#include <format>
#include <iostream>
#include <random>
#include <semaphore>
#include <thread>

using namespace std;

int shared = 0;
binary_semaphore consume { 0 };
binary_semaphore produce { 1 };

static void output(string msg, int data)
{
    cout << format("{:10s} {:3d}\n", msg, data);
}

static void consumer(int n)
{
    while (n-- > 0)
    {
        consume.acquire();
        output("received:", shared);
        produce.release();
    }
}

static void producer(int n)
{
    int min = 1, max = 1000;
    random_device randev;
    default_random_engine eng(randev());
    uniform_int_distribution dist(min, max);
    while (n-- > 0)
    {
        produce.acquire();
        shared = dist(eng);
        output("produced:", shared);
        consume.release();
    }
}

int main()
{
    int times = 10;
    jthread t1(consumer, times);
    jthread t2(producer, times);
    return 0;
}
