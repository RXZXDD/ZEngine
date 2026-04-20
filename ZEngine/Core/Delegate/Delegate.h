#pragma once
#include <iostream>

template<typename>
struct IDelegate;

template<typename Return, typename... Args>
struct IDelegate<Return(Args...)>
{

    virtual Return Execute(Args... args) = 0;
};

template<typename>
struct TDelegateBase;

template<typename Return, typename... Args>
struct TDelegateBase<Return(Args...)> : public IDelegate<Return(Args...)> {
    // using FuncPtrType = Return(*)(Args...);


    explicit TDelegateBase() {}
    virtual ~TDelegateBase() {}
    //std::tuple<Args...> args_;
};

template<typename>
struct TStaticDelegate;

template<typename Return, typename... Args>
struct TStaticDelegate<Return(Args...)> : public TDelegateBase<Return(Args...)> {

    using FuncPtrType = Return(*)(Args...);
    using FuncType = Return(Args...);

    explicit TStaticDelegate(FuncType func) : TDelegateBase<FuncType>(), func_(func) {
       //std::cout << "TStaticDelegate created with function pointer: " << reinterpret_cast<void*>(func) << std::endl;
    }

    Return Execute(Args... args) override {
        if (func_) {
            return func_(args...);
        }
        throw std::runtime_error("Function pointer is null");
    }



    FuncPtrType func_;
};

template<typename>
struct TMemFuncDelegate;

template<typename Return, typename ClsType, typename... Args>
struct TMemFuncDelegate<Return(ClsType::*)(Args...)> : public TDelegateBase<Return(Args...)> {
    using FuncPtrType = Return(ClsType::*)(Args...);
    using FuncType = Return(Args...);

    explicit TMemFuncDelegate(FuncPtrType func, ClsType* obj) : TDelegateBase<FuncType>(), func_(func), objPtr(obj) {
     //   std::cout << "TMemFuncDelegate created with function pointer: " << std::addressof(func) << " obj addr: " << std::addressof(*objPtr) << std::endl;

    }


    Return Execute(Args... args) override {
        if (func_ && objPtr) {
            return (objPtr->*func_)(args...);
        }
        throw std::runtime_error("Function pointer or object pointer is null");
    }
    FuncPtrType func_;
    ClsType* objPtr;
};


template<typename T>
struct Identity
{
    using type = T;
};

template<typename T>
using Identity_t = typename Identity<T>::type;


template<typename>
struct Delegate;

template<typename Return, typename... Args>
struct Delegate<Return(Args...)> {
    using FuncPtrType = Return(*)(Args...);
    using FuncType = Return(Args...);

    template<typename... Vars>
    void BindStatic(FuncType func, Vars... vars) {
        inst = new TStaticDelegate<Return(Args...)>(func, vars...);
    }

    template<typename ClsType, typename... Vars>
    void BindMember(Identity_t<Return(ClsType::*)(Args...)> func, ClsType* objPtr, Vars... vars) {
        inst = new TMemFuncDelegate<Return(ClsType::*)(Args...)>(func, objPtr, vars...);
    }

    Return Execute(Args... args) {
        if (inst) {
            return inst->Execute(args...);
        }
        throw std::runtime_error("Delegate instance is null");
    }

    Return ExecuteIfSafe(Args... args) {
        if (inst) {
            return inst->Execute(args...);
        }
		std::cerr << "Warning: Attempted to execute delegate, but instance is null. Returning default value." << std::endl;
        //throw std::runtime_error("Delegate instance is null");
    }

    void Unbind() {
        delete inst;
        inst = nullptr;
	}

private:
    TDelegateBase<FuncType>* inst;

};