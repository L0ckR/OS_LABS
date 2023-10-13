#include <monte-carlo.hpp>



bool IsInCircle(const Coordinates &cords, double radius)
{
    return (cords.x * cords.x + cords.y * cords.y) <= radius * radius;
}

Coordinates CreateRandCoord(double radius, unsigned int &seed)
{
    Coordinates cords = {
        (double)rand_r(&seed) / (RAND_MAX / radius),
        (double)rand_r(&seed) / (RAND_MAX / radius)};
    return cords;
}

void *task(void *input)
{
    const auto &args = *(reinterpret_cast<Args *>(input));
    unsigned int seed = args.seed;
    size_t counter = 0;
    for (size_t i = 0; i < args.dotsPerThread; i++)
    {

        if (IsInCircle(CreateRandCoord(args.radius, seed), args.radius))
        {
            counter++;
        }
    }
    (*args.dotsInCircle).fetch_add(counter);
    return nullptr;
}

double CircleArea(size_t threadQuantity, double radius, size_t dotsQuantity)
{
    std::atomic<size_t> dotsInCircle {0};
    double result = 0;
    if (threadQuantity >= 1)
    {
        const size_t actualThreadQuantity = std::min(threadQuantity, dotsQuantity);
        std::vector<pthread_t> threads(actualThreadQuantity);

        const size_t dotsPerThread = dotsQuantity / actualThreadQuantity;

        std::vector<Args> argsForThread(actualThreadQuantity);

        for (size_t i = 0; i < actualThreadQuantity; i++)
        {   
            argsForThread[i].radius = radius;
            argsForThread[i].dotsPerThread = dotsPerThread;
            argsForThread[i].dotsInCircle = &dotsInCircle;
            argsForThread[i].seed += i;
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
            if (IsInCircle(CreateRandCoord(radius, seed), radius))
            {
                ++dotsInCircleSingle;
            }
        }
        result = ((double)dotsInCircleSingle / dotsQuantity);
    }
    return ((2 * radius) * (2 * radius)) * result;
}
