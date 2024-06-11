# 学习SFML库记录

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
        "-I${workspaceFolder}",
    ],
}
```

2. 配置SFML库系统环境

-   配置 `LD_LIBRARY_PATH` 和 `LIBRARY_PATH` 中的SFML库位置，`SFML=x:\path\to\sfml\root`
-   配置 `LD_LIBRARY_PATH` 和 `LIBRARY_PATH` 到系统变量的 `Path`，`LD_LIBRARY_PATH/LIBRARY_PATH=%SFML%\bin`
-   配置项目 `CMakeLists.txt` 查找SFML库

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
