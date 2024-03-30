#include <condition_variable>
#include <chrono>
#include <iostream>
#include <format>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;

int shared = 0;
mutex mut;
condition_variable theConsumers;
bool inProgress = true;
condition_variable theProducer;
bool needProduce = true;
bool hasTransaction = false;
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
    unique_lock<mutex> ul(mut);
    int want = 0, debt = 0;
    while (!marketClosed)
    {
        theConsumers.wait(ul, []() { return !inProgress; });
        inProgress = true;
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
		hasTransaction = true;
		theProducer.notify_one();
		if (n == 0) return;
    }
}

static void producer()
{
    int min = 2500, max = 5000;
    random_device randev;
    default_random_engine eng(randev());
    uniform_int_distribution dist(min, max);
	unique_lock<mutex> ul(mut);
    while (!marketClosed)
    {
        if (needProduce)
        {
            shared = dist(eng);
            output("produced:", shared);
            needProduce = false;
        }
        hasTransaction = false;
		inProgress = false;
		theConsumers.notify_all();
        theProducer.wait(ul, []() { return needProduce || hasTransaction || marketClosed; });
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
    jthread p(producer);

    cout << "There are " << consumers.size() << " consumers\n";
    for (auto &t : consumers)
        t.join();
    marketClosed = true;
    theProducer.notify_one();
    return 0;
}
