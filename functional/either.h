
namespace functional {


template<typename LeftType, typename RightType>
class Either
{
    public: 
        typedef Either<LeftType, RightType> (*BindFunc)(RightType);

        static Either Left(LeftType val)
        {
            Either e;
            e.isLeft = true;
            e.lvalue = val;
            return e;
        }

        static Either Right(RightType val)
        {
            Either e;
            e.isLeft = false;
            e.value = val;
            return e;
        }
        bool isLeft;

        RightType getValue() const 
        {
            if(!isLeft)
                return value;
            throw "BAD EXTRACT";
        }

        Either<LeftType, RightType> bind(BindFunc func) const
        {
            if(isLeft)
                return Left(lvalue);
            return func(value);
        }

    protected:
        Either(){}

        RightType value;
        LeftType  lvalue;
};

}
