#pragma once
#include "PlatformTypeDef.h"

template<typename TInType>
struct TPoint
{
	using InType = TInType;

	InType X;
	InType Y;

	TPoint() = default;
	TPoint(InType InX, InType InY)
		: X(InX)
		, Y(InY) 
	{}


};

using FIntPoint = TPoint<int32>;
using FFloatPoint = TPoint<float>;

template<typename TInType>
struct TVector
{
	using InType = TInType;

	InType X;
	InType Y;
	InType Z;

	TVector() = default;
	TVector(InType InX, InType InY, InType InZ)
		: X(InX)
		, Y(InY)
		, Z(InZ)
	{}
};

using FIntVector = TVector<int32>;
using FFloatVector = TVector<float>;

template<typename TInType>
struct TVector4
{
	using InType = TInType;

	InType X;
	InType Y;
	InType Z;
	InType W;

	TVector4() = default;
	TVector4(InType InX, InType InY, InType InZ, InType InW)
		: X(InX)
		, Y(InY)
		, Z(InZ)
		, W(InW)
	{
	}
};

using FFloatVector4 = TVector4<float>;


/// <summary>
/// replace with FIntPoint
/// </summary>
struct FInt2
{
	int X = 0;
	int Y = 0;
	FInt2() = default;
	FInt2(int x, int y) : X(x), Y(y) {}


};