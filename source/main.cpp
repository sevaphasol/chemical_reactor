#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Context.hpp>
#include "application/window_manager.hpp"

int
main()
{
    application::WindowManager manager;

    manager.Run();

    return 0;
}
