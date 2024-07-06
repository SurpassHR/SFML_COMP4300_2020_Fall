#ifndef UTILS_H
#define UTILS_H

#include <string>

void log(const std::string& file, int line, const char* format, ...);

#define LOG(format, ...) log(__FILE__, __LINE__, format, ##__VA_ARGS__)

template<typename T>
T correctValueByLimit(T val, T floor, T ceil);

#endif // UTILS_H