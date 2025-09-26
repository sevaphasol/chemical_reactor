#pragma once

#include "gui/container_state.hpp"
#include "gui/widget.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <vector>

namespace gui {

class Container : public sf::Drawable {
  public:
    explicit Container( std::unique_ptr<ContainerState>&& state ) : state_( std::move( state ) ) {}

    void
    HandleEvents( const sf::Event& event )
    {
        for ( auto& widget : widgets_ )
        {
            widget->HandleEvents( event );
        }
    }

    void
    Update()
    {
        for ( auto& widget : widgets_ )
        {
            widget->Update( *state_ );
        }
    }

    void
    AddWidget( std::unique_ptr<Widget> widget )
    {
        widgets_.push_back( std::move( widget ) );
    }

  private:
    virtual void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        for ( const auto& widget : widgets_ )
        {
            target.draw( *widget, states );
        }
    }

  private:
    std::unique_ptr<ContainerState> state_;

    std::vector<std::unique_ptr<Widget>> widgets_;
};

} // namespace gui
