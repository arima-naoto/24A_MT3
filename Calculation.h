#pragma once
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
	/// 3次元ベクトルの計算結果表示用
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="vector"></param>
	/// <param name="label"></param>
	void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

	/// <summary>
	/// 加算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector3 Add(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 減算
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector3 Subtract(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// スカラー倍
	/// </summary>
	/// <param name="scalar"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	Vector3 Multiply(float scalar, const Vector3& v2);

	/// <summary>
	/// 内積
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	float Dot(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// ノルム(長さ)
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	float Length(const Vector3& v);

	/// <summary>
	/// 正規化
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	Vector3 Normalize(const Vector3& v);

	/// <summary>
	/// 更新処理用
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理用
	/// </summary>
	void Draw();

public:

	Vector3 v1_;
	Vector3 v2_;
	float k_;

	Vector3 resultAdd_;
	Vector3 resultSubtract_;
	Vector3 resultMultiply_;
	float resultDot_;
	float resultLength_;
	Vector3 resultNormalize_;

};

