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
        containers_.emplace_back( Container<ReactorState>() );

        containers_[0].AddWidget(
            std::make_unique<Reactor>( Config::ReactorPos, Config::ReactorSize ) );
        containers_[0].AddWidget(
            std::make_unique<Graph>( Config::NumberPlotPos, Config::NumberPlotSize, "Number" ) );
        containers_[0].AddWidget(
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

        for ( auto& container : containers_ )
        {
            container.HandleEvents();
        }
    }

    void
    Update()
    {
        for ( auto& container : containers_ )
        {
            container.Update();
        }
    }

    void
    Draw()
    {
        window_.clear();

        for ( const auto& container : containers_ )
        {
            window_.draw( *widget );
        }

        window_.display();
    }

  private:
    sf::RenderWindow window_;

    std::vector<Container<ReactorState>> containers_;
};

} // namespace application
