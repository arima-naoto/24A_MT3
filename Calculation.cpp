#include "Calculation.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

/// <summary>
/// 初期化処理
/// </summary>
Calculation::Calculation()
{
#pragma region 定義しなければならない

	translate_ = { 4.1f,2.6f,0.8f };
	scale_ = { 1.5f,5.2f,7.3f };
	point_ = { 2.3f,3.8f,1.4f };
	transformed_ = {};

	translateMatrix_ = {};
	scaleMatrix_ = {};
	transformMatrix_ = {
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f,
	};

#pragma endregion
}

/// <summary>
/// 3次元ベクトルの数値表示
/// </summary>
/// <param name="x">座標X</param>
/// <param name="y">座標Y</param>
/// <param name="vector">3次元ベクトル</param>
/// <param name="label">文字列</param>
void Calculation::VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

/// <summary>
/// 4x4行列の数値表示
/// </summary>
/// <param name="x">座標X</param>
/// <param name="y">座標Y</param>
/// <param name="matrix">4x4行列</param>
/// <param name="label">文字列</param>
void Calculation::MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	Novice::ScreenPrintf(x, y + 20 , label);

	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + 40 , "%6.02f", matrix.m[row][column]);
		}
	}
}

/// <summary>
/// 1. 平行移動行列
/// </summary>
/// <param name="translate">座標</param>
/// <returns></returns>
Matrix4x4 Calculation::MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 resultTranslate = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		translate.x,translate.y,translate.z,1.0f
	};

	return resultTranslate;
}

/// <summary>
/// 2. 拡大縮小行列
/// </summary>
/// <param name="scale">大きさ</param>
/// <returns></returns>
Matrix4x4 Calculation::MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 resultScale = {
		scale.x,0.0f,0.0f,0.0f,
		0.0f,scale.y,0.0f,0.0f,
		0.0f,0.0f,scale.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return resultScale;
}

/// <summary>
/// 3. 座標変換
/// </summary>
/// <param name="vector">3次元ベクトル</param>
/// <param name="matrix">4x4行列</param>
/// <returns></returns>
Vector3 Calculation::Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +  matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +  matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +  matrix.m[3][2];
	float w =  vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +  matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
} 

void Calculation::Update()
{
#pragma region 計算クラスのUpdateで演算を行う

	translateMatrix_ = MakeTranslateMatrix(translate_);
	scaleMatrix_ = MakeScaleMatrix(scale_);
	transformed_ = Transform(point_, transformMatrix_);

#pragma endregion
}

void Calculation::Draw()
{
#pragma region 計算クラスのDrawで計算結果の数値を描画する

	VectorScreenPrintf(0, 0, transformed_, "transformed");
	MatrixScreenPrintf(0, 0, translateMatrix_, "translateMatrix");
	MatrixScreenPrintf(0, kRowHeight * 5, scaleMatrix_, "scaleMatrix");

#pragma endregion
}