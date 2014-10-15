
namespace functional {

template<typename Out, typename Middle, typename In, Out F(Middle), Middle G(In)>
Out staticCompose(In x)
{
    return F(G(x));
}

template <typename ClassT, typename RetT, typename T1>
RetT invokeM(ClassT *instance, RetT (ClassT::*f)(T1), T1 a)
{
    return ((*instance).*f)(a);
}

template <typename MonadType, typename InnerType>
class Monad
{
    public:
        typedef MonadType (*BindFunc )(InnerType);
        typedef InnerType (*InnerFunc)(InnerType);

        struct BindFunctor
        {
            BindFunc f;
            BindFunctor(BindFunc f) {this->f = f;}
            MonadType operator ()(InnerType x) const {return f(x);}
        };

        struct InnerFunctor
        {
            InnerFunc f;
            InnerFunctor(InnerFunc f) {this->f = f;}
            MonadType operator ()(InnerType x) const {return MonadType::mreturn(f(x));}
        };

        static MonadType mreturn(InnerType) {throw "Not Implemented!";}

        //virtual MonadType bind(BindFunc) const = 0;

        MonadType bind(BindFunc f) const
        {
            BindFunctor func(f);
            return this->bind(func);
        }

        MonadType map(InnerFunc f)
        {
            return (*(MonadType*)this).bind(InnerFunctor(f));
        }
};

}
