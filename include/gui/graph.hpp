#pragma once

#include "gfx_core/font.hpp"
#include "gfx_core/primitive_type.hpp"
#include "gfx_core/rectangle_shape.hpp"
#include "gfx_core/text.hpp"
#include "gfx_core/transform.hpp"
#include "gfx_core/vector2.hpp"
#include "gfx_core/vertex_array.hpp"
#include "gfx_core/window.hpp"
#include "gui/draggable.hpp"
#include "gui/widget.hpp"
#include "gfx_core/vertex.hpp"
#include <algorithm>
#include <cassert>
#include <config.hpp>
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace gui {

class Graph : public gui::Widget, public ::gui::Draggable<Graph> {
  public:
    Graph( gfx_core::Vector2f pos, gfx_core::Vector2f size, const std::string& title )
        : gui::Widget( pos, size ), title_( title ), min_bounds_( 0, 0 ), max_bounds_( 1, 1 )
    {
        bool r = font_.loadFromFile( config::Reactor::Graphs::Common::Font::Name );
        // // std::cerr << r << std::endl;

        // // std::cerr << "Setting title_text_ font" << std::endl;
        title_text_.setFont( font_ );
        title_text_.setString( title_ );
        title_text_.setCharacterSize( config::Reactor::Graphs::Common::Font::Title::Size );
        title_text_.setFillColor( config::Reactor::Graphs::Common::Font::Color );

        // // std::cerr << "Setting axis_labels_text_ font" << std::endl;
        axis_labels_text_.setFont( font_ );
        axis_labels_text_.setCharacterSize( config::Reactor::Graphs::Common::Font::Labels::Size );
        axis_labels_text_.setFillColor( config::Reactor::Graphs::Common::Font::Color );

        RecalculateSteps();
    }

    virtual void
    HandleEvents( const gfx_core::Event& event ) override
    {
        HandleDragEvent( event );
    };

    void
    UpdateGraphRoutine()
    {
        UpdateVertexArray();
        UpdateTitle();
    }

    void
    AddPoint( double x, double y )
    {
        raw_points_.emplace_back( gfx_core::Vector2f( x, y ) );

        UpdateDataBounds( x, y );
    }

  private:
    virtual void
    DrawSelf( gfx_core::Window& window, gfx_core::Transform transform ) const override
    {
        // // std::cerr << "DrawSelf() from " << typeid( *this ).name() << std::endl;

        DrawGridLines( window, transform );
        DrawAxisLabels( window, transform );
        window.draw( plot_, transform );
        window.draw( title_text_, transform );
    }

    void
    RecalculateSteps()
    {
        double range_x = max_bounds_.x - min_bounds_.x;
        double range_y = max_bounds_.y - min_bounds_.y;

        if ( range_x == 0 )
        {
            range_x = 1.0f;
        }

        if ( range_y == 0 )
        {
            range_y = 1.0f;
        }

        gfx_core::Vector2f size = GetSize();

        step_.x = size.x / range_x;
        step_.y = size.y / range_y;
    }

    void
    DrawGridLines( gfx_core::Window& window, gfx_core::Transform transform ) const
    {
        DrawGridLines( window, transform, true );
        DrawGridLines( window, transform, false );
    }

    void
    DrawGridLines( gfx_core::Window& window, gfx_core::Transform transform, bool horizontal ) const
    {
        gfx_core::Vertex line[2];
        line[0].color = config::Reactor::Graphs::Common::Parameters::Color::Grid;
        line[1].color = config::Reactor::Graphs::Common::Parameters::Color::Grid;

        double min_val = horizontal ? min_bounds_.y : min_bounds_.x;
        double max_val = horizontal ? max_bounds_.y : max_bounds_.x;
        double range   = max_val - min_val;

        for ( int i = 0; i <= config::Reactor::Graphs::Common::Parameters::GridDivs; i++ )
        {
            double logical_val =
                min_val + i * range / config::Reactor::Graphs::Common::Parameters::GridDivs;
            double screen_coord = 0;

            if ( horizontal )
            {
                screen_coord = LogicalToScreenY( logical_val );

                line[0].position = gfx_core::Vector2f( GetPos().x, screen_coord );
                line[1].position = gfx_core::Vector2f( GetPos().x + GetSize().x, screen_coord );
            } else
            {
                screen_coord = LogicalToScreenX( logical_val );

                line[0].position = gfx_core::Vector2f( screen_coord, GetPos().y );
                line[1].position = gfx_core::Vector2f( screen_coord, GetPos().y + GetSize().y );
            }

            window.draw( line, 2, gfx_core::Lines, transform );
        }
    }

    void
    DrawAxisLabels( gfx_core::Window& window, gfx_core::Transform transform ) const
    {
        DrawLabelsForAxis( window, transform, false );
    }

    void
    DrawLabelsForAxis( gfx_core::Window& target, gfx_core::Transform transform, bool x_axis ) const
    {
        double min_val = x_axis ? min_bounds_.x : min_bounds_.y;
        double max_val = x_axis ? max_bounds_.x : max_bounds_.y;
        double range   = max_val - min_val;

        for ( int i = 0; i <= config::Reactor::Graphs::Common::Parameters::GridDivs; i++ )
        {
            double logical_val =
                min_val + i * range / config::Reactor::Graphs::Common::Parameters::GridDivs;

            double screen_x = 0;
            double screen_y = 0;
            if ( x_axis )
            {
                screen_x = LogicalToScreenX( logical_val ) -
                           config::Reactor::Graphs::Common::Parameters::Parameters::Labels::
                               Padding::Horizontal::X;
                screen_y = LogicalToScreenY( 0.0f ) -
                           config::Reactor::Graphs::Common::Parameters::Parameters::Labels::
                               Padding::Horizontal::Y;

            } else
            {
                screen_x = LogicalToScreenX( 0.0f ) - config::Reactor::Graphs::Common::Parameters::
                                                          Parameters::Labels::Padding::Vertical::X;
                screen_y = LogicalToScreenY( logical_val ) -
                           config::Reactor::Graphs::Common::Parameters::Parameters::Labels::
                               Padding::Vertical::Y;
            }

            std::ostringstream oss;
            oss << std::setprecision( 2 ) << std::scientific << logical_val;
            axis_labels_text_.setString( oss.str() );
            axis_labels_text_.setPosition( screen_x, screen_y );
            target.draw( axis_labels_text_, transform );
        }
    }

    void
    UpdateTitle()
    {
        gfx_core::Vector2f pos  = GetPos();
        gfx_core::Vector2f size = GetSize();

        title_text_.setPosition(
            pos.x + size.x / 2.0f - title_text_.getGlobalBounds().w / 2.0f,
            pos.y - config::Reactor::Graphs::Common::Parameters::Title::Padding::Y );
    }

    void
    UpdateDataBounds( double x, double y )
    {
        size_t n_points = raw_points_.size();

        min_bounds_.x = ( n_points == 1 ) ? x : std::min<double>( x, min_bounds_.x );
        max_bounds_.x = ( n_points == 1 ) ? x : std::max<double>( x, max_bounds_.x );
        min_bounds_.y = ( n_points == 1 ) ? y : std::min<double>( y, min_bounds_.y );
        max_bounds_.y = ( n_points == 1 ) ? y : std::max<double>( y, max_bounds_.y );

        RecalculateSteps();
    }

    void
    UpdateVertexArray()
    {
        plot_ = gfx_core::VertexArray( gfx_core::LineStrip, raw_points_.size() );

        for ( size_t i = 0; i < raw_points_.size(); i++ )
        {
            double screen_x = LogicalToScreenX( raw_points_[i].x );
            double screen_y = LogicalToScreenY( raw_points_[i].y );

            // // std::cerr << "screen_x = " << screen_x << std::endl;
            // // std::cerr << "screen_y = " << screen_y << std::endl;

            plot_[i].position = gfx_core::Vector2f( screen_x, screen_y );
            plot_[i].color    = config::Reactor::Graphs::Common::Parameters::Color::Plot;
        }
    }

    double
    LogicalToScreenX( double x ) const
    {
        return GetPos().x + ( x - min_bounds_.x ) * step_.x;
    }

    double
    LogicalToScreenY( double y ) const
    {
        return GetPos().y + GetSize().y - ( y - min_bounds_.y ) * step_.y;
    }

  private:
    std::string            title_;
    gfx_core::Font         font_;
    gfx_core::Text         title_text_;
    mutable gfx_core::Text axis_labels_text_;

    gfx_core::Vector2f step_{ 0, 0 };

    gfx_core::Vector2f min_bounds_{ 0, 0 };
    gfx_core::Vector2f max_bounds_{ 0, 0 };

    gfx_core::VertexArray           plot_;
    std::vector<gfx_core::Vector2f> raw_points_;
};

} // namespace gui
