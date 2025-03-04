#include "MainWindow.h"
#include <cstdlib>
#include <iostream>

int main()
{
    try
    {
        MainWindow window;
        window.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unhandled exception" << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Unknown error occured!" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
