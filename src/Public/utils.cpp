#include "utils.h"
#include <cstdarg>

const char* getFileName(const char* path) {
    const char* fileName = path;
    for (const char* p = path; *p; p++) {
        if (*p == '/' || *p == '\\') {
            fileName = p + 1;
        }
    }
    return fileName;
}

void log(const std::string& file, int line, const char* format, ...)
{
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args);
    va_end(args);

    std::string message(buffer);

    printf("[%s:%d]: %s\n", getFileName(file.c_str()), line, message.c_str());
}

template<typename T>
T correctValueByLimit(T val, T floor, T ceil) {
    if (val < floor) {
        return floor;
    } else if (val > ceil) {
        return ceil;
    }
    return val;
}