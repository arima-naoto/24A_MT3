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

	rotate_ = { 0.4f,1.43f,-0.8f };

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
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + 40 , "%6.02f", matrix.m[row][column]);
		}
	}
}

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

Matrix4x4 Calculation::Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 MultiplyMatrix{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			MultiplyMatrix.m[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				MultiplyMatrix.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return MultiplyMatrix;
}

void Calculation::Update()
{
	rotateXMatrix_ = MakeRotateXMatrix(rotate_.x);
	rotateYMatrix_ = MakeRotateYMatrix(rotate_.y);
	rotateZMatrix_ = Calculation::MakeRotateZMatrix(rotate_.z);

	rotateXYZMatrix_ = Multiply(rotateXMatrix_, Multiply(rotateYMatrix_, rotateZMatrix_));
}

void Calculation::Draw()
{
	MatrixScreenPrintf(0, 0, rotateXMatrix_, "rotateXMatrix");
	MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix_, "rotateYMatrix");
	MatrixScreenPrintf(0, kRowHeight * 5 * 2, rotateZMatrix_, "rotateZMatrix");
	MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix_, "rotateXYZMatrix");
}