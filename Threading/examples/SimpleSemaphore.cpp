#include <semaphore>
#include <iostream>
#include <format>
#include <thread>

using namespace std;

binary_semaphore consume { 0 };
binary_semaphore produce { 1 };
int shared = 0;

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
    srand(time(nullptr));
    while (n-- > 0)
    {
        produce.acquire();
        shared = rand() % 1000;
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
