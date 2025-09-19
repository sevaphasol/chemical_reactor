#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

namespace application {

class Graph : public sf::Drawable {
  public:
    struct Config
    {
        sf::Color    grid_color = sf::Color( 100, 100, 100, 150 );
        sf::Color    axis_color = sf::Color::White;
        sf::Color    plot_color = sf::Color::Red;
        sf::Color    text_color = sf::Color::White;
        int          grid_divs  = 10;
        std::string  title      = "Graph";
        sf::Font     font;
        const char*  font_name = "assets/JetBrainsMono-Regular.ttf";
        unsigned int font_size = 12;
    };

    Graph( sf::Vector2f pos, sf::Vector2f size, const char* name )
        : pos_( pos ), size_( size ), config_( Config() ), origin_px_( pos + size / 2.0f ),
          data_bounds_{ 0, 0, 0, 0 }, needs_update_( true )
    {
        config_.title = name;

        if ( !config_.font.loadFromFile( config_.font_name ) )
        {
            sf::err() << "Graph: Font not set in config!" << std::endl;
        }

        RecalculateSteps();
        CreateTitleText();
    }

    void
    AddPoint( double x, double y )
    {
        raw_points_.emplace_back( x, y );
        UpdateDataBounds();
        needs_update_ = true;
    }

    void
    SetTitle( const std::string& title )
    {
        config_.title = title;
        CreateTitleText();
    }

  private:
    virtual void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        if ( needs_update_ )
        {
            UpdateVertexArray();
        }

        DrawGridAndAxes( target );
        if ( line_.getVertexCount() > 1 )
        {
            target.draw( line_, states );
        }
        DrawTitle( target );
        DrawAxisLabels( target );
    }

    void
    DrawGridAndAxes( sf::RenderTarget& target ) const
    {
        DrawGridLines( target, true );
        DrawGridLines( target, false );
    }

    void
    DrawGridLines( sf::RenderTarget& target, bool horizontal ) const
    {
        sf::Vertex line[2];
        line[0].color = config_.grid_color;
        line[1].color = config_.grid_color;

        int    divisions = config_.grid_divs;
        double min_val   = horizontal ? data_bounds_.min_y : data_bounds_.min_x;
        double max_val   = horizontal ? data_bounds_.max_y : data_bounds_.max_x;
        double range     = max_val - min_val;

        if ( range == 0 )
            return;

        for ( int i = 0; i <= divisions; ++i )
        {
            double logical_val = min_val + i * range / divisions;

            double screen_coord;
            if ( horizontal )
            {
                // Y-линия: фиксированный Y, рисуем горизонтальную линию
                screen_coord = LogicalToScreenY( logical_val );
                if ( screen_coord < pos_.y || screen_coord > pos_.y + size_.y )
                    continue;

                line[0].position = sf::Vector2f( pos_.x, screen_coord );
                line[1].position = sf::Vector2f( pos_.x + size_.x, screen_coord );
            } else
            {
                // X-линия: фиксированный X, рисуем вертикальную линию
                screen_coord = LogicalToScreenX( logical_val );
                if ( screen_coord < pos_.x || screen_coord > pos_.x + size_.x )
                    continue;

                line[0].position = sf::Vector2f( screen_coord, pos_.y );
                line[1].position = sf::Vector2f( screen_coord, pos_.y + size_.y );
            }

            target.draw( line, 2, sf::Lines );
        }
    }

    void
    DrawAxis( sf::RenderTarget& target, bool isXAxis ) const
    {
        sf::Vertex axis[2];
        axis[0].color = config_.axis_color;
        axis[1].color = config_.axis_color;

        if ( isXAxis )
        {
            // Горизонтальная ось: Y = 0
            double y0 = LogicalToScreenY( 0.0f );
            if ( y0 >= pos_.y && y0 <= pos_.y + size_.y )
            {
                axis[0].position = sf::Vector2f( pos_.x, y0 );
                axis[1].position = sf::Vector2f( pos_.x + size_.x, y0 );
                target.draw( axis, 2, sf::Lines );
            }
        } else
        {
            // Вертикальная ось: X = 0
            double x0 = LogicalToScreenX( 0.0f );
            if ( x0 >= pos_.x && x0 <= pos_.x + size_.x )
            {
                axis[0].position = sf::Vector2f( x0, pos_.y );
                axis[1].position = sf::Vector2f( x0, pos_.y + size_.y );
                target.draw( axis, 2, sf::Lines );
            }
        }
    }

    void
    DrawAxisLabels( sf::RenderTarget& target ) const
    {
        sf::Text label;
        label.setFont( config_.font );
        label.setCharacterSize( config_.font_size );
        label.setFillColor( config_.text_color );

        // Подписи по X
        // DrawLabelsForAxis( target, label, false );
        // Подписи по Y
        DrawLabelsForAxis( target, label, true );
    }

    void
    DrawLabelsForAxis( sf::RenderTarget& target, sf::Text& label, bool isYAxis ) const
    {
        int    divisions = config_.grid_divs;
        double min_val   = isYAxis ? data_bounds_.min_y : data_bounds_.min_x;
        double max_val   = isYAxis ? data_bounds_.max_y : data_bounds_.max_x;
        double range     = max_val - min_val;

        if ( range == 0 )
            return;

        for ( int i = 0; i <= divisions; ++i )
        {
            double logical_val = min_val + i * range / divisions;

            double screen_x, screen_y;
            if ( isYAxis )
            {
                screen_x = LogicalToScreenX( 0.0f ) - 40; // слева от оси Y
                screen_y = LogicalToScreenY( logical_val );
                if ( screen_y < pos_.y || screen_y > pos_.y + size_.y )
                    continue;
            } else
            {
                screen_x = LogicalToScreenX( logical_val );
                screen_y = LogicalToScreenY( 0.0f ) + 10; // под осью X
                if ( screen_x < pos_.x || screen_x > pos_.x + size_.x )
                    continue;
            }

            std::ostringstream oss;
            oss.precision( 2 );
            oss << std::fixed << logical_val;
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
                                 pos_.y - 30 );
        target.draw( title_text_ );
    }

    void
    CreateTitleText()
    {
        title_text_.setFont( config_.font );
        title_text_.setString( config_.title );
        title_text_.setCharacterSize( config_.font_size + 4 );
        title_text_.setFillColor( config_.text_color );
        title_text_.setStyle( sf::Text::Bold );
    }

    void
    UpdateDataBounds()
    {
        if ( raw_points_.empty() )
        {
            data_bounds_ = { 0, 1, 0, 1 }; // дефолт, чтобы не было деления на 0
            RecalculateSteps();
            return;
        }

        double min_x = raw_points_[0].x, max_x = raw_points_[0].x;
        double min_y = raw_points_[0].y, max_y = raw_points_[0].y;

        for ( const auto& p : raw_points_ )
        {
            min_x = std::min<double>( min_x, p.x );
            max_x = std::max<double>( max_x, p.x );
            min_y = std::min<double>( min_y, p.y );
            max_y = std::max<double>( max_y, p.y );
        }

        // Добавляем отступ 10%
        double padding_x = ( max_x - min_x ) * 0.1f;
        double padding_y = ( max_y - min_y ) * 0.1f;
        if ( padding_x == 0 )
            padding_x = 1.0f;
        if ( padding_y == 0 )
            padding_y = 1.0f;

        data_bounds_.min_x = min_x; // - padding_x;
        data_bounds_.max_x = max_x; // + padding_x;
        data_bounds_.min_y = min_y; // - padding_y;
        data_bounds_.max_y = max_y; // + padding_y;

        RecalculateSteps();
    }

    void
    RecalculateSteps()
    {
        double range_x = data_bounds_.max_x - data_bounds_.min_x;
        double range_y = data_bounds_.max_y - data_bounds_.min_y;

        if ( range_x == 0 )
            range_x = 1.0f;
        if ( range_y == 0 )
            range_y = 1.0f;

        step_.x = size_.x / range_x;
        step_.y = size_.y / range_y;

        // Пересчитываем origin_px_: он должен соответствовать логическому (0,0)
        origin_px_.x = pos_.x - data_bounds_.min_x * step_.x;
        origin_px_.y = pos_.y + size_.y + data_bounds_.min_y * step_.y;
    }

    void
    UpdateVertexArray() const
    {
        line_ = sf::VertexArray( sf::LineStrip, raw_points_.size() );

        for ( size_t i = 0; i < raw_points_.size(); ++i )
        {
            double screen_x = LogicalToScreenX( raw_points_[i].x );
            double screen_y = LogicalToScreenY( raw_points_[i].y );

            line_[i].position = sf::Vector2f( screen_x, screen_y );
            line_[i].color    = config_.plot_color;
        }

        needs_update_ = false;
    }

    // Вспомогательные методы преобразования координат
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
    struct DataBounds
    {
        double min_x, max_x, min_y, max_y;
    };

    sf::Vector2f pos_;
    sf::Vector2f size_;
    sf::Vector2f origin_px_; // экранные координаты логического (0,0)
    sf::Vector2f step_;      // пикселей на единицу данных

    DataBounds data_bounds_;
    Config     config_;

    mutable sf::VertexArray   line_;
    std::vector<sf::Vector2f> raw_points_;
    mutable bool              needs_update_;

    mutable sf::Text title_text_;

    // Запрещаем копирование
    Graph( const Graph& ) = delete;
    Graph&
    operator=( const Graph& ) = delete;
};

} // namespace application
