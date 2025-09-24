#pragma once

#include "application/molecule.hpp"
#include "application/molecule_types.hpp"
#include "application/widget.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cmath>
#include <memory>
#include <random>
#include <vector>

namespace application {

class Reactor : public Widget {
    using CollideFuncT = void ( Reactor::* )( Molecule& mol1, Molecule& mol2 );

  public:
    Reactor( const sf::Vector2f& pos, const sf::Vector2f& sizes ) : pos_( pos ), sizes_( sizes )
    {
        vtable_[Molecule::CIRCLE][Molecule::CIRCLE] = &Reactor::CollideCircle;
        vtable_[Molecule::CIRCLE][Molecule::SQUARE] = &Reactor::CollideCircle;
        vtable_[Molecule::SQUARE][Molecule::CIRCLE] = &Reactor::CollideCircle;
        vtable_[Molecule::SQUARE][Molecule::SQUARE] = &Reactor::CollideSquareSquare;

        border_.setSize( sizes );
        border_.setFillColor( sf::Color::Transparent );
        border_.setOutlineColor( sf::Color::Red );
        border_.setOutlineThickness( 2.0f );
    }

  private:
    virtual void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        target.draw( border_ );

        for ( const auto& molecule : molecules_ )
        {
            target.draw( *molecule.ptr );
        }
    }

  public:
    virtual void
    Render( float elapsed_time ) override
    {
        std::cerr << "Render reactor" << std::endl;

        Clear();
        HandleMoleculesCollisions();
        HandleWallCollisions();
        PostRendering( elapsed_time );
        HandleWallCollisions();
    }

    virtual void
    HandleEvents() override
    {
        std::cerr << "Handle events" << std::endl;

        int left  = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) );
        int right = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) );

        MovePiston( ( right - left ) * 10 );
    }

    void
    MovePiston( float dist )
    {
        std::cerr

            float x = sizes_.x + dist;

        if ( Config::ReactorPos.x < x && x < Config::ReactorPos.x + Config::ReactorSize.x )
        {
            sizes_.x += dist;
            border_.setSize( sizes_ );
        }
    }

    void
    HandleWallCollisions()
    {
        for ( auto& mol : molecules_ )
        {
            float r  = mol.ptr->GetR();
            float x  = mol.ptr->GetX();
            float y  = mol.ptr->GetY();
            float vx = mol.ptr->GetVx();
            float vy = mol.ptr->GetVy();

            float width  = sizes_.x;
            float height = sizes_.y;

            if ( x + 2 * r > width )
            {
                mol.ptr->SetVx( -vx );
                mol.ptr->SetX( width - 2 * r );
            }

            if ( x < 0 )
            {
                mol.ptr->SetVx( -vx );
                mol.ptr->SetX( 0 );
            }

            if ( y + 2 * r > height )
            {
                mol.ptr->SetVy( -vy );
                mol.ptr->SetY( height - 2 * r );
            }

            if ( y < 0 )
            {
                mol.ptr->SetVy( -vy );
                mol.ptr->SetY( 0 );
            }
        }
    }

    void
    HandleMoleculesCollisions()
    {
        size_t n_molecules = molecules_.size();

        for ( size_t i = 0; i < n_molecules - 1; ++i )
        {
            for ( size_t j = i + 1; j < n_molecules; ++j )
            {
                Molecule& mol1 = *molecules_[i].ptr;
                Molecule& mol2 = *molecules_[j].ptr;

                if ( Molecule::CheckCollision( mol1, mol2 ) )
                {
                    Collide( i, j );

                    break;
                }
            }
        }
    }

    size_t
    GetMoleculesCount() const
    {
        return molecules_.size();
    }

    float
    CalcSumEnergy() const
    {
        float energy = 0;

        for ( const auto& molecule : molecules_ )
        {
            float m  = molecule.ptr->GetWeight();
            float vx = molecule.ptr->GetVx();
            float vy = molecule.ptr->GetVy();

            energy += m * ( vx * vx + vy * vy ) / 2;
        }

        return energy;
    }

    void
    AddCircleMolecule( float r, float x, float y, float vx, float vy )
    {
        molecules_.emplace_back( std::make_unique<CircleMolecule>(
            CircleMolecule( r, x, y, vx, vy, Config::CircleMoleculeWeight ) ) );
    }

    void
    AddSquareMolecule( float r, float x, float y, float vx, float vy )
    {
        molecules_.emplace_back( std::make_unique<SquareMolecule>(
            SquareMolecule( r, x, y, vx, vy, Config::SquareMoleculeWeight ) ) );
    }

    void
    Clear()
    {
        remove_indexes_.clear();
        new_molecules_.clear();
    }

    void
    PostRendering( float elapsed_time )
    {
        //         std::sort( remove_indexes_.begin(), remove_indexes_.end(), []( size_t a, size_t b
        //         ) {
        //             return a > b;
        //         } );
        //
        //         for ( const auto& req : remove_indexes_ )
        //         {
        //             if ( req < molecules_.size() )
        //             {
        //                 molecules_.erase( molecules_.begin() + req );
        //             }
        //         }

        //         int j = 0;
        //
        //         for ( int i = 0; i < molecules_.size(); i++ )
        //         {
        //             if ( molecules_[i].need_remove )
        //             {
        //                 if ( j < new_molecules_.size() )
        //                 {
        //                     molecules_[i] = std::move( new_molecules_[j] );
        //                 }
        //                 i--;
        //             }
        //         }
        //
        //         for ( auto& req : new_molecules_ )
        //         {
        //             molecules_.push_back( std::move( req ) );
        //         }
        //
        //         for ( auto& mol : molecules_ )
        //         {
        //             mol.ptr->Move( elapsed_time );
        //         }
        size_t new_idx = 0;

        for ( size_t i = 0; i < molecules_.size(); i++ )
        {
            if ( molecules_[i].need_remove )
            {
                if ( new_idx < new_molecules_.size() )
                {
                    molecules_[i] = std::move( new_molecules_[new_idx] );
                    new_idx++;
                } else
                {
                    molecules_.erase( molecules_.begin() + i );
                }
            }
        }

        for ( size_t idx = new_idx; idx < new_molecules_.size(); ++idx )
        {
            molecules_.push_back( std::move( new_molecules_[idx] ) );
        }

        for ( auto& mol : molecules_ )
        {
            mol.ptr->Move( elapsed_time );
        }
    }

  private:
    static float
    GetRandomAngle()
    {
        static std::random_device                    Rd;
        static std::mt19937                          Gen( Rd() );
        static std::uniform_real_distribution<float> Dis( 0.0, 2.0 * M_PI );

        return Dis( Gen );
    }

    void
    Collide( size_t mol1_idx, size_t mol2_idx )
    {
        // remove_indexes_.push_back( mol1_idx );
        // remove_indexes_.push_back( mol2_idx );
        MoleculeInfo& mol1 = molecules_[mol1_idx];
        MoleculeInfo& mol2 = molecules_[mol2_idx];

        mol1.need_remove = true;
        mol2.need_remove = true;

        ( this->*vtable_[mol1.ptr->GetType()][mol2.ptr->GetType()] )( *mol1.ptr, *mol2.ptr );
    }

    void
    CollideCircle( Molecule& mol1, Molecule& mol2 )
    {
        //         float r   = ( mol1.GetR() + mol2.GetR() ) / 2.0f;
        //         float x   = ( mol1.GetX() + mol2.GetX() ) / 2.0f;
        //         float y   = ( mol1.GetY() + mol2.GetY() ) / 2.0f;
        //         float m1  = mol1.GetWeight();
        //         float m2  = mol2.GetWeight();
        //         float v1x = mol1.GetVx();
        //         float v2x = mol2.GetVx();
        //         float v1y = mol1.GetVy();
        //         float v2y = mol2.GetVy();
        //
        //         float p1x = m1 * v1x;
        //         float p2x = m2 * v2x;
        //         float p1y = m1 * v1y;
        //         float p2y = m2 * v2y;
        //
        //         float px   = p1x + p2x;
        //         float py   = p1y + p2y;
        //         float p_sq = px * px + py * py;
        //
        //         constexpr float c_sq = Config::SpeedVelocitySq;
        //
        //         float energy    = mol1.GetFullEnergy() + mol2.GetFullEnergy();
        //         float energy_sq = energy * energy;
        //
        //         float m =
        //             ( 2 * energy + sqrt( 4 * energy_sq - 8 * p_sq * c_sq / energy_sq ) ) / ( 4 *
        //             c_sq );
        //
        //         float vx = px / m;
        //         float vy = py / m;
        //
        //         new_molecules_.push_back( { std::make_unique<SquareMolecule>( r, x, y, vx, vy, m
        //         ) } );

        float r          = ( mol1.GetR() + mol2.GetR() ) / 2.0f;
        float x          = ( mol1.GetX() + mol2.GetX() ) / 2.0f;
        float y          = ( mol1.GetY() + mol2.GetY() ) / 2.0f;
        float m          = mol1.GetWeight() + mol2.GetWeight();
        float energy     = mol1.GetEnergy() + mol2.GetEnergy();
        float disp_angle = GetRandomAngle();
        float v          = sqrt( 2 * energy / m );
        float vx         = v * std::cos( disp_angle );
        float vy         = v * std::sin( disp_angle );

        new_molecules_.push_back( { std::make_unique<SquareMolecule>( r, x, y, vx, vy, m ) } );
    }

    void
    CollideSquareSquare( Molecule& mol1, Molecule& mol2 )
    {
        float r             = ( mol1.GetR() + mol2.GetR() ) / 2.0f;
        float x             = ( mol1.GetX() + mol2.GetX() ) / 2.0f;
        float y             = ( mol1.GetY() + mol2.GetY() ) / 2.0f;
        float total_circles = mol1.GetWeight() + mol2.GetWeight();
        float energy        = mol1.GetEnergy() + mol2.GetEnergy();
        float disp_distance = 2 * Config::CircleMoleculeRadius / std::sin( M_PI / total_circles );

        float circle_energy = energy / total_circles;
        float v_circle      = sqrt( 2 * circle_energy / Config::CircleMoleculeWeight );

        for ( int i = 0; i < total_circles; i++ )
        {
            float offset_angle   = 2.0f * M_PI * i / total_circles;
            float cos_disp_angle = std::cos( offset_angle );
            float sin_disp_angle = std::sin( offset_angle );

            float spawn_x = x + disp_distance * cos_disp_angle;
            float spawn_y = y + disp_distance * sin_disp_angle;

            new_molecules_.push_back(
                { std::make_unique<CircleMolecule>( Config::CircleMoleculeRadius,
                                                    spawn_x,
                                                    spawn_y,
                                                    v_circle * cos_disp_angle,
                                                    v_circle * sin_disp_angle,
                                                    Config::CircleMoleculeWeight ) } );
        }
    }

  private:
    std::array<std::array<CollideFuncT, Molecule::N_TYPES>, Molecule::N_TYPES> vtable_;

    struct MoleculeInfo
    {
        MoleculeInfo( std::unique_ptr<Molecule> mol )
            : ptr( std::move( mol ) ), need_remove( false ) {};

        std::unique_ptr<Molecule> ptr;
        bool                      need_remove;
    };

    std::vector<MoleculeInfo> molecules_;
    std::vector<size_t>       remove_indexes_;
    std::vector<MoleculeInfo> new_molecules_;

    sf::Vector2f       pos_;
    sf::Vector2f       sizes_;
    sf::RectangleShape border_;
};

} // namespace application
