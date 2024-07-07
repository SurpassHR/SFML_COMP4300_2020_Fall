# 学习SFML库记录

- 声明: 本学习记录内容来自 David Churchill 教授的 2020 Fall COMP4300 课程，课程教授的ECS架构、数据与逻辑分离的理念等，
与我在工作上使用的一些设计思想不谋而合。在个人项目中以小游戏项目的方式相互印证的方法，来掌握工作一年来所学知识，
趣味性与实用性相结合，大赞。

- 本项目有几个初衷:
    - C++实践，C++嵌入式开发总是与硬件打交道导致感觉违背了我学编程最初的动力，简单来说不是我想写的东西；
    - 学习CMake，CMake很强大，希望深入学习；
    - 上班更体面地摸鱼；
    - 可能也会在这里做一些github workflow、CI的尝试；

## 项目当前进展

### Assignment 1

https://github.com/SurpassHR/SFML_COMP4300_2020_Fall/assets/47974229/0dee72be-545b-4deb-9d65-0bbfed5ba68d

### Assignement 2

https://github.com/SurpassHR/SFML_COMP4300_2020_Fall/assets/47974229/857e73fc-571f-4495-b2f1-1d007921800d

## 开发环境配置

1. 配置vscode clangd cmake环境

```json
{
    "cmake.configureOnEdit": true, // cmake会在CMakeLists.txt配置改变时重新配置项目
    "cmake.skipConfigureIfCachePresent": true, // 如果缓存信息存在则跳过配置项目过程
    "clangd.arguments": [
        "--compile-commands-dir=${workspaceFolder}/build", // 指明compile-commands.json生成位置
        "--completion-style=detailed",
        "--header-insertion=never",
        "--header-insertion-decorators",
        "--query-driver=D:\\ProgramFiles\\mingw64\\bin\\g*.exe",
    ],
    "clangd.fallbackFlags": [
        "-std=c++14",
        "--target=x86_64-w64-mingw", // 重要，直接可以使用系统变量/用户变量Path中配置好的MinGW路径
        "-I${workspaceFolder}",
    ],
}
```

2. 配置SFML库系统环境

-   配置 `LD_LIBRARY_PATH` 和 `LIBRARY_PATH` 中的SFML库位置，`SFML=x:\path\to\sfml\root`
-   配置 `LD_LIBRARY_PATH` 和 `LIBRARY_PATH` 到系统变量的 `Path`，`LD_LIBRARY_PATH/LIBRARY_PATH=%SFML%\bin`
-   将 `%SFML%\lib`、`%SFML%\include` 也包含到路径中
-   配置项目 `CMakeLists.txt` 查找SFML库

3. 开发环境问题及定位解决

- 2024-06-24
    - 上述配置方法已经在一台Win11 i9 11900kb和一台Win11 i7 10700验证过，但是在我18年Mi Gaming Laptop Win11 i5 8300h上出现了问题，总是提示找不到动态链接库，目前问题已解决，但是根因尚不明确
    - 解决方法:
        - SFML官网给出的SFML-2.6.1 bin构建所使用的gcc版本为13.1.0，因此下载[对应版本的gcc](https://github.com/niXman/mingw-builds-binaries/releases/tag/13.1.0-rt_v11-rev1)即可解决
    - 遗留问题:
        - 为啥另外两台gcc版本为8.1.0运行是正常的
        ```bash
        ~ ❯ gcc --version
        gcc.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
        Copyright (C) 2018 Free Software Foundation, Inc.
        This is free software; see the source for copying conditions.  There is NO
        warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
        ```

- 2024-06-27
    - 还是由于gcc版本过低导致的问题: 使用c++17的标准库filesystem时报错，更新mingw gcc版本到13.1.0解决

```cmake
set(LIB_SFML $ENV{SFML}/lib)
set(SFML_DIR ${LIB_SFML}/cmake/SFML) # 要求该路径下包含 SFMLconfigure.cmake
```

## SFML库是什么

- multi-media multi-language multi-platform Simple and Fast Multimedia Library

### SFML库基本结构

- 可以分为 Audio Graphics Network System Window 几个模块

```bash
tree . -L 1
.
|-- Audio
|-- Audio.hpp
|-- Config.hpp
|-- GpuPreference.hpp
|-- Graphics
|-- Graphics.hpp
|-- Main.hpp
|-- Network
|-- Network.hpp
|-- OpenGL.hpp
|-- System
|-- System.hpp
|-- Window
`-- Window.hpp
```

### 基本程序框架

```c++
int main()
{
    // create main window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML window");

    // start video loop
    while (window.isOpen()) {
        // do something

        // clear previous frame
        window.clear();

        // draw something
        // window.draw(sf::Drawable);

        // draw new frame
        window.display();
    }

    return EXIT_SUCCESS;
}
```

## C++ Tricks

### 符号重载

- 可以被重载的符号
    1. 赋值运算符 =：用于实现深拷贝。
    2. 算术运算符 +、-、*、/、%：可以重载为成员函数或非成员函数。
    3. 关系运算符 ==、!=、<、>、<=、>=：通常作为成员函数重载。
    4. 递增和递减运算符 ++ 和 --：可以作为前缀或后缀运算符重载。
    5. 位运算符 &、|、^、~、<<、>>：可以重载为成员函数或非成员函数。
    6. 下标运算符 []：用于访问类似数组的对象的元素。
    7. 函数调用运算符 ()：允许对象像函数一样被调用。
    8. 成员访问运算符 ->：用于访问类的成员。
    9. 类型转换运算符：允许自定义类型转换。

- 举例，重载一个学生年龄结构体的大小比较符号
```c++
struct StudentAge {
    unsigned year;
    unsigned month;
    unsigned day;
    bool operator >(const StudentAge &rhs) const {
        if (year > rhs.year) {
            return true;
        } else if (year == rhs.year) {
            if (month > rhs.month) {
                return true;
            } else if (month == rhs.month) {
                if (day > rhs.day) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};
```
- 那么在使用StudentAge类型的变量时就可以直接进行大小比较了

## CMake Tricks

- 如果我希望将一个仓库内的源文件作为公共组件提供给其他的应用使用，那么我可以将其编成一个单独的库。

- 假设现在有如下代码仓结构:

```bash
.
|-- CMakeLists.txt
|-- include
|   |-- Application
|   `-- Public
`-- src
    |-- CMakeLists.txt
    |-- Application
    |   |-- CMakeLists.txt
    |   `-- main.cpp
    `-- Public
        |-- CMakeLists.txt
        `-- utils.cpp
```

- Public组件仓 `CMakeLists.txt` 配置如下:

```cmake
# src/Public/CMakeLists.txt
FILE(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
ADD_LIBRARY(Public STATIC ${SRC})
TARGET_INCLUDE_DIRECTORIES(Public PUBLIC ${CMAKE_SOURCE_DIR}/include/Public)
```

- Application应用仓 `CMakeLists.txt` 配置如下:

```cmake
# src/Application/CMakeLists.txt
FILE(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
ADD_EXECUTABLE("Application" ${SRC})
TARGET_LINK_LIBRARIES("Application" PRIVATE Public)
```