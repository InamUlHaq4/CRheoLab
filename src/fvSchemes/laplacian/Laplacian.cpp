#include "Laplacian.h"

Laplacian::Laplacian(): name_("Laplacian"), discretizationScheme_("Gauss")
{   // Todo WdCG
    std::cout << "Base class is being created" << std::endl;
}

const std::string& Laplacian::operatorType()
{
  return name_;
}
const std::string& Laplacian::discretizationScheme()
{
  return discretizationScheme_ ;
}
