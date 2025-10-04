#pragma once

#include "gui/widget.hpp"
#include "reactor/graph.hpp"
#include "config.hpp"
#include <cstdio>

namespace reactor {

class ReactorGraphs : public gui::Widget {
  public:
    ReactorGraphs( gfx_core::Vector2f pos, gfx_core::Vector2f size )
        : ReactorGraphs( pos.x, pos.y, size.x, size.y ) {};

    ReactorGraphs( float x, float y, float w, float h ) : gui::Widget( x, y, w, h )
    {
        AddChild( std::make_unique<EnergyGraph>(
            config::Reactor::Graphs::Specialization::Number::Position,
            config::Reactor::Graphs::Common::Parameters::Size,
            "Number" ) );
        AddChild( std::make_unique<NumberGraph>(
            config::Reactor::Graphs::Specialization::Energy::Position,
            config::Reactor::Graphs::Common::Parameters::Size,
            "Energy" ) );
    }

    float
    GetElapsedTime();

    float
    GetMoleculesAmount();

    float
    GetFullEnergy();
};

} // namespace reactor
