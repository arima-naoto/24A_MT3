#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

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

	/// <summary>
	/// 1. X軸回転行列
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns></returns>
	Matrix4x4 MakeRotateXMatrix(float radian);

	/// <summary>
	/// 2. Y軸回転行列
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns></returns>
	Matrix4x4 MakeRotateYMatrix(float radian);

	/// <summary>
	/// 3. Z軸回転行列
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns></returns>
	Matrix4x4 MakeRotateZMatrix(float radian);

	/// <summary>
	/// 行列の積
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

#pragma endregion

public://メンバ変数

	Vector3 rotate_;

	Matrix4x4 rotateXMatrix_;
	Matrix4x4 rotateYMatrix_;
	Matrix4x4 rotateZMatrix_;

	Matrix4x4 rotateXYZMatrix_;

};

