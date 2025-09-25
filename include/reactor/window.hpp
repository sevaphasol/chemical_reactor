#pragma once

#include "gui/window_manager.hpp"
#include "reactor/reactor.hpp"
#include <memory>

namespace reactor {

class ReactorWindow : public gui::WindowManager {
  public:
    ReactorWindow()
    {
        auto container = std::make_unique<gui::Container>();

        container->AddWidget( std::make_unique<Reactor>( application::Config::ReactorPos,
                                                         application::Config::ReactorSize ) );
        container->AddWidget( std::make_unique<ReactorGraph>( application::Config::NumberPlotPos,
                                                              application::Config::NumberPlotSize,
                                                              "Number" ) );
        container->AddWidget( std::make_unique<ReactorGraph>( application::Config::EnergyPlotPos,
                                                              application::Config::EnergyPlotSize,
                                                              "Energy" ) );

        container->SetState( std::make_unique<reactor::ReactorState>() );

        containers_.push_back( std::move( container ) );
    }
};

} // namespace reactor
