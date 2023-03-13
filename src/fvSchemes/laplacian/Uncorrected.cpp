#include "Uncorrected.h" 

std::string Uncorrected::nonOrthogonalCorrectionScheme_("Uncorrected");
 
Uncorrected::Uncorrected(): interpolationScheme_("Linear")
{
    std::cout << "Uncorrected class is being created" << std::endl;
}

std::string Uncorrected::className()
{
    return nonOrthogonalCorrectionScheme_;
}

std::shared_ptr<Laplacian> Uncorrected::New()
{
    return std::make_shared<Uncorrected>();
}

const std::string& Uncorrected::interpolationScheme()
{
  // std::cout << interpolationScheme_ << std::endl;
  return interpolationScheme_;
}

const std::string& Uncorrected::nonOrthogonalCorrectionScheme()
{
  // std::cout << nonOrthogonalCorrectionScheme_ << std::endl;
  return nonOrthogonalCorrectionScheme_;
}

void Uncorrected::print()
{
    std::cout
        << this->discretizationScheme() << " " 
        << interpolationScheme() << " " 
        << nonOrthogonalCorrectionScheme() << " scheme for the " 
        << this->operatorType() << " operator!"
        << std::endl;
}

bool Uncorrected::signToRegistry =
Factory::registerScheme
(
    Uncorrected::nonOrthogonalCorrectionScheme_,
    Uncorrected::New
);
