#include "Orthogonal.h" 

std::string Orthogonal::nonOrthogonalCorrectionScheme_("Orthogonal");
 
Orthogonal::Orthogonal(): interpolationScheme_("Linear")
{
    std::cout << "Orthogonal class is being created" << std::endl;
}

std::string Orthogonal::className()
{
    return nonOrthogonalCorrectionScheme_;
}

std::shared_ptr<Laplacian> Orthogonal::New()
{
    return std::make_shared<Orthogonal>();
}

const std::string& Orthogonal::interpolationScheme()
{
  // std::cout << interpolationScheme_ << std::endl;
  return interpolationScheme_;
}
const std::string& Orthogonal::nonOrthogonalCorrectionScheme()
{
  // std::cout << nonOrthogonalCorrectionScheme_ << std::endl;
  return nonOrthogonalCorrectionScheme_;
}

void Orthogonal::print()
{
    std::cout
        << this->discretizationScheme() << " " 
        << interpolationScheme() << " " 
        << nonOrthogonalCorrectionScheme() << " scheme for the " 
        << this->operatorType() << " operator!"
        << std::endl;
}

bool Orthogonal::signToRegistry = Factory::registerScheme
(
    Orthogonal::nonOrthogonalCorrectionScheme_,
    Orthogonal::New
);
