
#include "gfx/core/color.hpp"
#include "reactor/config.hpp"
#include "gfx/ui/window_manager.hpp"
#include "reactor/view/reactor.hpp"

int
main()
{
    gfx::ui::WindowManager wm( config::Reactor::Window::Width,
                               config::Reactor::Window::Height,
                               config::Reactor::Window::Title );

    wm.setDeltaTime( config::Reactor::Physics::DeltaTime );
    wm.setBackgroundColor( gfx::core::Color( 10, 10, 10 ) );

    wm.addWidget( std::make_unique<reactor::view::Reactor>() );

    wm.run();

    return 0;
}
