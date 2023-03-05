#include "spmat.h"

// Addition operator inside the class
void spmat::operator+=(const spmat* B)
{
  for(unsigned int i=0;i<this->getNumRows();i++)
  {
    for(unsigned int j=0;j<this->getNbNZ(i);j++)
    {
      this->addValue(i,B->getNZColumn(i,j),B->getNZValue(i,j));
    }
  }
}
