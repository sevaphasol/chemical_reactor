#include "reactor/model/graph.hpp"

#include <algorithm>

namespace reactor {
namespace model {

const std::vector<gfx::core::Vector2f>&
Graph::getPoints() const
{
    return points_;
}

gfx::core::Vector2f
Graph::getMinBounds() const
{
    return min_bounds_;
}

gfx::core::Vector2f
Graph::getMaxBounds() const
{
    return max_bounds_;
}

void
Graph::addPoint( double x, double y )
{
    points_.emplace_back( static_cast<float>( x ), static_cast<float>( y ) );
    updateBounds( x, y );
}

void
Graph::clear()
{
    points_.clear();
    min_bounds_ = { 0, 0 };
    max_bounds_ = { 1, 1 };
}

void
Graph::updateBounds( double x, double y )
{
    if ( points_.size() == 1 )
    {
        min_bounds_ = max_bounds_ = gfx::core::Vector2f( x, y );
    } else
    {
        min_bounds_.x = std::min( min_bounds_.x, static_cast<float>( x ) );
        max_bounds_.x = std::max( max_bounds_.x, static_cast<float>( x ) );
        min_bounds_.y = std::min( min_bounds_.y, static_cast<float>( y ) );
        max_bounds_.y = std::max( max_bounds_.y, static_cast<float>( y ) );
    }
}

} // namespace model
} // namespace reactor
