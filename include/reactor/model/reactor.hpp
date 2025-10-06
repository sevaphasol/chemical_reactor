#pragma once

#include "reactor/model/molecule.hpp"

#include <vector>
#include <memory>

namespace reactor {
namespace model {

class Reactor {
  public:
    Reactor( double w, double h );
    ~Reactor() = default;

    void
    update( double dt );

    void
    addMolecule( std::unique_ptr<Molecule> mol );
    void
    removeMolecule( size_t index );
    void
    movePiston( double dist );

    size_t
    getMoleculesCount() const;
    double
    getElapsedTime() const;
    double
    getTotalEnergy() const;

    double
    getW() const;
    double
    getH() const;
    double
    getPistonPos() const;

    const std::vector<std::unique_ptr<Molecule>>&
    getMolecules() const;

  private:
    void
    handleWallCollisions();
    void
    handleMoleculesCollisions();
    void
    moveMolecules( double dt );

    bool
    collide( size_t mol1_idx, size_t mol2_idx );
    void
    collide( Molecule& mol1, Molecule& mol2 );
    void
    collideCircleCircle( Molecule& mol1, Molecule& mol2 );
    void
    collideCircleSquare( Molecule& mol1, Molecule& mol2 );
    void
    collideSquareSquare( Molecule& mol1, Molecule& mol2 );
    void
    collideSquareCircle( Molecule& mol1, Molecule& mol2 );

  private:
    std::vector<std::unique_ptr<Molecule>> molecules_;
    std::vector<std::unique_ptr<Molecule>> new_molecules_;
    std::vector<size_t>                    remove_indexes_;

    double elapsed_time_ = 0.0;
    double w_            = 0.0;
    double h_            = 0.0;
    double piston_pos_   = 0.0;
};

} // namespace model
} // namespace reactor
