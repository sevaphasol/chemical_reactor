
#include "gfx/ui/window_manager.hpp"
#include "reactor/view/reactor.hpp"
#include "reactor/model/reactor.hpp"
#include "reactor/controller/reactor.hpp"
#include "reactor/config.hpp"
#include <memory>

int
main()
{
    gfx::ui::WindowManager wm( config::Reactor::Window::Width,
                               config::Reactor::Window::Height,
                               config::Reactor::Window::Title );

    reactor::model::Reactor model( config::Reactor::Size.x, config::Reactor::Size.y );

    auto controller   = std::make_unique<reactor::controller::Reactor>( model );
    auto reactor_view = std::make_unique<reactor::view::Reactor>( model );

    wm.desktop_.addChild( std::move( reactor_view ) );

    wm.run();

    return 0;
}
