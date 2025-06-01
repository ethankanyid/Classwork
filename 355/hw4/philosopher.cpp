#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <unistd.h>
#include <mutex>
#include <chrono>
#include <thread>

using namespace std;

static int NUMBER_OF_PHILOSPHERS = 5;
static int EATING_TIME = 500; // in milliseconds
static int THINKING_TIME = 1000; // in milliseconds
static int ITERATIONS = 1;

static bool quiet = false;

static void safePrint(const string& msg);

class Syncro
{
    private:
        mutex* chopsticks;
    public:
        void putDownChopstick(int id)
        {
            //max chopstick first to prevent deadlock
            int first = max(id, (id + 1) % NUMBER_OF_PHILOSPHERS);

            //min second
            int second = min(id, (id + 1) % NUMBER_OF_PHILOSPHERS);

            // Pick up the first chopstick
            chopsticks[first].unlock();

            // Pick up the second chopstick
            chopsticks[second].unlock();
        }
        int pickUpChopstick(int id)
        {
            //min chopstick first to prevent deadlock
            int first = min(id, (id + 1) % NUMBER_OF_PHILOSPHERS);

            //max second
            int second = max(id, (id + 1) % NUMBER_OF_PHILOSPHERS);

            // Pick up the first chopstick
            bool status = chopsticks[first].try_lock();
            if (!status) return false;

            // Pick up the second chopstick
            // prevents deadlock, but causes philosopher to starve
            if (!chopsticks[second].try_lock()) {
                chopsticks[first].unlock();
                return false;
            }
            return true;
        }
        ~Syncro()
        {
            delete[] chopsticks;
        }
        Syncro()
        {
            chopsticks = new mutex[NUMBER_OF_PHILOSPHERS];
        }
};

class Philosopher
{
    int id;
    string name;

    double thought;
    double ate;
    double starved;

    Syncro* syncro;

    public:
        thread mainThread;

        Philosopher(string name, int id, Syncro* syncro)
        {
            this->syncro = syncro;
            this->name = name;
            this->id = id;

            thought = 0.0;
            ate = 0.0;
            starved = 0.0;

            // begin threading
            mainThread = thread(&Philosopher::run, this, ITERATIONS);
        }

        ~Philosopher()
        {
            if (mainThread.joinable())
            {
                mainThread.join();
            }
        }

        void think(int milliseconds = THINKING_TIME)
        {
            auto start = chrono::high_resolution_clock::now();
            safePrint("philosopher " + to_string(id) + " is thinking.\n");
            this_thread::sleep_for(chrono::milliseconds(milliseconds));

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> time = end - start;
            thought += time.count();
        }

        void eat(int milliseconds = EATING_TIME)
        {
            //starving
            auto start = chrono::high_resolution_clock::now();
            bool starving = false;
            while(!syncro->pickUpChopstick(id))
            {
                if (!starving)
                {
                    safePrint("philosopher " + to_string(id) + " is starving.\n");
                    starving = true;
                }
                this_thread::sleep_for(chrono::milliseconds(100)); // avoid busy-waiting
            }
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> time = end - start;
            starved += time.count();

            //eating
            start = chrono::high_resolution_clock::now();
            safePrint("philosopher " + to_string(id) + " started eating.\n");
            this_thread::sleep_for(chrono::milliseconds(milliseconds));
            syncro->putDownChopstick(id);
            safePrint("philosopher " + to_string(id) + " finished eating.\n");
            end = chrono::high_resolution_clock::now();
            time = end - start;
            ate += time.count();
        }

        void run(int number = ITERATIONS)
        {
            for (int i = 0; i < number; i++)
            {
                think();
                eat();
            }
        }

        void print()
        {
            cout << "philosopher " << id << endl;
            cout << "\tthought for " << fixed << setprecision(3) << thought << " seconds" << endl;
            cout << "\tate for " << fixed << setprecision(3) << ate << " seconds" << endl;
            cout << "\tstarved for " << fixed << setprecision(3) << starved << " seconds" << endl;
        }
};

const string nameArray[] = {"Yoda", "Obi-Wan", "Rey", "Kanan", "Leia", "Luke", "Ahsoka",
                          "Mace Windu", "Ezra", "Palpatine", "Anakin", "Kylo Ren", "Dooku",
                          "Kit Fitso", "Luminara", "Plo Koon", "Revan", "Thrawn", "Zeb", "Sabine"};

void dine()
{
    Syncro syncro;
    Philosopher* philosophers[NUMBER_OF_PHILOSPHERS];

    for(int i = 0; i < NUMBER_OF_PHILOSPHERS; i++)
    {
        philosophers[i] = new Philosopher(nameArray[i], i, &syncro);
    }

    // Wait for all philosopher threads to finish
    for(int i = 0; i < NUMBER_OF_PHILOSPHERS; i++)
    {
        if (philosophers[i]->mainThread.joinable())
        {
            philosophers[i]->mainThread.join();
        }
    }

    cout << endl << endl << endl;

    for(int i = 0; i < NUMBER_OF_PHILOSPHERS; i++)
    {
        philosophers[i]->print();
        delete philosophers[i];
        cout << endl;
    }
}

static void safePrint(const string& msg)
{
    if (quiet)
        return;
    // is initialized once and persists between calls
    static mutex cout_mutex;

    //locks until out of scope
    lock_guard<mutex> lock(cout_mutex);

    cout << msg;
}

int main(int argc, char* argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "p:e:t:i:hq")) != -1) {
        switch (opt) {
            case 'p':
                NUMBER_OF_PHILOSPHERS = atoi(optarg);  // Number of philosophers
                break;
            case 'e':
                EATING_TIME = atoi(optarg);  // Eating time (in ms)
                break;
            case 't':
                THINKING_TIME = atoi(optarg);  // Thinking time (in ms)
                break;
            case 'i':
                ITERATIONS = atoi(optarg);  // Number of iterations
                break;
            case 'h':
                cout << "Usage: " << argv[0] << " [-p num_philosophers] [-e eating_time] [-t thinking_time] [-i iterations]" << endl;
                exit(0);
            case 'q':
                quiet = true;
                break;
            default:
                cerr << "Usage: " << argv[0] << " [-p num_philosophers] [-e eating_time] [-t thinking_time] [-i iterations]" << endl;
                exit(EXIT_FAILURE);
        }
    }

    //iterations, wait times, philosophers
    dine();
    return 0;
}
