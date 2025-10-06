#include "reactor/view/window_manager.hpp"
#include "reactor/config.hpp"
#include "reactor/view/reactor.hpp"

namespace reactor {
namespace view {

WindowManager::WindowManager( float w, float h, const char* title )
    : gfx::ui::WindowManager( w, h, title ),
      model_( config::Reactor::Size.x, config::Reactor::Size.y ), controller_( model_ )
{
    setDeltaTime( config::Reactor::Physics::DeltaTime );

    desktop_.addChild( std::make_unique<reactor::view::Reactor>( model_ ) );
}

} // namespace view
} // namespace reactor
