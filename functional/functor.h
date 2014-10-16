
namespace functional {

template<typename Out, typename In, class F>
class MonoFunctor {
public:
    F f;
    MonoFunctor(F f){this->f = f;};
    inline Out operator()(In x) const {return f(x);}
};


template<typename Out, typename In, class F>
MonoFunctor<Out, In, F> mkMonoF(F f)
{
    return MonoFunctor<Out, In, F>(f);
}

template<typename Out, typename In, class F, class G>
class ComposeFunctor
{
public:
    F f;
    G g;
    ComposeFunctor(F f, G g):f(f), g(g) {}
    inline Out operator()(In x) const {return f(g(x));}
};

template<typename Out, typename In, class F, class G>
ComposeFunctor<Out, In, F, G> staticCompose(F f, G g)
{
    return ComposeFunctor<Out, In, F, G>(f, g);
}


}
