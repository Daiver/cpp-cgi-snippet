
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
        typedef MonadType (*BindFunc)(InnerType);

        struct BindFunctor
        {
            BindFunc f;
            BindFunctor(BindFunc f)
            {
                this->f = f;
            }

            MonadType operator ()(InnerType x) const
            {
                return f(x);
            }
        };

        static MonadType mreturn(InnerType) {throw "Not Implemented!";}

        //virtual MonadType bind(BindFunc) const = 0;

        MonadType bind(BindFunc f) const
        {
            BindFunctor func(f);
            return this->bind(func);
        }

        /*MonadType map(InnerType (*func)(InnerType))
        {
            return this->bind(
                        staticCompose<MonadType, InnerType, InnerType,
                            MonadType::mreturn,
                    );
        }*/
};

}
