#pragma once

#include <SFML/Graphics.hpp>
#include <application/molecule.hpp>
#include <application/molecule_manager.hpp>
#include <application/graph.hpp>

namespace application {

class SceneManager {
  public:
    SceneManager();

    void
    Run();

    void
    AddCircleMolecule( float r, float x, float y, float vx, float vy );

    void
    AddSquareMolecule( float r, float x, float y, float vx, float vy );

  private:
    void
    HandleEvents();

    void
    Render( float elapsed_time );

    void
    Draw();

    void
    ParseCollisions();

    void
    HandleWallCollision( Molecule& molecule ) const;

  private:
    sf::RenderWindow window_;

    MoleculeManager molecule_manager_;

    CoordSystem n_molecules_plot_;
    CoordSystem energy_plot_;

    uint width_;
    uint height_;
};

} // namespace application
