#pragma once

namespace reactor {
namespace model {

class Molecule {
  public:
    Molecule( double r, double x, double y, double vx, double vy, double m );
    virtual ~Molecule() = default;

    enum Type { CIRCLE, SQUARE, COUNT };

    void
    move( double dt );
    double
    getX() const;
    double
    getY() const;
    double
    getVx() const;
    double
    getVy() const;
    void
    setVx( double vx );
    void
    setVy( double vy );
    void
    setX( double x );
    void
    setY( double y );
    double
    getR() const;
    double
    getM() const;
    double
    getKineticEnergy() const;
    double
    getPotentialEnergy() const;
    double
    getFullEnergy() const;
    virtual Type
    getType() const = 0;

    static bool
    checkCollision( const Molecule& mol1, const Molecule& mol2 );

  protected:
    double r_, x_, y_, vx_, vy_, m_;
};

class CircleMolecule : public Molecule {
  public:
    CircleMolecule( double r, double x, double y, double vx, double vy, double m )
        : Molecule( r, x, y, vx, vy, m )
    {
    }

  private:
    Molecule::Type
    getType() const override
    {
        return Type::CIRCLE;
    }
};

class SquareMolecule : public Molecule {
  public:
    SquareMolecule( double r, double x, double y, double vx, double vy, double m )
        : Molecule( r, x, y, vx, vy, m )
    {
    }

  private:
    Molecule::Type
    getType() const override
    {
        return Type::SQUARE;
    }
};

} // namespace model
} // namespace reactor
