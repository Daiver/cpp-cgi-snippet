
namespace functional {

template<typename LeftType, typename RightType>
class Either
{
    public: 
        static Either Left(LeftType val){
            Either e();
            e.isLeft = true;
            e.lvalue = val;
            return e;
        }

        static Either Right(RightType val){
            Either e();
            e.isLeft = false;
            e.value = val;
            return e;
        }
        bool isLeft;

    //protected:
        Either(){}

        RightType value;
        LeftType  lvalue;
};

}
