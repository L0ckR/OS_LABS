#include <monte-carlo.hpp>

std::atomic<size_t> dotsInCircle {0};

bool IsInCircle(const Coordinats &cords, const double radius)
{
    // if ((cords.x > radius) || (cords.y > radius)){
    //     return false;                                        // нет необходимости т.к. точки генерируются от -radius до radius
    // }
    return (cords.x * cords.x + cords.y * cords.y) <= radius * radius;
}

Coordinats CreateRandCoord(const double radius, unsigned int *seed)
{
    const Coordinats cords = {
        (double)rand_r(seed) / (RAND_MAX / radius),
        (double)rand_r(seed) / (RAND_MAX / radius)};
    return cords;
}

void *task(void *input)
{
    size_t counter = 0;
    for (size_t i = 0; i < (reinterpret_cast<Args *>(input))->dotsPerThread; i++)
    {
        if (IsInCircle(CreateRandCoord((reinterpret_cast<Args *>(input))->radius, (reinterpret_cast<Args *>(input))->seed), (reinterpret_cast<Args *>(input))->radius))
        {
            counter++;
        }
    }
    delete (reinterpret_cast<Args *>(input))->seed;
    dotsInCircle.fetch_add(counter, std::memory_order_relaxed);
    pthread_exit(0);
}

double CircleArea(const size_t threadQuantity, const double radius, const size_t dotsQuantity)
{
    double result = 0;
    if (threadQuantity >= 1)
    {
        time_t currentTime = time(nullptr);
        const size_t actualThreadQuantity = std::min(threadQuantity, dotsQuantity);
        std::vector<pthread_t> threads(actualThreadQuantity);

        const size_t dotsPerThread = dotsQuantity / actualThreadQuantity;

        std::vector<Args> argsForThread(actualThreadQuantity);

        for (size_t i = 0; i < actualThreadQuantity; i++)
        {   
            argsForThread[i].radius = radius;
            argsForThread[i].dotsPerThread = dotsPerThread;
            argsForThread[i].seed = new unsigned int;
            *argsForThread[i].seed = currentTime + i;
            if ((i + 1) * dotsPerThread >= dotsQuantity)
            {
                argsForThread[i].dotsPerThread = dotsQuantity - i * dotsPerThread;
                pthread_create(&threads[i], nullptr, task, reinterpret_cast<void *>(&argsForThread[i]));
            }
            else
            {
                pthread_create(&threads[i], nullptr, task, reinterpret_cast<void *>(&argsForThread[i]));
            }
        }

        for (auto &thread : threads)
        {
            pthread_join(thread, nullptr);
        }
        result = ((double)dotsInCircle / dotsQuantity);
    }
    else
    {
        size_t dotsInCircleSingle = 0;
        unsigned int seed = (unsigned)time(nullptr);
        for (size_t i = 0; i < dotsQuantity; i++)
        {
            if (IsInCircle(CreateRandCoord(radius, &seed), radius))
            {
                dotsInCircleSingle++;
            }
        }
        result = ((double)dotsInCircleSingle / dotsQuantity);
    }
    return ((2 * radius) * (2 * radius)) * result;
}
