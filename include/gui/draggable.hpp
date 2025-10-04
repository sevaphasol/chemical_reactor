#pragma once

#include "gfx_core/event.hpp"

namespace gui {

template<typename Derived>
class Draggable {
  public:
    void
    HandleDragEvent( const gfx_core::Event& event )
    {
        switch ( event.type )
        {
            case gfx_core::Event::MouseButtonPressed:
                HandleMousePress( event );
                break;
            case gfx_core::Event::MouseMoved:
                HandleMouseMove( event );
                break;
            case gfx_core::Event::MouseButtonReleased:
                is_dragging_ = false;
                break;
            default:
                return;
        }
    }

    void
    HandleMousePress( const gfx_core::Event& event )
    {
        if ( event.mouse_button.button == gfx_core::Mouse::Right )
        {
            gfx_core::Vector2f mouse_pos( static_cast<float>( event.mouse_button.x ),
                                          static_cast<float>( event.mouse_button.y ) );
            if ( self().PointInside( mouse_pos ) )
            {
                is_dragging_ = true;
                drag_offset_ = mouse_pos - self().GetPos();
            }
        }
    }

    void
    HandleMouseMove( const gfx_core::Event& event )
    {
        if ( is_dragging_ )
        {
            gfx_core::Vector2f mouse_pos( static_cast<float>( event.mouse_move.x ),
                                          static_cast<float>( event.mouse_move.y ) );
            self().SetPos( mouse_pos - drag_offset_ );
        }
    }

  private:
    bool               is_dragging_ = false;
    gfx_core::Vector2f drag_offset_;

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
