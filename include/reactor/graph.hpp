#pragma once

#include "gui/graph.hpp"
#include <string>

namespace reactor {

class EnergyGraph : public gui::Graph {
  public:
    EnergyGraph( gfx_core::Vector2f pos, gfx_core::Vector2f size, const std::string& name )
        : Graph( pos, size, name ) {};

    virtual void
    Update() override;
};

class NumberGraph : public gui::Graph {
  public:
    NumberGraph( gfx_core::Vector2f pos, gfx_core::Vector2f size, const std::string& name )
        : Graph( pos, size, name ) {};

    virtual void
    Update() override;
};

} // namespace reactor
