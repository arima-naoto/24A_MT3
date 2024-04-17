#pragma once
#include "Matrix4x4.h"

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
	/// 1. 行列の加法
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 2. 行列の減法
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 3. 行列の積
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 4. 逆行列
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	Matrix4x4 Inverse(const Matrix4x4& m);

	/// <summary>
	/// 5. 転置行列
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	Matrix4x4 Transpose(const Matrix4x4& m);

	/// <summary>
	/// 6. 単位行列
	/// </summary>
	/// <returns></returns>
	Matrix4x4 MakeIdentity4x4();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

#pragma endregion

public:

	Matrix4x4 m1_;
	Matrix4x4 m2_;

	Matrix4x4 resultAdd_;
	Matrix4x4 resultSubtract_;
	Matrix4x4 resultMultiply_;
	Matrix4x4 inverseM1_;
	Matrix4x4 inverseM2_;
	Matrix4x4 transposeM1_;
	Matrix4x4 transposeM2_;
	Matrix4x4 identity_;

};

