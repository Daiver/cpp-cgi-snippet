#ifndef __TRIPPLE_H__
#define __TRIPPLE_H__

namespace functional{

template <typename T1, typename T2, typename T3>
class Tripple
{
public:
    Tripple(const T1 t1, T2 t2, const T3 t3): first(t1), second(t2), third(t3) {}
    T1 first;
    T2 second;
    T3 third;
};

template<typename T1, typename T2, typename T3>
inline Tripple<T1, T2, T3> makeTripple(const T1 &t1, const T2 &t2, const T3 &t3)
{
    return Tripple<T1, T2, T3>(t1, t2, t3);
}


}
#endif
