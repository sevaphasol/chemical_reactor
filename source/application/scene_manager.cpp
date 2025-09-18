#include "application/scene_manager.hpp"
#include "application/config.hpp"
#include "application/molecule.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <memory>
#include <vector>

namespace application {

SceneManager::SceneManager()
    : width_( Config::WindowWidth ), height_( Config::WindowHeight ),
      window_( sf::VideoMode( Config::WindowWidth, Config::WindowHeight ),
               Config::Title,
               sf::Style::Close ),
      n_molecules_plot_( sf::Vector2f( 0, 0 ), sf::Vector2f( 500, 500 ) ),
      energy_plot_( sf::Vector2f( 550, 0 ), sf::Vector2f( 500, 500 ) )
{
    window_.setFramerateLimit( 60 );
}

void
SceneManager::Run()
{
    float time = 0;

    while ( window_.isOpen() )
    {
        HandleEvents();

        n_molecules_plot_.AddPoint( time, molecule_manager_.GetMoleculesCount() / 100.0f );
        energy_plot_.AddPoint( time, molecule_manager_.CalcSumEnergy() / 10000000000.0 );

        Render( Config::DeltaTime );
        Draw();

        time += Config::DeltaTime;
    }
}

void
SceneManager::AddCircleMolecule( float r, float x, float y, float vx, float vy )
{
    molecule_manager_.AddCircleMolecule( r, x, y, vx, vy );
}

void
SceneManager::AddSquareMolecule( float r, float x, float y, float vx, float vy )
{
    molecule_manager_.AddSquareMolecule( r, x, y, vx, vy );
}

void
SceneManager::HandleEvents()
{
    sf::Event event;

    while ( window_.pollEvent( event ) )
    {
        if ( event.type == sf::Event::Closed )
        {
            window_.close();
        }

        bool left  = sf::Keyboard::isKeyPressed( sf::Keyboard::Left );
        bool right = sf::Keyboard::isKeyPressed( sf::Keyboard::Right );

        width_ += ( int( right ) - int( left ) ) * 10;

        //         bool can_continue = sf::Keyboard::isKeyPressed( sf::Keyboard::Space );
        //
        //         while ( !can_continue )
        //         {
        //             can_continue = sf::Keyboard::isKeyPressed( sf::Keyboard::Space );
        //         }
    }
}

void
SceneManager::Render( float elapsed_time )
{
    molecule_manager_.Clear();

    ParseCollisions();

    molecule_manager_.PostRendering( elapsed_time );
}

void
SceneManager::Draw()
{
    window_.clear();

    const auto& mol_vector = molecule_manager_.GetMoleculesVector();

    for ( const auto& molecule : mol_vector )
    {
        window_.draw( *molecule );
    }

    window_.draw( n_molecules_plot_ );
    window_.draw( energy_plot_ );

    window_.display();
}

void
SceneManager::HandleWallCollision( Molecule& molecule ) const
{
    float vx = molecule.GetVx();
    float vy = molecule.GetVy();
    float x  = molecule.GetX();
    float y  = molecule.GetY();
    float r  = molecule.GetR();

    if ( x + 2 * r > width_ )
    {
        molecule.SetVx( -vx );
        molecule.SetX( width_ - 2 * r );
    }

    if ( x < 0 )
    {
        molecule.SetVx( -vx );
        molecule.SetX( 0 );
    }

    if ( y + 2 * r > height_ )
    {
        molecule.SetVy( -vy );
        molecule.SetY( height_ - 2 * r );
    }

    if ( y < 0 )
    {
        molecule.SetVy( -vy );
        molecule.SetY( 0 );
    }
}

void
SceneManager::ParseCollisions()
{
    const auto& mol_vector = molecule_manager_.GetMoleculesVector();

    size_t n_molecules = mol_vector.size();

    for ( size_t i = 0; i < n_molecules - 1; ++i )
    {
        for ( size_t j = i + 1; j < n_molecules; ++j )
        {
            Molecule& mol1 = *mol_vector[i];
            Molecule& mol2 = *mol_vector[j];

            if ( Molecule::CheckCollision( mol1, mol2 ) )
            {
                molecule_manager_.Collide( i, j );
            }
        }
    }

    for ( const auto& molecule : mol_vector )
    {
        HandleWallCollision( *molecule );
    }
}

} // namespace application
