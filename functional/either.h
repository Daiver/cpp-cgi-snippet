
namespace functional {

enum EitherType {EITHER_LEFT, EITHER_RIGHT};

template<typename LeftType, typename RightType>
class Either
{
    public: 
        static Either Left(LeftType val){
            return Either(EITHER_LEFT, val);
        }

        static Either Right(RightType val){
            return Either(val);
        }

    protected:
        Either(RightType right){
            this->type = EITHER_RIGHT;
            value = right;
        }

        Either(EitherType type, LeftType left){
            this->type = EITHER_LEFT;
            lvalue = left;
        }

        EitherType type;
        RightType value;
        LeftType  lvalue;
};

}
