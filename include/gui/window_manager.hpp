#pragma once

#include "application/config.hpp"
#include "application/container.hpp"
#include "application/reactor_state.hpp"
#include <SFML/Graphics.hpp>
#include <application/molecule.hpp>
#include <application/reactor.hpp>
#include <application/graph.hpp>
#include <memory>

namespace application {

class WindowManager {
  public:
    WindowManager() : window_( Config::WindowVideoMode, Config::Title, Config::WindowStyle )
    {
        window_.setFramerateLimit( 60 );

        reactor_container_.AddWidget(
            std::make_unique<Reactor>( Config::ReactorPos, Config::ReactorSize ) );
        reactor_container_.AddWidget(
            std::make_unique<Graph>( Config::NumberPlotPos, Config::NumberPlotSize, "Number" ) );
        reactor_container_.AddWidget(
            std::make_unique<Graph>( Config::EnergyPlotPos, Config::EnergyPlotSize, "Energy" ) );
    }

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
        sf::Event event;

        while ( window_.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed )
            {
                window_.close();
            }
        }

        reactor_container_.HandleEvents();
    }

    void
    Update()
    {
        reactor_container_.Update();
    }

    void
    Draw()
    {
        window_.clear();
        window_.draw( reactor_container_ );
        window_.display();
    }

  private:
    sf::RenderWindow window_;

    Container<ReactorState> reactor_container_;
};

} // namespace application
