#include <MarkWareTuya/MarkWareTuya.hpp>
#include <markwaretuya/version.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

// Standalone main entry point

auto main(int argc, char *argv[], char *env[]) -> int
{
    // init MarkWareTuya instance
    std::unique_ptr<MarkWareTuya> Lib = std::make_unique<MarkWareTuya>();

    // bye bye
    std::cout << "Bye bye!" << std::endl;

    return 0;
}
