
namespace functional {

template<typename Out, typename Middle, typename In, Out F(Middle), Middle G(In)>
Out staticCompose(In x)
{
    return F(G(x));
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

        MonadType bind(BindFunc f) const
        {
            return this->bind(BindFunctor(f));
        }

        MonadType map(InnerFunc f)
        {
            return (*(MonadType*)this).bind(InnerFunctor(f));
        }
};

}
