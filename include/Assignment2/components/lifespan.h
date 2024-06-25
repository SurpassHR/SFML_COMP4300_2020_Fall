#ifndef LIFESPAN_H
#define LIFESPAN_H

class Lifespan {
public:
    Lifespan(int lifespan, int createFrame) : lifespan(lifespan), frameCreated(createFrame) {}
    ~Lifespan() = default;
public:
    int lifespan{ 0 };
    int frameCreated{ 0 };
};

#endif // LIFESPAN_H