#include "monad.h"


namespace functional {

template<typename LeftType, typename RightType>
class Either : public Monad<Either<LeftType, RightType>, RightType>
{
    public: 
        //typedef Either<LeftType, RightType> (*BindFunc)(RightType);
        typedef typename Monad<Either, RightType>::BindFunc BindFuncEither;

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

        static Either mreturn(RightType r)
        {
            return Right(r);
        }

        bool isLeft;

        RightType getValue() const 
        {
            if(!isLeft)
                return value;
            throw "BAD EXTRACT";
        }

        Either<LeftType, RightType> bind(BindFuncEither func) const
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