#pragma once

#include "application/molecule.hpp"
#include "application/molecule_types.hpp"
#include "application/vector.hpp"
#include <array>
#include <cmath>
#include <memory>
#include <vector>

namespace application {

class MoleculeManager {
    using CollideFuncT = void ( MoleculeManager::* )( Molecule& mol1, Molecule& mol2 );

  public:
    size_t
    GetMoleculesCount()
    {
        return molecules_.size();
    }

    void
    HandleWallCollisions( Molecule& mol )
    {
        float r  = mol.GetR();
        float x  = mol.GetX();
        float y  = mol.GetY();
        float vx = mol.GetVx();
        float vy = mol.GetVy();

        float width  = sizes_.GetX();
        float height = sizes_.GetY();

        if ( x + 2 * r > width )
        {
            mol.SetVx( -vx );
            mol.SetX( width - 2 * r );
        }

        if ( x < 0 )
        {
            mol.SetVx( -vx );
            mol.SetX( 0 );
        }

        if ( y + 2 * r > height )
        {
            mol.SetVy( -vy );
            mol.SetY( height - 2 * r );
        }

        if ( y < 0 )
        {
            mol.SetVy( -vy );
            mol.SetY( 0 );
        }
    }

    void
    HandleCollisions()
    {
        size_t n_molecules = molecules_.size();

        for ( size_t i = 0; i < n_molecules - 1; ++i )
        {
            for ( size_t j = i + 1; j < n_molecules; ++j )
            {
                Molecule& mol1 = *molecules_[i];
                Molecule& mol2 = *molecules_[j];

                if ( Molecule::CheckCollision( mol1, mol2 ) )
                {
                    Collide( i, j );
                }
            }
        }
    }

    void
    HandleCollisions( float elapsed_time )
    {
        Clear();
        HandleCollisions();
    }

    float
    CalcSumEnergy() const
    {
        float energy = 0;

        for ( const auto& molecule : molecules_ )
        {
            float m  = molecule->GetWeight();
            float vx = molecule->GetVx();
            float vy = molecule->GetVy();

            energy += m * ( vx * vx + vy * vy ) / 2;
        }

        return energy;
    }

    MoleculeManager()
    {
        vtable_[Molecule::CIRCLE][Molecule::CIRCLE] = &MoleculeManager::CollideCircleCircle;
        vtable_[Molecule::CIRCLE][Molecule::SQUARE] = &MoleculeManager::CollideCircleSquare;
        vtable_[Molecule::SQUARE][Molecule::CIRCLE] = &MoleculeManager::CollideCircleSquare;
        vtable_[Molecule::SQUARE][Molecule::SQUARE] = &MoleculeManager::CollideSquareSquare;
    }

    void
    Collide( size_t mol1_idx, size_t mol2_idx )
    {
        Molecule& mol1 = *molecules_[mol1_idx];
        Molecule& mol2 = *molecules_[mol2_idx];

        remove_indexes_.push_back( mol1_idx );
        remove_indexes_.push_back( mol2_idx );

        ( this->*vtable_[mol1.GetType()][mol2.GetType()] )( mol1, mol2 );
    }

    void
    AddCircleMolecule( float r, float x, float y, float vx, float vy )
    {
        molecules_.emplace_back(
            std::make_unique<CircleMolecule>( CircleMolecule( r, x, y, vx, vy ) ) );
    }

    void
    AddSquareMolecule( float r, float x, float y, float vx, float vy )
    {
        molecules_.emplace_back(
            std::make_unique<SquareMolecule>( SquareMolecule( r, x, y, vx, vy, 2.0f ) ) );
    }

    void
    Clear()
    {
        remove_indexes_.clear();
        new_molecules_.clear();
    }

    const std::vector<std::unique_ptr<Molecule>>&
    GetMoleculesVector() const
    {
        return molecules_;
    }

    void
    PostRendering( float elapsed_time )
    {
        std::sort( remove_indexes_.begin(), remove_indexes_.end(), []( size_t a, size_t b ) {
            return a > b;
        } );

        for ( const auto& req : remove_indexes_ )
        {
            if ( req < molecules_.size() )
            {
                molecules_.erase( molecules_.begin() + req );
            }
        }

        for ( auto& req : new_molecules_ )
        {
            molecules_.push_back( std::move( req ) );
        }

        for ( auto& mol : molecules_ )
        {
            mol->Move( elapsed_time );
        }
    }

  private:
    void
    CollideCircleCircle( Molecule& mol1, Molecule& mol2 )
    {
        // std::cerr << __LINE__ << std::endl;
        // std::abort();

        float r  = ( mol1.GetR() + mol2.GetR() ) / 2.0f;
        float x  = ( mol1.GetX() + mol2.GetX() ) / 2.0f;
        float y  = ( mol1.GetY() + mol2.GetY() ) / 2.0f;
        float vx = mol1.GetVx() + mol2.GetVx();
        float vy = mol1.GetVy() + mol2.GetVy();
        float m  = mol1.GetWeight() + mol2.GetWeight();

        new_molecules_.push_back( { std::make_unique<SquareMolecule>( r, x, y, vx, vy, m ) } );
    }

    void
    CollideCircleSquare( Molecule& mol1, Molecule& mol2 )
    {
        // std::cerr << __LINE__ << std::endl;
        // std::abort();

        float r  = ( mol1.GetR() + mol2.GetR() ) / 2.0f;
        float x  = ( mol1.GetX() + mol2.GetX() ) / 2.0f;
        float y  = ( mol1.GetY() + mol2.GetY() ) / 2.0f;
        float vx = mol1.GetVx() + mol2.GetVx();
        float vy = mol1.GetVy() + mol2.GetVy();
        float m  = mol1.GetWeight() + mol2.GetWeight();

        new_molecules_.push_back(
            { std::make_unique<SquareMolecule>( r * m / 10.0f, x, y, vx, vy, m ) } );
    }

    void
    CollideSquareSquare( Molecule& mol1, Molecule& mol2 )
    {
        // std::cerr << __LINE__ << std::endl;
        // std::abort();

        float r             = ( mol1.GetR() + mol2.GetR() ) / 2.0f;
        float x             = ( mol1.GetX() + mol2.GetX() ) / 2.0f;
        float y             = ( mol1.GetY() + mol2.GetY() ) / 2.0f;
        float v1x           = mol1.GetVx();
        float v1y           = mol1.GetVy();
        float v2x           = mol2.GetVx();
        float v2y           = mol2.GetVy();
        float vx            = mol1.GetVx() + mol2.GetVx();
        float vy            = mol1.GetVy() + mol2.GetVy();
        float m1            = mol1.GetWeight();
        float m2            = mol2.GetWeight();
        float total_circles = m1 + m2;

        float energy = m1 * ( v1x * v1x + v1y * v1y ) / 2 + m2 * ( v2x * v2x + v2y * v2y );

        // if ( total_circles > 100 )
        // {
        //     energy *= total_circles / 100;
        //     total_circles = 100;
        // }

        float theta = M_PI / total_circles;
        float delta = 3 * r / std::sin( theta );

        float circle_energy = energy / total_circles;
        float v_circle      = sqrt( 2 * circle_energy );

        for ( int k = 0; k < total_circles; k++ )
        {
            float offset_angle     = 2.0f * M_PI * k / total_circles;
            float cos_offset_angle = std::cos( offset_angle );
            float sin_offset_angle = std::sin( offset_angle );

            float spawn_x = x + delta * cos_offset_angle;
            float spawn_y = y + delta * sin_offset_angle;

            new_molecules_.push_back(
                { std::make_unique<CircleMolecule>( r,
                                                    spawn_x,
                                                    spawn_y,
                                                    v_circle * cos_offset_angle,
                                                    v_circle * sin_offset_angle ) } );
        }
    }

  private:
    std::array<std::array<CollideFuncT, Molecule::N_TYPES>, Molecule::N_TYPES> vtable_;

    std::vector<std::unique_ptr<Molecule>> molecules_;

    std::vector<size_t>                    remove_indexes_;
    std::vector<std::unique_ptr<Molecule>> new_molecules_;

    Vector sizes_;
};

} // namespace application
