#include "Corrected.h" 

std::string Corrected::nonOrthogonalCorrectionScheme_("Corrected");
 
Corrected::Corrected(): interpolationScheme_("Linear")
{
    std::cout << "Corrected class is being created" << std::endl;
}

std::string Corrected::className()
{
    return nonOrthogonalCorrectionScheme_;
}

std::shared_ptr<Laplacian> Corrected::New()
{
    return std::make_shared<Corrected>();
}

const std::string& Corrected::interpolationScheme()
{
  // std::cout << interpolationScheme_ << std::endl;
  return interpolationScheme_;
}

const std::string& Corrected::nonOrthogonalCorrectionScheme()
{
  // std::cout << nonOrthogonalCorrectionScheme_ << std::endl;
  return nonOrthogonalCorrectionScheme_;
}

void Corrected::print()
{
    std::cout
        << this->discretizationScheme() << " " 
        << interpolationScheme() << " " 
        << nonOrthogonalCorrectionScheme() << " scheme for the " 
        << this->operatorType() << " operator!"
        << std::endl;
}

bool Corrected::signToRegistry =
Factory::registerScheme
(
    Corrected::nonOrthogonalCorrectionScheme_,
    Corrected::New
);