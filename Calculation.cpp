#include "Calculation.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>
using namespace std;

//文字列縦幅
static const int kRowHeight = 20;

//文字列横幅
static const int kColumnWidth = 60;

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="affine">アフィン構造体</param>
Calculation::Calculation(Affine affine)
{
#pragma region 定義しなければならない

	//アフィン構造体
	affine_ = affine;

	//X軸回転行列
	rotateXMatrix_ = {};
	
	//Y軸回転行列
	rotateYMatrix_ = {};
	
	//Z軸回転行列
	rotateZMatrix_ = {};

	//回転行列
	rotateMatrix_ = {};

	//ワールド行列
	worldMatrix_ = {};

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
/// <param name="m1">行列1</param>
/// <param name="m2">行列2</param>
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
/// X軸回転行列
/// </summary>
/// <param name="radian">角度</param>
/// <returns></returns>
Matrix4x4 Calculation::MakeRotateXMatrix(float radian)
{
	Matrix4x4 rotateXMatrix = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,cosf(radian),sinf(radian),0.0f,
		0.0f,-sinf(radian),cosf(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateXMatrix;
}

/// <summary>
/// Y軸回転行列
/// </summary>
/// <param name="radian">角度</param>
/// <returns></returns>
Matrix4x4 Calculation::MakeRotateYMatrix(float radian)
{
	Matrix4x4 rotateYMatrix = {
		cosf(radian),0.0f,-sinf(radian),0.0f,
		0.0f,1.0f,0.0f,0.0f,
		sinf(radian),0.0f,cosf(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateYMatrix;
}

/// <summary>
/// Z軸回転行列
/// </summary>
/// <param name="radian">角度</param>
/// <returns></returns>
Matrix4x4 Calculation::MakeRotateZMatrix(float radian)
{
	Matrix4x4 rotateZMatrix = {
		cosf(radian),sinf(radian),0.0f,0.0f,
		-sinf(radian),cosf(radian),0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateZMatrix;
}

/// <summary>
/// XYZ軸回転行列
/// </summary>
/// <param name="radian">角度</param>
/// <returns></returns>
Matrix4x4 Calculation::MakeRotateMatrix(const Vector3 &radian)
{
	//行列の積を使用し、X軸回転行列・Y軸回転行列・Z軸回転行列を結合する
	return Multiply(MakeRotateXMatrix(radian.x), Multiply(MakeRotateYMatrix(radian.y), MakeRotateZMatrix(radian.z)));
}

/// <summary>
/// 平行移動行列
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
/// アフィン変換行列
/// </summary>
/// <param name="affine">アフィン構造体</param>
/// <returns></returns>
Matrix4x4 Calculation::MakeAffineMatrix(Affine affine)
{
	//行列の積を使用し、拡大縮小行列・回転行列・平行移動行列を結合する
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

	//ワールド行列の演算結果表示
	Calculation::MatrixScreenPrintf(0, 0, worldMatrix_, "worldMatrix");

#pragma endregion
}