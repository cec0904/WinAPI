﻿#pragma once
#include "EngineMath.h"

struct FVector4D
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;

#pragma region Construction
	FVector4D()
	{
	}

	FVector4D(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	FVector4D(const FVector4D& _v)
		: x(_v.x), y(_v.y), z(_v.z), w(_v.w)
	{
	}

	FVector4D(FVector4D&& _v)
		: x(_v.x), y(_v.y), z(_v.z), w(_v.w)
	{
	}
#pragma endregion

#pragma region Equal

	const FVector4D& operator = (const FVector4D& _v)
	{
		x = _v.x;
		y = _v.y;
		z = _v.z;
		w = _v.w;
		return *this;
	}

	const FVector4D& operator = (float Value)
	{
		x = Value;
		y = Value;
		z = Value;
		w = Value;
		return *this;
	}
	const FVector4D& operator = (double Value)
	{
		x = (float)Value;
		y = (float)Value;
		z = (float)Value;
		w = (float)Value;
		return *this;
	}
	const FVector4D& operator = (int Value)
	{
		x = (int)Value;
		y = (int)Value;
		z = (int)Value;
		w = (int)Value;
		return *this;
	}
#pragma endregion 

#pragma region Plus
	FVector4D operator + (const FVector4D& _v)	const
	{
		FVector4D result;
		result.x = x + _v.x;
		result.y = y + _v.y;
		result.z = z + _v.z;
		result.w = w + _v.w;
		return result;
	}

	FVector4D operator + (float Value) const
	{
		FVector4D result;
		result.x = x + Value;
		result.y = y + Value;
		result.z = z + Value;
		result.w = w + Value;
		return result;
	}
	FVector4D operator + (double Value) const
	{
		FVector4D result;
		result.x = x + (float)Value;
		result.y = y + (float)Value;
		result.z = z + (float)Value;
		result.w = w + (float)Value;
		return result;
	}
	FVector4D operator + (int  Value) const
	{
		FVector4D result;
		result.x = x + (float)Value;
		result.y = y + (float)Value;
		result.z = z + (float)Value;
		result.w = w + (float)Value;
		return result;
	}

	// += 

	const FVector4D& operator += (const FVector4D& _v)
	{
		x += _v.x;
		y += _v.y;
		z += _v.z;
		w += _v.w;
		return *this;
	}

	const FVector4D& operator += (float Value)
	{
		x += Value;
		y += Value;
		z += Value;
		w += Value;
		return *this;
	}
	const FVector4D& operator += (double Value)
	{
		x += (float)Value;
		y += (float)Value;
		z += (float)Value;
		w += (float)Value;
		return *this;
	}
	const FVector4D& operator += (int Value)
	{
		x += (float)Value;
		y += (float)Value;
		z += (float)Value;
		w += (float)Value;
		return *this;
	}

	//++
	const FVector4D& operator ++ () //전위 
	{
		x += 1.f;
		y += 1.f;
		z += 1.f;
		w += 1.f;
		return *this;
	}

	const FVector4D& operator ++ (int) //후위
	{
		FVector4D temp = { x, y, z, w };
		x += 1.f;
		y += 1.f;
		z += 1.f;
		w += 1.f;
		return temp;
	}

#pragma endregion

#pragma region Minus

	FVector4D operator - (const FVector4D& _v)	const
	{
		FVector4D result;
		result.x = x - _v.x;
		result.y = y - _v.y;
		result.z = z - _v.z;
		result.w = w - _v.w;
		return result;
	}

	FVector4D operator - (float Value) const
	{
		FVector4D result;
		result.x = x - Value;
		result.y = y - Value;
		result.z = z - Value;
		result.w = w - Value;
		return result;
	}
	FVector4D operator - (double Value) const
	{
		FVector4D result;
		result.x = x - (float)Value;
		result.y = y - (float)Value;
		result.z = z - (float)Value;
		result.w = w - (float)Value;
		return result;
	}
	FVector4D operator - (int  Value) const
	{
		FVector4D result;
		result.x = x - (float)Value;
		result.y = y - (float)Value;
		result.z = z - (float)Value;
		result.w = w - (float)Value;
		return result;
	}

	// -= 

	const FVector4D& operator -= (const FVector4D& _v)
	{
		x -= _v.x;
		y -= _v.y;
		z -= _v.z;
		w -= _v.w;
		return *this;
	}

	const FVector4D& operator -= (float Value)
	{
		x -= Value;
		y -= Value;
		z -= Value;
		w -= Value;
		return *this;
	}
	const FVector4D& operator -= (double Value)
	{
		x -= (float)Value;
		y -= (float)Value;
		z -= (float)Value;
		w -= (float)Value;
		return *this;
	}
	const FVector4D& operator -= (int Value)
	{
		x -= (float)Value;
		y -= (float)Value;
		z -= (float)Value;
		w -= (float)Value;
		return *this;
	}

	//--
	const FVector4D& operator -- () //전위 
	{
		x -= 1.f;
		y -= 1.f;
		z -= 1.f;
		w -= 1.f;
		return *this;
	}

	const FVector4D& operator -- (int) //후위
	{
		FVector4D temp = { x, y, z, w };
		x -= 1.f;
		y -= 1.f;
		z -= 1.f;
		w -= 1.f;
		return temp;
	}
#pragma endregion

#pragma region Multiply
	FVector4D operator * (const FVector4D& _v)	const
	{
		FVector4D result;
		result.x = x * _v.x;
		result.y = y * _v.y;
		result.z = z * _v.z;
		result.w = w * _v.w;
		return result;
	}

	FVector4D operator * (float Value) const
	{
		FVector4D result;
		result.x = x * Value;
		result.y = y * Value;
		result.z = z * Value;
		result.w = w * Value;
		return result;
	}
	FVector4D operator * (double Value) const
	{
		FVector4D result;
		result.x = x * (float)Value;
		result.y = y * (float)Value;
		result.z = z * (float)Value;
		result.w = w * (float)Value;
		return result;
	}
	FVector4D operator * (int  Value) const
	{
		FVector4D result;
		result.x = x * (float)Value;
		result.y = y * (float)Value;
		result.z = z * (float)Value;
		result.w = w * (float)Value;
		return result;
	}

	// *= 

	const FVector4D& operator *= (const FVector4D& _v)
	{
		x *= _v.x;
		y *= _v.y;
		z *= _v.z;
		w *= _v.w;
		return *this;
	}

	const FVector4D& operator *= (float Value)
	{
		x *= Value;
		y *= Value;
		z *= Value;
		w *= Value;
		return *this;
	}
	const FVector4D& operator *= (double Value)
	{
		x *= (float)Value;
		y *= (float)Value;
		z *= (float)Value;
		w *= (float)Value;
		return *this;
	}
	const FVector4D& operator *= (int Value)
	{
		x *= (float)Value;
		y *= (float)Value;
		z *= (float)Value;
		w *= (float)Value;
		return *this;
	}
#pragma endregion

#pragma region Divide
	FVector4D operator / (const FVector4D& _v)	const
	{
		FVector4D result;
		result.x = x / _v.x;
		result.y = y / _v.y;
		result.z = z / _v.z;
		result.w = w / _v.w;
		return result;
	}

	FVector4D operator / (float Value) const
	{
		FVector4D result;
		result.x = x / Value;
		result.y = y / Value;
		result.z = z / Value;
		result.w = w / Value;
		return result;
	}
	FVector4D operator / (double Value) const
	{
		FVector4D result;
		result.x = x / (float)Value;
		result.y = y / (float)Value;
		result.z = z / (float)Value;
		result.w = w / (float)Value;
		return result;
	}
	FVector4D operator / (int  Value) const
	{
		FVector4D result;
		result.x = x / (float)Value;
		result.y = y / (float)Value;
		result.z = z / (float)Value;
		result.w = w / (float)Value;
		return result;
	}

	// /= 

	const FVector4D& operator /= (const FVector4D& _v)
	{
		x /= _v.x;
		y /= _v.y;
		z /= _v.z;
		w /= _v.w;
		return *this;
	}

	const FVector4D& operator /= (float Value)
	{
		x /= Value;
		y /= Value;
		z /= Value;
		w /= Value;
		return *this;
	}
	const FVector4D& operator /= (double Value)
	{
		x /= (float)Value;
		y /= (float)Value;
		z /= (float)Value;
		w /= (float)Value;
		return *this;
	}
	const FVector4D& operator /= (int Value)
	{
		x /= (float)Value;
		y /= (float)Value;
		z /= (float)Value;
		w /= (float)Value;
		return *this;
	}
#pragma endregion

	static FVector4D Black;
	static FVector4D White;
	static FVector4D Red;
	static FVector4D Green;
	static FVector4D Blue;
};