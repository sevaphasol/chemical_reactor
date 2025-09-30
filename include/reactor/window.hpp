#pragma once

#include "config.hpp"
#include "gui/window_manager.hpp"
#include "reactor/reactor.hpp"
#include <memory>

namespace reactor {

class ReactorWindow : public gui::WindowManager {
  public:
    explicit ReactorWindow( float w, float h, const std::string& title, const sf::Uint32& style )
        : gui::WindowManager( w, h, title, style )
    {
        desktop_.AddChild( std::make_unique<Reactor>( config::Reactor::Position,
                                                      config::Reactor::Size,
                                                      config::Reactor::BackGroundColor ) );
    }
};

} // namespace reactor
