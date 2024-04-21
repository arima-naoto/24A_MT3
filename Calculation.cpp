#include "Calculation.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;



/// <summary>
/// 初期化処理
/// </summary>
Calculation::Calculation()
{
#pragma region 定義しなければならない

	affine_ = {
		{ 1.2f,0.79f,-2.1f },
		{ 0.4f,1.43f,-0.8f },
		{ 2.7f,-4.15f,1.57f }
	};

	rotateXMatrix_ = {};
	rotateYMatrix_ = {};
	rotateZMatrix_ = {};

	rotateXYZMatrix_ = {};

#pragma endregion
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
	Novice::ScreenPrintf(x, y , label);

	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + 20 , "%6.02f", matrix.m[row][column]);
		}
	}
}

/// <summary>
/// 行列の積
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Calculation::Multiply(const Matrix4x4 &m1,const Matrix4x4 &m2)
{
	Matrix4x4 MultiplyMatrix{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			MultiplyMatrix.m[i][j] = 0;
			for(int k = 0; k < 4; k++)
			{
				MultiplyMatrix.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return MultiplyMatrix;
}

/// <summary>
/// 拡大縮小行列
/// </summary>
/// <param name="scale"></param>
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
/// X軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 Calculation::MakeRotateXMatrix(float radian)
{
	Matrix4x4 rotateXMatrix = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,std::cos(radian),std::sin(radian),0.0f,
		0.0f,-std::sin(radian),std::cos(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateXMatrix;
}

/// <summary>
/// Y軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 Calculation::MakeRotateYMatrix(float radian)
{
	Matrix4x4 rotateYMatrix = {
		std::cos(radian),0.0f,-std::sin(radian),0.0f,
		0.0f,1.0f,0.0f,0.0f,
		std::sin(radian),0.0f,std::cos(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateYMatrix;
}

/// <summary>
/// Z軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 Calculation::MakeRotateZMatrix(float radian)
{
	Matrix4x4 rotateZMatrix = {
		std::cos(radian),std::sin(radian),0.0f,0.0f,
		-std::sin(radian),std::cos(radian),0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateZMatrix;
}

/// <summary>
/// XYZ軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 Calculation::MakeRotateMatrix(const Vector3 &radian)
{
	return Multiply(MakeRotateXMatrix(radian.x), Multiply(MakeRotateYMatrix(radian.y), MakeRotateZMatrix(radian.z)));
}

/// <summary>
/// 平行移動行列
/// </summary>
/// <param name="translate"></param>
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
/// アフィン変換行列
/// </summary>
/// <param name="affine"></param>
/// <returns></returns>
Matrix4x4 Calculation::MakeAffineMatrix(Affine affine)
{
	return Multiply(Multiply(MakeScaleMatrix(affine.scale),MakeRotateMatrix(affine.rotate)),MakeTranslateMatrix(affine.translate));
}

/// <summary>
/// 更新処理
/// </summary>
void Calculation::Update()
{
#pragma region アフィン変換処理

	worldMatrix_ = Calculation::MakeAffineMatrix(affine_);

#pragma endregion
}

/// <summary>
/// 描画処理
/// </summary>
void Calculation::Draw()
{
#pragma region 計算結果の表示

	Calculation::MatrixScreenPrintf(0, 0, worldMatrix_, "worldMatrix");

#pragma endregion
}