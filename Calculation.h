#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

struct Affine
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

/// <summary>
/// 計算クラスの宣言
/// </summary>
class Calculation
{
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Calculation();

	/// <summary>
	/// 4x4行列の数値表示
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="matrix"></param>
	void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix,const char *label);

#pragma region //4x4行列関数の作成

	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	Matrix4x4 MakeRotateXMatrix(float radian);

	Matrix4x4 MakeRotateYMatrix(float radian);

	Matrix4x4 MakeRotateZMatrix(float radian);

	Matrix4x4 MakeRotateXYZMatrix(const Vector3 &radian);

	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	Matrix4x4 MakeAffineMatrix(Affine affine);

	void Update();

	void Draw();

#pragma endregion

public://メンバ変数

	Affine affine_;

	Matrix4x4 rotateXMatrix_;
	Matrix4x4 rotateYMatrix_;
	Matrix4x4 rotateZMatrix_;

	Matrix4x4 rotateXYZMatrix_;

	Matrix4x4 worldMatrix_;

};

