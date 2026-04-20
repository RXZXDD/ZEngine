#pragma once
#include "Delegate.h"

#define DECLEAR_DELEGATE_TYPE(TypeName,ReturnType, ...) \
     typedef Delegate<ReturnType(__VA_ARGS__)> TypeName;

#define DECLEAR_DELEGATE(TypeName) \
    DECLEAR_DELEGATE_TYPE(TypeName, void);

#define DECLEAR_DELEGATE_ONE_PARAM(TypeName, ParamType) \
    DECLEAR_DELEGATE_TYPE(TypeName, void, ParamType)

#define DECLEAR_DELEGATE_TWO_PARAM(TypeName, ParamType1, ParamType2) \
    DECLEAR_DELEGATE_TYPE(TypeName, void, ParamType1, ParamType2)

#define DECLEAR_DELEGATE_WITH_RETURN(TypeName, ReturnType) \
    DECLEAR_DELEGATE_TYPE(TypeName, ReturnType);

#define DECLEAR_DELEGATE_ONE_PARAM_WITH_RETURN(TypeName, ReturnType, ParamType) \
    DECLEAR_DELEGATE_TYPE(TypeName, ReturnType, ParamType)

#define DECLEAR_DELEGATE_TWO_PARAM_WITH_RETURN(TypeName, ReturnType, ParamType1, ParamType2) \
    DECLEAR_DELEGATE_TYPE(TypeName, ReturnType, ParamType1, ParamType2)