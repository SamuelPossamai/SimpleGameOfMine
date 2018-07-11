
#include <utility/random.h>

using namespace utility;

std::mt19937 Random::_gen((std::random_device())());


