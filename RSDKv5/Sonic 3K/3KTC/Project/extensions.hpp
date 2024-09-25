#pragma once

namespace RSDK
{

#define VoidPtr(name)      void (*name)(void)
#define Type_VoidPtr       void (*)(void)
#define Type_StateHook     bool32 (*)(bool32)
#define RSDK_TYPEDEF(name) typedef struct name name

#define THIS_REF(class) class *self = RSDK_THIS(class)
#define SELF_REF(class) class *self = RSDK_SELF(class)

#define RSDK_THIS(class) ((class *)this)
#define RSDK_SELF(class) ((class *)sceneInfo->entity)

// Gets & Sets a public function to a pointer
#define GetPublicFuncAssign(ptr, id, functionName) ptr = (decltype(ptr))Mod::GetPublicFunction(id, functionName)

template <typename R> struct Action {

    R (Action::*action)();

    inline void Init() { action = nullptr; }

    template <typename T> inline bool Set(R (T::*action)())
    {
        // converts from T:: -> Action:: without the compiler interfering :]
        union {
            R (T::*in)();
            R (Action::*out)();
        };
        in = action;

        this->action = out;
        return true;
    }

    inline bool Set(R (*action)())
    {
        // converts from T:: -> Action:: without the compiler interfering :]
        union {
            R (*in)();
            R (Action::*out)();
        };
        in = action;

        this->action = out;
        return true;
    }

    template <typename T> inline R SetAndRun(R (T::*action)(), void *self = nullptr)
    {
        bool applied = Set(action);

        if (applied)
            return Run(self);

        return R();
    }

    template <typename T> inline R SetAndRun(R (*action)(), void *self = nullptr)
    {
        bool applied = Set(action);

        if (applied)
            return Run(self);

        return R();
    }

    inline R Run(void *self)
    {
        if (action) {
            return (((Action *)self)->*action)();
        }

        return R();
    }

    template <typename T> inline bool Matches(void *other)
    {
        // converts from Action:: -> void (*)() without the compiler interfering :]
        union {
            R *in;
            R (Action::*out)();
        };
        in = other;

        return action == out;
    }

    template <typename T> inline bool Matches(R (T::*other)()) { return action == (R(Action::*)())other; }

    inline bool Matches(Action *other)
    {
        if (other == nullptr)
            return action == nullptr;
        else
            return action == other->action;
    }

    inline void Copy(Action *other)
    {
        if (other == nullptr)
            this->action = nullptr;
        else
            this->action = other->action;
    }

    // Equals
    inline void operator=(const Action &rhs) { this->Copy((Action *)&rhs); }

    // Conditionals
    inline bool operator==(const Action &rhs) { return this->Matches((Action *)&rhs); }
    inline bool operator!=(const Action &rhs) { return !(*this == rhs); }
};

namespace Ext
{

// ---------------------
// RSDKv5 ModAPI Helpers
// ---------------------

// Essentially just an alias for Mod::GetPublicFunction
template <typename T> inline static T PubFunc(const char *id, const char *functionName) { return (T)Mod::GetPublicFunction(id, functionName); }
template <typename T> inline static T PubFunc(const char *functionName) { return (T)Mod::GetPublicFunction(NULL, functionName); }

// Using T::SomeFunction as a state
template <typename T, typename X> inline void StateHook(T(X::*state), bool32 (*hook)(bool32 skippedState), bool32 priority)
{
    modTable->RegisterStateHook(reinterpret_cast<void (*&)()>(state), hook, priority);
}

// Using an RSDK::Action as a state
template <typename T, typename X> inline void StateHook(RSDK::Action<T> &state, bool32 (*hook)(bool32 skippedState), bool32 priority)
{
    modTable->RegisterStateHook(reinterpret_cast<void (*&)()>(state.action), hook, priority);
}

} // namespace Ext

} // namespace RSDK
