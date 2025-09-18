#pragma once

#include "application/molecule_manager.hpp"
#include "application/vector.hpp"

namespace application {

class Reactor : sf::Drawable {

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
    Render( float elapsed_time )
    {
        mol_manager_.HandleCollisions( elapsed_time );

        HandleWallCollisions();
    }

  private:
    MoleculeManager  mol_manager_;
    geometry::Vector sizes_;
};

} // namespace application
