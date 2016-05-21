#include <iostream>
#include <thread>
#include <future>
#include <sstream>
#include <string>

std::string func(std::string input, std::string cow) {
    std::stringstream ss;
    ss << "Hello " << input << " " << cow;
    std::string s = ss.str();

    return s;
}

int main(int argc, char **argv) {

    std::future<std::string> ret1 = std::async(&func, "luke", "r");
    std::future<std::string> ret2 = std::async(&func, "aqua", "b");
    std::future<std::string> ret3 = std::async(&func, "sam", "g");
    std::future<std::string> ret4 = std::async(&func, "tom", "p");
    std::future<std::string> ret5 = std::async(&func, "niall", "b");

    std::cout << ret1.get() << std::endl;
    std::cout << ret2.get() << std::endl;
    std::cout << ret3.get() << std::endl;
    std::cout << ret4.get() << std::endl;
    std::cout << ret5.get() << std::endl;

}
