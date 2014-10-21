#ifndef __MONAD_H__
#define __MONAD_H__

#include "functor.h"

namespace functional {

template <typename MonadType, typename InnerType>
class Monad
{
public:
    typedef MonadType (*BindFunc )(InnerType);
    typedef InnerType (*InnerFunc)(InnerType);

    static MonadType mreturn(InnerType) {throw "Not Implemented!";}

    inline MonadType bind(BindFunc f) const
    {
        return this->bind(f);
    }

    inline MonadType map(InnerFunc f)
    {
        return (*(MonadType*)this).bind(
                    staticCompose<MonadType, InnerType, 
                        MonadType (*)(InnerType), InnerType (*)(InnerType)>
                            (MonadType::mreturn, f)
                );
    }

    template<class F>
    inline MonadType operator>> (F f)
    {
        return ((MonadType*)(this))->bind(f);
    }

};

}

#endif
