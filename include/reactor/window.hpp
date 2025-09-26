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
            application::Config::AddMolButtonPos,
            application::Config::ButtonSize,
            "Add Molecule",
            [reactor_ptr]() { reactor_ptr->AddRandomCircleMolecule(); } ) );

        container->AddWidget(
            std::make_unique<gui::Button>( application::Config::RemoveMolButtonPos,
                                           application::Config::ButtonSize,
                                           "Remove Molecule",
                                           [reactor_ptr]() { reactor_ptr->RemoveMolecule(); } ) );

        container->AddWidget( std::make_unique<gui::Button>(
            application::Config::MovePistonRightButtonPos,
            application::Config::ButtonSize,
            "Move Pistol Left",
            [reactor_ptr]() {
                reactor_ptr->MovePiston( -application::Config::MovePistonDist );
            } ) );

        container->AddWidget( std::make_unique<gui::Button>(
            application::Config::MovePistonLeftButtonPos,
            application::Config::ButtonSize,
            "Move Pistol Right",
            [reactor_ptr]() { reactor_ptr->MovePiston( application::Config::MovePistonDist ); } ) );

        containers_.push_back( std::move( container ) );
    }
};

} // namespace reactor
