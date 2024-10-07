using System;

namespace RSDK;

[CRepr] public struct bool32 : IEquatable<Self>
{
    public uint32 val;

    public this(int32 value) => val = (.)value;
    public this(uint32 value) => val = value;
    public this(bool value) => val = value ? 1 : 0;

    public bool Equals(Self other) { return val == other.val; }
    public bool Equals(Object obj) { return obj is Self && Equals((Self)obj); }

    public static implicit operator bool(Self b) => b.val != 0;

    public static implicit operator int(Self b) => b.val;
    public static implicit operator int32(Self b) => (.)b.val;

    public static implicit operator uint(Self b) => b.val;
    public static implicit operator uint32(Self b) => b.val;

    public static implicit operator Self(bool b) => b ? 1 : 0;
    public static implicit operator Self(uint32 value) => Self(value);

    public static bool operator ==(Self lhs, Self rhs) => lhs.val == rhs.val;
    public static bool operator !=(Self lhs, Self rhs) => lhs.val != rhs.val;
}

[CRepr] public struct Boolean<T> where T : var, IInteger, IMinMaxValue<T>
{
    public T val;

    public this(T value) => val = value;
    public this(bool value) => val = value ? 1 : 0;

    public bool Equals(Self other) { return val == other.val; }
    public bool Equals(Object obj) { return obj is Self && Equals((Self)obj); }

    public static implicit operator bool(Self b) => b.val != 0;

    public static implicit operator int(Self b) => b.val;
    public static implicit operator int32(Self b) => (.)b.val;

    public static implicit operator uint(Self b) => b.val;
    public static implicit operator uint32(Self b) => b.val;

    public static implicit operator Self(bool b) => b ? 1 : 0;
    public static implicit operator Self(T value) => Self(value);

    public static bool operator ==(Self lhs, Self rhs) => lhs.val == rhs.val;
    public static bool operator !=(Self lhs, Self rhs) => lhs.val != rhs.val;
}

typealias color = uint32;
typealias size_t = uint;
typealias long = int64;