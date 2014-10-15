
namespace functional {

template <typename MonadType, typename InnerType>
class Monad
{
    public:
        typedef MonadType (*BindFunc)(InnerType);
        static MonadType mreturn(InnerType) {};

        virtual MonadType bind(BindFunc) const = 0;
};

}
