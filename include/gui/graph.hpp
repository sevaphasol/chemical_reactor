#pragma once

#include "gui/draggable.hpp"
#include "gui/widget.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <config.hpp>

namespace gui {

class Graph : public gui::Widget, public ::gui::Draggable<Graph> {
  public:
    Graph( sf::Vector2f pos, sf::Vector2f size, const std::string& title )
        : gui::Widget( pos, size ), title_( title ), min_bounds_( 0, 0 ), max_bounds_( 1, 1 )
    {
        font_.loadFromFile( config::Reactor::Graphs::Common::Font::Name );

        title_text_.setFont( font_ );
        title_text_.setString( title_ );
        title_text_.setCharacterSize( config::Reactor::Graphs::Common::Font::Title::Size );
        title_text_.setFillColor( config::Reactor::Graphs::Common::Font::Color );

        axis_labels_text_.setFont( font_ );
        axis_labels_text_.setCharacterSize( config::Reactor::Graphs::Common::Font::Labels::Size );
        axis_labels_text_.setFillColor( config::Reactor::Graphs::Common::Font::Color );

        RecalculateSteps();
    }

    virtual void
    HandleEvents( const sf::Event& event ) override
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
        raw_points_.emplace_back( sf::Vector2f( x, y ) );

        UpdateDataBounds( x, y );
    }

  private:
    virtual void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        DrawGridLines( target );
        DrawAxisLabels( target );
        target.draw( plot_, states );
        target.draw( title_text_, states );
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

        step_.x = size_.x / range_x;
        step_.y = size_.y / range_y;
    }

    void
    DrawGridLines( sf::RenderTarget& target ) const
    {
        DrawGridLines( target, true );
        DrawGridLines( target, false );
    }

    void
    DrawGridLines( sf::RenderTarget& target, bool horizontal ) const
    {
        sf::Vertex line[2];
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

                line[0].position = sf::Vector2f( pos_.x, screen_coord );
                line[1].position = sf::Vector2f( pos_.x + size_.x, screen_coord );
            } else
            {
                screen_coord = LogicalToScreenX( logical_val );

                line[0].position = sf::Vector2f( screen_coord, pos_.y );
                line[1].position = sf::Vector2f( screen_coord, pos_.y + size_.y );
            }

            target.draw( line, 2, sf::Lines );
        }
    }

    void
    DrawAxisLabels( sf::RenderTarget& target ) const
    {
        DrawLabelsForAxis( target, false );
    }

    void
    DrawLabelsForAxis( sf::RenderTarget& target, bool x_axis ) const
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
            target.draw( axis_labels_text_ );
        }
    }

    void
    UpdateTitle()
    {
        title_text_.setPosition(
            pos_.x + size_.x / 2.0f - title_text_.getGlobalBounds().width / 2.0f,
            pos_.y - config::Reactor::Graphs::Common::Parameters::Title::Padding::Y );
    }

    void
    UpdateDataBounds( double x, double y )
    {
        size_t n_points = raw_points_.size();

        min_bounds_.x = n_points == 1 ? x : std::min<double>( x, min_bounds_.x );
        max_bounds_.x = n_points == 1 ? x : std::max<double>( x, max_bounds_.x );
        min_bounds_.y = n_points == 1 ? y : std::min<double>( y, min_bounds_.y );
        max_bounds_.y = n_points == 1 ? y : std::max<double>( y, max_bounds_.y );

        RecalculateSteps();
    }

    void
    UpdateVertexArray()
    {
        plot_ = sf::VertexArray( sf::LineStrip, raw_points_.size() );

        for ( size_t i = 0; i < raw_points_.size(); i++ )
        {
            double screen_x = LogicalToScreenX( raw_points_[i].x );
            double screen_y = LogicalToScreenY( raw_points_[i].y );

            plot_[i].position = sf::Vector2f( screen_x, screen_y );
            plot_[i].color    = config::Reactor::Graphs::Common::Parameters::Color::Plot;
        }
    }

    double
    LogicalToScreenX( double x ) const
    {
        return pos_.x + ( x - min_bounds_.x ) * step_.x;
    }

    double
    LogicalToScreenY( double y ) const
    {
        return pos_.y + size_.y - ( y - min_bounds_.y ) * step_.y;
    }

  private:
    std::string      title_;
    sf::Font         font_;
    sf::Text         title_text_;
    mutable sf::Text axis_labels_text_;

    sf::Vector2f step_;

    sf::Vector2f min_bounds_;
    sf::Vector2f max_bounds_;

    sf::VertexArray           plot_;
    std::vector<sf::Vector2f> raw_points_;
};

} // namespace gui
