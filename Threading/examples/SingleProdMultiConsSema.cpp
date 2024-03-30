#include <format>
#include <iostream>
#include <random>
#include <semaphore>
#include <thread>

using namespace std;

int shared = 0;
binary_semaphore consume { 0 };
binary_semaphore produce { 1 };
bool needProduce = true;
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

static void consumer(int id, int n)
{
    int min = 1, max = 1000;
    random_device randev;
    default_random_engine eng(randev());
    uniform_int_distribution dist(min, max);
    int want = 0, debt = 0;
    while (!marketClosed && n > 0)
    {
        consume.acquire();
        want = dist(eng);
        int need = want + debt;
        int tmp = need - shared;
        debt = need > shared ? tmp : 0;
        shared = shared >= need ? shared - need : 0;

        if (debt)
        {
            output("consumer:", id, "wanted:", want, "remaining:", shared, "debt:", debt);
			needProduce = true;
        }
        else
        {
            output("consumer:", id, "consumed:", need, "remaining:", shared);
            --n;
        }
	    produce.release();
    }
}

static void producer()
{
    int min = 2500, max = 5000;
    random_device randev;
    default_random_engine eng(randev());
    uniform_int_distribution dist(min, max);
    while (true)
    {
        produce.acquire();
        if (marketClosed) return;
        if (needProduce)
        {
            shared = dist(eng);
            output("produced:", shared);
            needProduce = false;
        }
        consume.release();
    }
}

int main()
{
    int min = 2, max = 5;
    random_device randev;
    default_random_engine eng(randev());
    uniform_int_distribution dist(min, max);
    vector<jthread> consumers;
    int transactions = 3;
    for (int i = dist(eng); i > 0; --i)
		consumers.push_back(jthread(consumer, i, transactions));
    jthread t2(producer);

    cout << "There are " << consumers.size() << " consumers\n";
    for (auto &t : consumers)
        t.join();
    marketClosed = true;
    produce.release();
    return 0;
}
