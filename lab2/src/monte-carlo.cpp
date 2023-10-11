#include <monte-carlo.hpp>

bool IsInCircle(const Coordinats &cords, const double radius)
{
    // if ((cords.x > radius) || (cords.y > radius)){
    //     return false;                                        // нет необходимости т.к. точки генерируются от -radius до radius
    // }
    return (cords.x * cords.x + cords.y * cords.y) <= radius * radius;
}

Coordinats CreateRandCoord(const double radius, unsigned int * seed)
{
    const Coordinats cords = {
        (double)rand_r(seed) / (RAND_MAX / radius),
        (double)rand_r(seed) / (RAND_MAX / radius)};
    return cords;
}

void task(const double radius, std::atomic<size_t> &dotsInCircle, const size_t dotsPerThread, unsigned int *seed)
{
    size_t counter = 0;
    for (size_t i = 0; i < dotsPerThread; i++)
    {
        if (IsInCircle(CreateRandCoord(radius, seed), radius))
        {
            counter++;
        }
    }
    dotsInCircle.fetch_add(counter, std::memory_order_relaxed);
}

double CircleArea(const size_t threadQuantity, const double radius, const size_t dotsQuantity)
{

    if (threadQuantity >= 1)
    {
        time_t currentTime = time(nullptr);
        std::atomic<size_t> dotsInCircle{0};
        const size_t actualThreadQuantity = std::min(threadQuantity, dotsQuantity);
        std::vector<std::thread> threads;
        threads.reserve(actualThreadQuantity);

        const size_t dotsPerThread = dotsQuantity / actualThreadQuantity;

        for (size_t i = 0; i < dotsQuantity; i += dotsPerThread)
        {
            unsigned int seed =  currentTime + (i % dotsPerThread);
            if (i + dotsPerThread >= dotsQuantity)
            {
                size_t dotsPerLastThread = dotsQuantity - i;
                threads.emplace_back(task, std::ref(radius), std::ref(dotsInCircle), std::ref(dotsPerLastThread), &seed);
            }
            else
            {
                threads.emplace_back(task, std::ref(radius), std::ref(dotsInCircle), std::ref(dotsPerThread), &seed);
            }
        }

        for (auto &thread : threads)
        {
            thread.join();
        }

        return ((2 * radius) * (2 * radius)) * ((double)dotsInCircle / dotsQuantity);
    }
    else
    {
        size_t dotsInCircle = 0;
        unsigned int seed = (unsigned)time(nullptr);
        for (size_t i = 0; i < dotsQuantity; i++)
        {
            if (IsInCircle(CreateRandCoord(radius, &seed), radius))
            {
                dotsInCircle++;
            }
        }
        return ((2 * radius) * (2 * radius)) * ((double)dotsInCircle / dotsQuantity);
    }
}
