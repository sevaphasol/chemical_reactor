#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Context.hpp>
#include "config.hpp"
#include "reactor/window.hpp"

int
main()
{
    reactor::ReactorWindow application( config::Reactor::Window::Width,
                                        config::Reactor::Window::Height,
                                        config::Reactor::Window::Title );

    application.Run();

    return 0;
}
