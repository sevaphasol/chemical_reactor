#pragma once

#include "gui/widget.hpp"
#include <SFML/Window/Event.hpp>

namespace gui {

template<typename Derived>
class Draggable {
  public:
    void
    HandleDragEvent( const sf::Event& event )
    {
        if ( event.type == sf::Event::MouseButtonPressed )
        {
            if ( event.mouseButton.button == sf::Mouse::Left )
            {
                sf::Vector2f mouse_pos( static_cast<float>( event.mouseButton.x ),
                                        static_cast<float>( event.mouseButton.y ) );
                if ( self().PointInside( mouse_pos ) )
                {
                    is_dragging_ = true;
                    drag_offset_ = mouse_pos - self().GetPos();
                }
            }
        } else if ( event.type == sf::Event::MouseButtonReleased )
        {
            is_dragging_ = false;
        } else if ( event.type == sf::Event::MouseMoved && is_dragging_ )
        {
            sf::Vector2f mouse_pos( static_cast<float>( event.mouseMove.x ),
                                    static_cast<float>( event.mouseMove.y ) );
            self().SetPos( mouse_pos - drag_offset_ );
        }
    }

  private:
    bool         is_dragging_ = false;
    sf::Vector2f drag_offset_;

    Derived&
    self()
    {
        return *static_cast<Derived*>( this );
    }

    const Derived&
    self() const
    {
        return *static_cast<const Derived*>( this );
    }
};

} // namespace gui
