#include "reactor/view/button.hpp"
#include "reactor/config.hpp"

namespace reactor {
namespace view {

Button::Button( const gfx::core::Vector2f& pos, const gfx::core::Vector2f& size )
    : gfx::ui::Button( pos, size )
{
    updateVisuals();
}

void
Button::updateVisuals()
{
    if ( isPressed() )
    {
        setBackgroundColor( config::Reactor::Buttons::Common::Parameters::Color::Pressed );
    } else if ( isHovered() )
    {
        setBackgroundColor( config::Reactor::Buttons::Common::Parameters::Color::Hover );
    } else
    {
        setBackgroundColor( config::Reactor::Buttons::Common::Parameters::Color::Default );
    }
}

} // namespace view
} // namespace reactor
