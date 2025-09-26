#pragma once

#include "config.hpp"
#include "gui/button.hpp"
#include "gui/window_manager.hpp"
#include "reactor/graph.hpp"
#include "reactor/reactor.hpp"
#include <memory>

void
foo()
{
    std::cerr << "TestButton" << std::endl;
}

namespace reactor {

class ReactorWindow : public gui::WindowManager {
  public:
    ReactorWindow()
    {
        auto container =
            std::make_unique<gui::Container>( std::make_unique<reactor::ReactorState>() );

        auto reactor = std::make_unique<Reactor>( application::Config::ReactorPos,
                                                  application::Config::ReactorSize );

        auto* reactor_ptr = reactor.get();

        container->AddWidget( std::move( reactor ) );
        container->AddWidget( std::make_unique<EnergyGraph>( application::Config::NumberPlotPos,
                                                             application::Config::NumberPlotSize,
                                                             "Number" ) );
        container->AddWidget( std::make_unique<NumberGraph>( application::Config::EnergyPlotPos,
                                                             application::Config::EnergyPlotSize,
                                                             "Energy" ) );

        container->AddWidget( std::make_unique<gui::Button>(
            application::Config::ButtonPos,
            application::Config::ButtonSize,
            "TestButton",
            [reactor_ptr]() {
                reactor_ptr->AddCircleMolecule(
                    application::Config::CircleMoleculeRadius,
                    application::Config::ReactorSize.x * rand() / RAND_MAX,
                    application::Config::ReactorSize.y * rand() / RAND_MAX,
                    application::Config::StartVelocityMax * rand() / RAND_MAX,
                    application::Config::StartVelocityMax * rand() / RAND_MAX );
            } ) );

        containers_.push_back( std::move( container ) );
    }
};

} // namespace reactor
