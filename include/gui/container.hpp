#pragma once

#include "gui/container_state.hpp"
#include "gui/widget.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <vector>

namespace gui {

class Container : public sf::Drawable {
  public:
    Container() = default;

    void
    HandleEvents()
    {
        for ( auto& widget : widgets_ )
        {
            widget->HandleEvents( *state_ );
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

    void
    SetState( std::unique_ptr<ContainerState>&& state )
    {
        state_ = std::move( state );
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
