#pragma once

#include "gfx/core/vector2.hpp"

#include <vector>

namespace reactor {
namespace model {

class Graph {
  public:
    explicit Graph() = default;

    void
    addPoint( double x, double y );
    void
    clear();

    const std::vector<gfx::core::Vector2f>&
    getPoints() const;

    gfx::core::Vector2f
    getMinBounds() const;
    gfx::core::Vector2f
    getMaxBounds() const;

  private:
    void
    updateBounds( double x, double y );

    std::vector<gfx::core::Vector2f> points_;

    gfx::core::Vector2f min_bounds_{ 0.0f, 0.0f };
    gfx::core::Vector2f max_bounds_{ 1.0f, 1.0f };
};

} // namespace model
} // namespace reactor
