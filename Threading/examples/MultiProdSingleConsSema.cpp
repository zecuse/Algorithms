#include <format>
#include <iostream>
#include <random>
#include <semaphore>
#include <thread>

using namespace std;

int shared = 1000;
binary_semaphore consume { 0 };
binary_semaphore produce { 0 };
bool marketClosed = false;

template<typename S, typename I>
static void output(S msg, I data)
{
    cout << format("{:10s} {:4d}\n", msg, data);
}

template<typename S, typename I, typename ...Args>
static void output(S msg, I data, Args... args)
{
    cout << format("{:10s} {:4d} ", msg, data);
    output(args...);
}

static void consumer(int n)
{
    int min = 1, max = 2000;
    random_device randev;
    default_random_engine eng(randev());
    uniform_int_distribution dist(min, max);
    int want = 0, debt = 0;
    while (!marketClosed && n > 0)
    {
        want = dist(eng);
        int need = want + debt;
        int tmp = need - shared;
        debt = need > shared ? tmp : 0;
        shared = shared >= need ? shared - need : 0;

        if (debt)
        {
            output("wanted:", want, "remaining:", shared, "debt:", debt);
            produce.release();
			consume.acquire();
        }
        else
        {
            output("consumed:", need, "remaining:", shared);
            --n;
        }
    }
}

static void producer(int id)
{
    int min = 1000, max = 3000;
    random_device randev;
    default_random_engine eng(randev());
    uniform_int_distribution dist(min, max);
    int amount = dist(eng);
    while (true)
    {
        produce.acquire();
        if (marketClosed)
        {
            consume.release();
            return;
        }
        shared += amount;
		output("producer:", id, "supplied:", amount, "available:", shared);
        amount = dist(eng);
        consume.release();
    }
}

int main()
{
    int min = 2, max = 5;
    random_device randev;
    default_random_engine eng(randev());
    uniform_int_distribution dist(min, max);
    vector<jthread> producers;
    int transactions = 10;
    for (int i = dist(eng); i > 0; --i)
		producers.push_back(jthread(producer, i));
    jthread t2(consumer, transactions);

    cout << "There are " << producers.size() << " producers\n";
    t2.join();
    marketClosed = true;
    for (auto &t : producers)
    {
        produce.release();
        consume.acquire();
    }
    return 0;
}
