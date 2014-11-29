#ifndef __TRIPPLE_H__
#define __TRIPPLE_H__

namespace functional{

template<typename T, typename U>
struct refpair {
    refpair(T & first, U & second) : first(first), second(second) { }
 
    void operator = (const std::pair<T, U> & pair) {
        first = pair.first;
        second = pair.second;
    }
 
    T & first;
    U & second;
};
 
template<typename T, typename U>
refpair<T, U> mkrefpair(T & first, U & second) {
    return refpair<T, U>(first, second);
}

#define LET2(Type1, Name1, Type2, Name2) \
    Type1 Name1; Type2 Name2; functional::mkrefpair(Name1, Name2)

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

template<typename T1, typename T2, typename T3>
struct refTripple {
    refTripple(T1 & first, T2 & second, T3 & third) : first(first), second(second), third(third) { }
 
    void operator = (const Tripple<T1, T2, T3> &tripple) {
        first = tripple.first;
        second = tripple.second;
        third = tripple.third;
    }
 
    T1 & first;
    T2 & second;
    T3 & third;
};
 
template<typename T1, typename T2, typename T3>
refTripple<T1, T2, T3> mkrefTripple(T1 & first, T2 & second, T3 & third) {
    return refTripple<T1, T2, T3>(first, second, third);
}

#define LET3(Type1, Name1, Type2, Name2, Type3, Name3) \
    Type1 Name1; Type2 Name2; Type3 Name3; functional::mkrefTripple(Name1, Name2, Name3)


}
#endif
