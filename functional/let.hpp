#ifndef __LET_H__
#define __LET_H__

#include "tripple.hpp"
#include "../common.hpp"

namespace functional {

#define LET2(Name1, Name2, Pair) \
    TYPEOF(Pair.first) Name1 = Pair.first; TYPEOF(Pair.second) Name2 = Pair.second;

#define LET3(Name1, Name2, Name3, Tripple) \
    TYPEOF(Tripple.first) Name1 = Tripple.first; \
    TYPEOF(Tripple.second) Name2 = Tripple.second; \
    TYPEOF(Tripple.third) Name3 = Tripple.third;

}
#endif
