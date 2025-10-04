// text.hpp — обновлённая версия
#pragma once

#include "gfx_core/font.hpp"
#include "gfx_core/rect.hpp"
#include "gfx_core/text.hpp"
#include "gfx_core/transform.hpp"
#include "gfx_core/window.hpp"
#include "gui/widget.hpp"
#include <string>

namespace gui {

class Text : public Widget {
  public:
    explicit Text( const gfx_core::Vector2f& pos,
                   const std::string&        text,
                   const std::string&        font_name,
                   unsigned int              font_size,
                   const gfx_core::Color&    text_color )
        : Widget( pos )
    {
        font_.loadFromFile( font_name );
        text_.setFont( font_ );
        text_.setCharacterSize( font_size );
        text_.setString( text );
        text_.setFillColor( text_color );
    }

    explicit Text( const gfx_core::Vector2f& pos,
                   const std::string&        text,
                   const gfx_core::Font&     font,
                   unsigned int              font_size,
                   const gfx_core::Color&    text_color )
        : Widget( pos ), font_( font ), text_( text, font, font_size )
    {
        text_.setFillColor( text_color );
    }

    void
    SetString( const std::string& str )
    {
        text_.setString( str );
    }

    gfx_core::FloatRect
    GetLocalBounds() const
    {
        return text_.getLocalBounds();
    }

    void
    MoveInCenterOfRect( const gfx_core::Vector2f& rect_pos, const gfx_core::Vector2f& rect_size )
    {
        const gfx_core::FloatRect text_bounds = text_.getLocalBounds();
        text_.setOrigin( text_bounds.x + text_bounds.w / 2.0f,
                         text_bounds.y + text_bounds.h / 2.0f );
        text_.setPosition( rect_pos.x + rect_size.x / 2.0f, rect_pos.y + rect_size.y / 2.0f );
    }

    virtual void
    DrawSelf( gfx_core::Window& window, gfx_core::Transform transform ) const override
    {
        // transform.translate( GetPos() );
        window.draw( text_, transform );
    }

  private:
    gfx_core::Font font_;
    gfx_core::Text text_;
};

} // namespace gui
