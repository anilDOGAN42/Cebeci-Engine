#include "transform.hpp"

namespace CebeciEngine::Core {
transform::transform(){
    this->Position={0,0,0};
    this->Rotation={0,0,0};
    this->Scale={1,1,1};
}
}