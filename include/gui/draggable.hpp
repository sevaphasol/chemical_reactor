#pragma once

#include <SFML/Window/Event.hpp>

namespace gui {

template<typename Derived>
class Draggable {
  public:
    void
    HandleDragEvent( const sf::Event& event )
    {
        switch ( event.type )
        {
            case sf::Event::MouseButtonPressed:
                HandleMousePress( event );
                break;
            case sf::Event::MouseMoved:
                HandleMouseMove( event );
                break;
            case sf::Event::MouseButtonReleased:
                is_dragging_ = false;
                break;
            default:
                return;
        }
    }

    void
    HandleMousePress( const sf::Event& event )
    {
        if ( event.mouseButton.button == sf::Mouse::Right )
        {
            sf::Vector2f mouse_pos( static_cast<float>( event.mouseButton.x ),
                                    static_cast<float>( event.mouseButton.y ) );
            if ( self().PointInside( mouse_pos ) )
            {
                is_dragging_ = true;
                drag_offset_ = mouse_pos - self().GetPos();
            }
        }
    }

    void
    HandleMouseMove( const sf::Event& event )
    {
        if ( is_dragging_ )
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
