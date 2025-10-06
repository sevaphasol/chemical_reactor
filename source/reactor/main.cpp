
#include "reactor/config.hpp"
#include "reactor/view/window_manager.hpp"

int
main()
{
    reactor::view::WindowManager wm( config::Reactor::Window::Width,
                                     config::Reactor::Window::Height,
                                     config::Reactor::Window::Title );

    wm.run();

    return 0;
}
