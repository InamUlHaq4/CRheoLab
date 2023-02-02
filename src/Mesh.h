#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <algorithm> 

#include "Point.h"
#include "Face.h"
#include "Cell.h"
#include "Patch.h"
#include "findFiles.h"
#include "IOObject.h"

#include "RunTime.h"

class Mesh {

public:

  // Constructor
  Mesh(const RunTime& time);

  // Destructor
  ~Mesh() = default;

  // No copy, no assigment
  Mesh(const Mesh&) = delete;
  void operator=(const Mesh&) = delete;

  const RunTime& time() const {return time_;}

  std::vector <IOObject*>& dataBaseRef();
  const std::vector <IOObject*>& dataBase() const;
  bool addToDataBase(IOObject* obj);

  template<typename T>
  T& lookup(const std::string& seeking) const;

  //Getters
  const std::vector<Cell>& cellList() const;
  const std::vector<Patch>& patchList() const;
  const std::vector<Point>& pointList() const;
  const std::vector<Face>& faceList() const;
  const unsigned int nCells() const;
  const unsigned int nInteriorFaces()  const;
  const unsigned int nPoints() const;
  const unsigned int nFaces() const;
  const unsigned int nBoundaryFaces() const;
  const unsigned int nPatches() const;

private:

  void readMesh();

  unsigned int getNEntitites(std::ifstream& file);

  void readPoints(std::string path);

  void readFaces(std::string path);

  vector<int> readOwners(std::string path);

  vector<int> readNeighbours(std::string path);

  void updateCellAndFaceData(std::string pathOwners, std::string pathNeighbours);

  void readBoundary(std::string path);

  const RunTime& time_;
   
  unsigned int nCells_;

  unsigned int nPoints_;
  
  unsigned int nFaces_;
 
  unsigned int nInteriorFaces_;

  unsigned int nBoundaryFaces_;

  unsigned int nPatches_;

  std::vector<Point> pointList_;

  std::vector<Face>  faceList_;

  std::vector<Cell>  cellList_;

  std::vector<Patch> patchList_;
  
  std::vector<IOObject*> dataBase_;

} ;

#include "MeshI.h"

#endif


