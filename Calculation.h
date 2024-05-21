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
	/// 3次元ベクトルの数値表示
	/// </summary>
	void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

	/// <summary>
	/// 4x4行列の数値表示
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="matrix"></param>
	void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix,const char *label);

#pragma region //4x4行列関数の作成

	/// <summary>
	/// 1. 平行移動行列
	/// </summary>
	/// <param name="translate"></param>
	/// <returns></returns>
	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	/// <summary>
	/// 2. 拡大縮小行列
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
	/// 3. 座標変換
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

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

	//座標
	Vector3 translate_;

	//倍率
	Vector3 scale_;

	//ポイント
	Vector3 point_;

	//トランスフォーム
	Vector3 transformed_;

	//平行移動行列
	Matrix4x4 translateMatrix_;

	//拡大拡縮行列
	Matrix4x4 scaleMatrix_;

	//座標変換行列
	Matrix4x4 transformMatrix_;

};

