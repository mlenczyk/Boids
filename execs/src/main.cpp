#include <iostream>

#include "exception.h"
#include "window.h"

using namespace std;

int main()
{
    try
    {
        Window window("Boids - flocking simulation", 800, 600);

        while(!window.IsClosed())
        {
            window.PollEvents();
        }
    }
    catch(Exception& e)
    {
        printf(e.what());
    }

    return 0;
}