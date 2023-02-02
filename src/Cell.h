#ifndef CELL_H
#define CELL_H

class Face;

class Cell
{
    public:

        // Constructor
        Cell();

        // Destructor
        virtual  ~Cell()=default;

        // Setters
        void setCellFaces(const vector<Face*>&);
        void setID(const int&);

        // Getters
        const vector3& centerOfMass() const;
        const double& volume() const;
        const double& maxNonOrthogonality() const;
        const double& skewness() const;
        const int& ID() const;
        const vector<Face*>& cellFaces() const;


        // Computations
        void computeCenter();
        void computeVolume();
        double computepyrVol (const vector3&, const vector3&, const vector3&) const;
        vector3 computeGeometricCenter() const;
        void computeMaxNonOrthogonality();
        void computeSkewness();

    private:

        // ID
        int ID_;

        // Cell Volume
        double volume_;

        // Cell center of Mass
        vector3 centerOfMass_;

        // Cell skewness
        double skewness_;

        // Faces that make up a cell
        vector<Face*> cellFaces_;

        double maxNonOrthogonality_;

};

#endif // CELL_H
