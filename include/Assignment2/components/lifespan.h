#ifndef LIFESPAN_H
#define LIFESPAN_H

#include <cstdlib>

class Lifespan {
public:
    Lifespan(unsigned long long createFrame, unsigned long long lifespan = ULONG_LONG_MAX)
        : frameCreated(createFrame),
        lifespan(lifespan) {}
    ~Lifespan() = default;
public:
    unsigned long long lifespan{ 0 };
    unsigned long long frameCreated{ 0 };
};

#endif // LIFESPAN_H