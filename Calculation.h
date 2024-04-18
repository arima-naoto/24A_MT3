#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

//アフィン構造体
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

	/// <summary>
	/// 行列の積
	/// </summary>
	/// <param name="m1">行列1</param>
	/// <param name="m2">行列2</param>
	/// <returns></returns>
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 拡大縮小行列
	/// </summary>
	/// <param name="scale">大きさ</param>
	/// <returns></returns>
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
	/// X軸回転行列
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns></returns>
	Matrix4x4 MakeRotateXMatrix(float radian);

	/// <summary>
	/// Y軸回転行列
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns></returns>
	Matrix4x4 MakeRotateYMatrix(float radian);

	/// <summary>
	/// Z軸回転行列
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns></returns>
	Matrix4x4 MakeRotateZMatrix(float radian);

	/// <summary>
	/// XYZ軸回転行列
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns></returns>
	Matrix4x4 MakeRotateXYZMatrix(const Vector3 &radian);

	/// <summary>
	/// 平行移動行列
	/// </summary>
	/// <param name="translate">座標</param>
	/// <returns></returns>
	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	/// <summary>
	/// アフィン変換行列
	/// </summary>
	/// <param name="affine">アフィン</param>
	/// <returns></returns>
	Matrix4x4 MakeAffineMatrix(Affine affine);

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

	Affine affine_;

	Matrix4x4 rotateXMatrix_;
	Matrix4x4 rotateYMatrix_;
	Matrix4x4 rotateZMatrix_;

	Matrix4x4 rotateXYZMatrix_;

	Matrix4x4 worldMatrix_;

};

