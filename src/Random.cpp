#include "Random.h"
#include <random>
#include <ctime>

using namespace std;
int randomInt(const int &a, const int &b)
{
    random_device dev;
    uniform_int_distribution<int> rd(a, b);
    return rd(dev);
}

double randomDouble(const double &min, const double &max)
{
    srand(time(NULL));
    double rr[50];
    int rrr = randomInt(0, 49);
    for (int i = 0; i <= 49; i++)
    {
        rr[i] = ((double)rand() / RAND_MAX) * (max - min) + min;
    }
    return rr[rrr];
}

double normalRandom(const double &mid, const double &a)
{
    srand(time(NULL));
    default_random_engine gen;
    normal_distribution<double> ndist(mid, a);
    double result, min, max;
    double rd[1000];
    int nr = randomInt(0, 999);

    for (int i = 0; i < 1000; i++)
    {
        rd[i] = ndist(gen);
        if (i == 0)
        {
            min = rd[i];
            max = rd[i];
        }
        if (rd[i] > max)
            max = rd[i];
        else if (rd[i] < min)
            min = rd[i];
    }

    return rd[nr];
}