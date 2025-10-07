#include "reactor/view/graph.hpp"
#include "gfx/core/primitive_type.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "reactor/config.hpp"
#include "reactor/model/graph.hpp"

#include <ios>
#include <sstream>
#include <iomanip>

namespace reactor {
namespace view {

Graph::Graph( model::Graph&              model,
              const std::string&         title,
              const gfx::core::Vector2f& pos,
              const gfx::core::Vector2f& size )
    : Widget( pos, size ), model_( model )
{
    font_.loadFromFile( config::Reactor::GraphPanel::Common::Font::Name );

    title_text_.setFont( font_ );
    title_text_.setString( title );
    title_text_.setCharacterSize( config::Reactor::GraphPanel::Common::Font::Title::Size );
    title_text_.setFillColor( config::Reactor::GraphPanel::Common::Font::Color );

    axis_labels_text_.setFont( font_ );
    axis_labels_text_.setCharacterSize( config::Reactor::GraphPanel::Common::Font::Labels::Size );
    axis_labels_text_.setFillColor( config::Reactor::GraphPanel::Common::Font::Color );

    updateTitlePosition();
}

bool
Graph::onIdleSelf( const gfx::core::Event::IdleEvent& event )
{
    updateFromModel();

    return false;
}

void
Graph::updateFromModel()
{
    recalculateSteps();

    const auto& points      = model_.getPoints();
    size_t      points_size = points.size();

    plot_ = gfx::core::VertexArray( gfx::core::PrimitiveType::LineStrip, points.size() );

    for ( size_t i = 0; i < points_size; ++i )
    {
        plot_[i].position = { logicalToScreenX( points[i].x ), logicalToScreenY( points[i].y ) };
        plot_[i].color    = config::Reactor::GraphPanel::Common::Parameters::Color::Plot;
    }

    updateTitlePosition();
}

void
Graph::recalculateSteps()
{
    gfx::core::Vector2f range = model_.getMaxBounds() - model_.getMinBounds();

    if ( range.x == 0 )
    {
        range.x = 1.0f;
    }

    if ( range.y == 0 )
    {
        range.y = 1.0f;
    }

    step_ = size_ / range;
}

float
Graph::logicalToScreenX( float x ) const
{
    return ( x - model_.getMinBounds().x ) * step_.x;
}

float
Graph::logicalToScreenY( float y ) const
{
    return getSize().y - ( y - model_.getMinBounds().y ) * step_.y;
}

void
Graph::drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    drawGridLines( window, transform );
    drawAxisLabels( window, transform );

    window.draw( plot_, transform );
    window.draw( title_text_, transform );
}

void
Graph::drawGridLines( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    gfx::core::Vertex line[2];
    line[0].color = line[1].color = config::Reactor::GraphPanel::Common::Parameters::Color::Grid;

    gfx::core::Vector2f min_bounds = model_.getMinBounds();
    gfx::core::Vector2f max_bounds = model_.getMaxBounds();

    int divs = config::Reactor::GraphPanel::Common::Parameters::GridDivs;

    float x_min = 0;
    float x_max = x_min + getSize().x;
    float y_min = 0;
    float y_max = y_min + getSize().y;

    for ( int i = 0; i <= divs; ++i )
    {
        float t = static_cast<float>( i ) / divs;

        float y          = logicalToScreenY( min_bounds.y + t * ( max_bounds.y - min_bounds.y ) );
        line[0].position = { x_min, y };
        line[1].position = { x_max, y };
        window.draw( line, 2, gfx::core::Lines, transform );

        float x          = logicalToScreenX( min_bounds.x + t * ( max_bounds.x - min_bounds.x ) );
        line[0].position = { x, y_min };
        line[1].position = { x, y_max };
        window.draw( line, 2, gfx::core::Lines, transform );
    }
}

void
Graph::drawAxisLabels( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    auto min_bounds = model_.getMinBounds();
    auto max_bounds = model_.getMaxBounds();

    int divs = config::Reactor::GraphPanel::Common::Parameters::GridDivs;

    auto hor_pad = config::Reactor::GraphPanel::Common::Parameters::Labels::Padding::Horizontal;
    auto ver_pad = config::Reactor::GraphPanel::Common::Parameters::Labels::Padding::Vertical;

    for ( int i = 0; i <= divs; ++i )
    {
        float t     = static_cast<float>( i ) / divs;
        float val_x = min_bounds.x + t * ( max_bounds.x - min_bounds.x );
        float val_y = min_bounds.y + t * ( max_bounds.y - min_bounds.y );

        std::ostringstream oss;
        oss << std::setw( 2 ) << std::setprecision( 2 ) << std::scientific << val_y;
        axis_labels_text_.setString( oss.str() );
        axis_labels_text_.setPosition( -ver_pad.x, logicalToScreenY( val_y ) - ver_pad.y );
        window.draw( axis_labels_text_, transform );
    }
}

void
Graph::updateTitlePosition()
{
    auto bounds = title_text_.getGlobalBounds();
    title_text_.setPosition( getSize().x / 2.0f - bounds.w / 2.0f,
                             -config::Reactor::GraphPanel::Common::Parameters::Title::Padding::Y );
}

} // namespace view
} // namespace reactor
