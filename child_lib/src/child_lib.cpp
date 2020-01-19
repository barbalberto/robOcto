// Include the declaration of our library function
#include <stdio.h>
#include <string.h>
#include <child_lib/child_lib.hpp>
#include <root_lib/root_lib.hpp>

void say_hello(std::string str)
{
    std::string hello_world;
    hello_world = "I'm child_lib: This is the message for you:\n\r" + str + "\n\nBye, have a nice day.\n";
    say_something(hello_world);
}
