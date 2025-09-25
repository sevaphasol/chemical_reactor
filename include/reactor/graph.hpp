#pragma once

#include "gui/container_state.hpp"
#include "gui/widget.hpp"
#include "reactor/reactor.hpp"
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <config.hpp>

namespace reactor {

class ReactorGraph : public gui::Widget {
  public:
    ReactorGraph( sf::Vector2f pos, sf::Vector2f size, const char* name )
        : gui::Widget( pos, size ), data_bounds_{ 0, 1, 0, 1 }
    {
        title_ = name;

        if ( !font_.loadFromFile( application::Config::FontName ) )
        {
            std::cerr << "Font has not been loaded" << std::endl;
        }

        RecalculateSteps();
        CreateTitleText();
    }

    void
    AddPoint( double x, double y )
    {
        raw_points_.emplace_back( x, y );

        UpdateDataBounds( x, y );
    }

    void
    CreateTitleText()
    {
        title_text_.setFont( font_ );
        title_text_.setString( title_ );
        title_text_.setCharacterSize( application::Config::TitleFontSize );
        title_text_.setFillColor( application::Config::TextColor );
    }

    virtual void
    HandleEvents( gui::ContainerState& state ) override {};

    virtual void
    Update( gui::ContainerState& state ) override
    {
        ReactorState& reactor_state = dynamic_cast<ReactorState&>( state );

        AddPoint( reactor_state.elapsed_time, reactor_state.n_molecules );
    }

  private:
    virtual void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        UpdateVertexArray();

        DrawGridLines( target );
        target.draw( plot_, states );
        DrawTitle( target );
        DrawAxisLabels( target );
    }

    void
    RecalculateSteps()
    {
        double range_x = data_bounds_.max_x - data_bounds_.min_x;
        double range_y = data_bounds_.max_y - data_bounds_.min_y;

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
        line[0].color = application::Config::GridColor;
        line[1].color = application::Config::GridColor;

        double min_val = horizontal ? data_bounds_.min_y : data_bounds_.min_x;
        double max_val = horizontal ? data_bounds_.max_y : data_bounds_.max_x;
        double range   = max_val - min_val;

        for ( int i = 0; i <= application::Config::GridDivs; i++ )
        {
            double logical_val  = min_val + i * range / application::Config::GridDivs;
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
        sf::Text label;
        label.setFont( font_ );
        label.setCharacterSize( application::Config::LabelsFontSize );
        label.setFillColor( application::Config::TextColor );

        DrawLabelsForAxis( target, label, false );
    }

    void
    DrawLabelsForAxis( sf::RenderTarget& target, sf::Text& label, bool x_axis ) const
    {
        double min_val = x_axis ? data_bounds_.min_x : data_bounds_.min_y;
        double max_val = x_axis ? data_bounds_.max_x : data_bounds_.max_y;
        double range   = max_val - min_val;

        for ( int i = 0; i <= application::Config::GridDivs; i++ )
        {
            double logical_val = min_val + i * range / application::Config::GridDivs;

            double screen_x = 0;
            double screen_y = 0;
            if ( x_axis )
            {
                screen_x = LogicalToScreenX( logical_val ) - application::Config::HorLabelsXPadding;
                screen_y = LogicalToScreenY( 0.0f ) - application::Config::HorLabelsYPadding;

            } else
            {
                screen_x = LogicalToScreenX( 0.0f ) - application::Config::VerLabelsXPadding;
                screen_y = LogicalToScreenY( logical_val ) - application::Config::VerLabelsYPadding;
            }

            std::ostringstream oss;
            oss << std::setprecision( 2 ) << std::scientific << logical_val;
            label.setString( oss.str() );
            label.setPosition( screen_x, screen_y );
            target.draw( label );
        }
    }

    void
    DrawTitle( sf::RenderTarget& target ) const
    {
        title_text_.setPosition( pos_.x + size_.x / 2.0f -
                                     title_text_.getGlobalBounds().width / 2.0f,
                                 pos_.y - application::Config::TitleYPadding );
        target.draw( title_text_ );
    }

    void
    UpdateDataBounds( double x, double y )
    {
        size_t n_points = raw_points_.size();

        double min_x = n_points == 1 ? x : std::min<double>( x, data_bounds_.min_x );
        double max_x = n_points == 1 ? x : std::max<double>( x, data_bounds_.max_x );
        double min_y = n_points == 1 ? y : std::min<double>( y, data_bounds_.min_y );
        double max_y = n_points == 1 ? y : std::max<double>( y, data_bounds_.max_y );

        data_bounds_ = { min_x, max_x, min_y, max_y };

        RecalculateSteps();
    }

    void
    UpdateVertexArray() const
    {
        plot_ = sf::VertexArray( sf::LineStrip, raw_points_.size() );

        for ( size_t i = 0; i < raw_points_.size(); i++ )
        {
            double screen_x = LogicalToScreenX( raw_points_[i].x );
            double screen_y = LogicalToScreenY( raw_points_[i].y );

            plot_[i].position = sf::Vector2f( screen_x, screen_y );
            plot_[i].color    = application::Config::PlotColor;
        }
    }

    double
    LogicalToScreenX( double x ) const
    {
        return pos_.x + ( x - data_bounds_.min_x ) * step_.x;
    }

    double
    LogicalToScreenY( double y ) const
    {
        return pos_.y + size_.y - ( y - data_bounds_.min_y ) * step_.y;
    }

  private:
    sf::Font         font_;
    std::string      title_;
    mutable sf::Text title_text_;

    sf::Vector2f step_;

    struct
    {
        double min_x, max_x, min_y, max_y;
    } data_bounds_;

    mutable sf::VertexArray   plot_;
    std::vector<sf::Vector2f> raw_points_;
};

} // namespace reactor
