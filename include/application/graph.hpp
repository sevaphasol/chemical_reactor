#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "application/config.hpp"

namespace application {

class CoordSystem : public sf::Drawable {
  public:
    CoordSystem( sf::Vector2f pos, sf::Vector2f sizes )
        : pos_( pos ), sizes_( sizes ), center_( pos + sf::Vector2f( sizes.x / 2, sizes.y / 2 ) ),
          origin_( center_ ), step_x_( sizes.x / 20.0f ), step_y_( sizes.y / 20.0f ),
          points_( sf::LineStrip )
    {
    }

    void
    AddPoint( float x, float y )
    {
        raw_points_.emplace_back( x, y );

        float px = origin_.x + x * step_x_;
        float py = origin_.y - y * step_y_;

        if ( px < pos_.x || px > pos_.x + sizes_.x || py < pos_.y || py > pos_.y + sizes_.y )
        {
            step_x_ *= 0.5f;
            step_y_ *= 0.5f;
        }
    }

    void
    Clear()
    {
        raw_points_.clear();
        step_x_ = sizes_.x / 20.0f;
        step_y_ = sizes_.y / 20.0f;
    }

  private:
    virtual void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        DrawGridAndAxes( target );

        if ( raw_points_.empty() )
        {
            return;
        }

        sf::VertexArray line( sf::LineStrip, raw_points_.size() );
        for ( size_t i = 0; i < raw_points_.size(); ++i )
        {
            float x          = raw_points_[i].x;
            float y          = raw_points_[i].y;
            line[i].position = sf::Vector2f( origin_.x + x * step_x_, origin_.y - y * step_y_ );
            line[i].color    = plot_color_;
        }

        if ( raw_points_.size() > 1 )
        {
            target.draw( line );
        }
    }

    void
    DrawGridAndAxes( sf::RenderTarget& target ) const
    {
        sf::Vertex line[2];
        line[0].color = grid_color_;
        line[1].color = grid_color_;

        for ( int i = pos_.x; i <= pos_.x + sizes_.x; i += step_x_ )
        {
            float y          = origin_.y - ( ( i - pos_.x - sizes_.x / 2 ) / step_x_ ) * step_y_;
            line[0].position = sf::Vector2f( pos_.x, y );
            line[1].position = sf::Vector2f( pos_.x + sizes_.x, y );
            target.draw( line, 2, sf::Lines );
        }

        for ( int i = pos_.y; i <= pos_.y + sizes_.y; i += step_y_ )
        {
            float x          = origin_.x + ( ( i - pos_.y - sizes_.y / 2 ) / step_y_ ) * step_x_;
            line[0].position = sf::Vector2f( x, pos_.y );
            line[1].position = sf::Vector2f( x, pos_.y + sizes_.y );
            target.draw( line, 2, sf::Lines );
        }

        sf::Vertex axis[2];
        axis[0].color = axis_color_;
        axis[1].color = axis_color_;

        axis[0].position = sf::Vector2f( pos_.x, origin_.y );
        axis[1].position = sf::Vector2f( pos_.x + sizes_.x, origin_.y );
        target.draw( axis, 2, sf::Lines );

        axis[0].position = sf::Vector2f( origin_.x, pos_.y );
        axis[1].position = sf::Vector2f( origin_.x, pos_.y + sizes_.y );
        target.draw( axis, 2, sf::Lines );
    }

  private:
    sf::Vector2f pos_;
    sf::Vector2f sizes_;
    sf::Vector2f center_;
    sf::Vector2f origin_;

    sf::Color grid_color_ = sf::Color( 100, 100, 100, 150 );
    sf::Color axis_color_ = sf::Color::White;
    sf::Color plot_color_ = sf::Color::Red;

    float step_x_;
    float step_y_;

    sf::VertexArray           points_;
    std::vector<sf::Vector2f> raw_points_;
};

} // namespace application
