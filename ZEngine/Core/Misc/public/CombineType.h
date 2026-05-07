#pragma once
#include "PlatformTypeDef.h"

template<typename TIntType>
struct TIntPoint
{
	using IntType = TIntType;

	IntType X;
	IntType Y;

	TIntPoint() = default;
	TIntPoint(IntType InX, IntType InY)
		: X(InX)
		, Y(InY) 
	{}


};

using FIntPoint = TIntPoint<int32>;

template<typename TIntType>
struct TIntVector
{
	using IntType = TIntType;

	IntType X;
	IntType Y;
	IntType Z;

	TIntVector() = default;
	TIntVector(IntType InX, IntType InY, IntType InZ)
		: X(InX)
		, Y(InY)
		, Z(InZ)
	{}
};

using FIntVector = TIntVector<int32>;

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