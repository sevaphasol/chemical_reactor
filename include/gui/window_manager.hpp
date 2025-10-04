#pragma once

#include <reactor/molecule.hpp>
#include <reactor/reactor.hpp>
#include <reactor/graph.hpp>

#include "gfx_core/color.hpp"
#include "gfx_core/window.hpp"

namespace gui {

class WindowManager {
  public:
    explicit WindowManager( float w, float h, const std::string& title )
        : window_( w, h, title.data() ), desktop_( 0, 0, w, h )
    {
        window_.setFramerateLimit( 60 );
    }

    virtual ~WindowManager() = default;

    void
    Run()
    {
        while ( window_.isOpen() )
        {
            HandleEvents();
            Update();
            Draw();
        }
    }

  private:
    void
    HandleEvents()
    {
        gfx_core::Event event;

        while ( window_.pollEvent( event ) )
        {
            if ( event.type == gfx_core::Event::Closed )
            {
                window_.close();
            }

            desktop_.HandleEvents( event );
        }
    }

    void
    Update()
    {
        desktop_.Update();
    }

    void
    Draw()
    {
        window_.clear();
        window_.draw( desktop_ );
        window_.display();
    }

  protected:
    Widget desktop_;

  private:
    gfx_core::Window window_;
};

} // namespace gui
