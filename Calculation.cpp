#include "Calculation.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

/// <summary>
/// 初期化処理
/// </summary>
Calculation::Calculation()
{
#pragma region //定義しなければならない
	v1_ = { 1.0f,3.0f,-5.0f };
	v2_ = { 4.0f,-1.0f,2.0f };
	k_ = { 4.0f };

	resultAdd_ = {};
	resultSubtract_ = {};
	resultMultiply_ = {};
	resultDot_ = {};
	resultLength_ = {};
	resultNormalize_ = {};
#pragma endregion
}

void Calculation::VectorScreenPrintf(int x,int y,const Vector3 &vector,const char *label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth , y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

Vector3 Calculation::Add(const Vector3& v1, const Vector3& v2)
{
    //足し算の計算結果を求める
	Vector3 resultAdd = { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
	return resultAdd;
}

Vector3 Calculation::Subtract(const Vector3& v1, const Vector3& v2)
{
    //引き算の計算結果を求める
	Vector3 resultSubtract = { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
	return resultSubtract;
}

Vector3 Calculation::Multiply(float scalar, const Vector3& v2)
{
    //乗算の計算結果を求める
	Vector3 resultMultiply = { scalar * v2.x ,scalar * v2.y,scalar * v2.z };
	return resultMultiply;

}

float Calculation::Dot(const Vector3& v1, const Vector3& v2)
{
#pragma region//内積を求める

	float resultDot = { v1.x * v2.x + v1.y * v2.y + v1.z * v2.z };

	return resultDot;
}

float Calculation::Length(const Vector3 &v)
{
	//長さを求める
	float result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}

Vector3 Calculation::Normalize(const Vector3& v)
{
	//正規化を使用して計算結果を求める
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	Vector3 resultNormalize = { v.x,v.y,v.z };

	if (length != 0.0f)
	{
		resultNormalize = { v.x / length,v.y / length,v.z / length };
	}
	return resultNormalize;
}

void Calculation::Update()
{
	resultAdd_ = Calculation::Add(v1_, v2_); //足し算
	resultSubtract_ = Calculation::Subtract(v1_, v2_);//引き算
	resultMultiply_ = Calculation::Multiply(k_, v1_);//スカラー倍
	resultDot_ = Calculation::Dot(v1_, v2_);//内積
	resultLength_ = Calculation::Length(v1_);//ノルム(長さ)
	resultNormalize_ = Calculation::Normalize(v2_);//正規化
}

void Calculation::Draw()
{
#pragma region 計算結果の表示を行う

	Calculation::VectorScreenPrintf(0, 0, resultAdd_, " : Add");
	Calculation::VectorScreenPrintf(0, kRowHeight, resultSubtract_, " : Subtract");
	Calculation::VectorScreenPrintf(0, kRowHeight * 2, resultMultiply_, " : Multiply");
	Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f : Dot", resultDot_);
	Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f : Lendth", resultLength_);
	Calculation::VectorScreenPrintf(0, kRowHeight * 5, resultNormalize_, " :  Normalize");

#pragma endregion
}