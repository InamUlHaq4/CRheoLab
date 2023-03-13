#include "Limited.h" 

std::string Limited::nonOrthogonalCorrectionScheme_("Limited");
 
Limited::Limited(): interpolationScheme_("Linear"), conditioner_(""), phiFactor(0)
{
    std::cout << "Limited class is being created" << std::endl;
}

std::string Limited::className()
{
    return nonOrthogonalCorrectionScheme_;
}

std::shared_ptr<Laplacian> Limited::New()
{
    return std::make_shared<Limited>();
}

const std::string& Limited::interpolationScheme()
{
  // std::cout << interpolationScheme_ << std::endl;
  return interpolationScheme_;
}

const std::string& Limited::nonOrthogonalCorrectionScheme()
{
  // std::cout << nonOrthogonalCorrectionScheme_ << std::endl;
  return nonOrthogonalCorrectionScheme_;
}

void Limited::print()
{
    std::cout
        << this->discretizationScheme() << " " 
        << interpolationScheme() << " " 
        << nonOrthogonalCorrectionScheme() << " scheme for the " 
        << this->operatorType() << " operator!"
        << std::endl;
}

bool Limited::signToRegistry =
Factory::registerScheme
(
    Limited::nonOrthogonalCorrectionScheme_,
    Limited::New
);
