#ifndef LIFESPAN_H
#define LIFESPAN_H

class Lifespan {
public:
    Lifespan(unsigned long long lifespan, unsigned long long createFrame) : lifespan(lifespan), frameCreated(createFrame) {}
    ~Lifespan() = default;
public:
    unsigned long long lifespan{ 0 };
    unsigned long long frameCreated{ 0 };
};

#endif // LIFESPAN_H