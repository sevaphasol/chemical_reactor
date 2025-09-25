#pragma once

#include "application/widget.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <vector>

namespace application {

template<typename GlobalStateType>
class Container : public sf::Drawable {
  public:
    Container() = default;

    void
    HandleEvents()
    {
        for ( auto& widget : widgets_ )
        {
            widget->HandleEvents();
        }
    }

    void
    Update()
    {
        for ( auto& widget : widgets_ )
        {
            widget->Update( global_state_ );
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
    std::vector<std::unique_ptr<Widget>> widgets_;

    GlobalStateType global_state_;
};

} // namespace application
