#include "Calculation.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

/// <summary>
/// 初期化処理
/// </summary>
Calculation::Calculation()
{
	m1_ = { 3.2f,0.7f,9.6f,4.4f,
			5.5f,1.3f,7.8f,2.1f,
			6.9f,8.0f,2.6f,1.0f,
			0.5f,7.2f,5.1f,3.3f,
	};

	m2_ = { 4.1f,6.5f,3.3f,2.2f,
			8.8f,0.6f,9.9f,7.7f,
			1.1f,5.5f,6.6f,0.0f,
			3.3f,9.9f,8.8f,2.2f,
	};

	resultAdd_ = {};
	resultSubtract_ = {};
	resultMultiply_ = {};
	inverseM1_ = {};
	inverseM2_ = {};
	transposeM1_ = {};
	transposeM2_ = {};
	identity_ = {};

}

void Calculation::MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	Novice::ScreenPrintf(x, y, label);

	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + 22 , "%6.02f", matrix.m[row][column]);
		}
	}
}

/// <summary>
/// 加法
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Calculation::Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 AddMatrix{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			AddMatrix.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return AddMatrix;
}

/// <summary>
/// 減法
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Calculation::Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 SubtractMatrix{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			SubtractMatrix.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return SubtractMatrix;
}

/// <summary>
/// 行列の積
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
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

/// <summary>
/// 逆行列
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4x4 Calculation::Inverse(const Matrix4x4& m)
{
#pragma region //4x4行列の行列式Aを求める
	float MatrixA = 1.0f / (m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -
		                    m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -
		                    m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +
		                    m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +
		                    m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -
		                    m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -
		                    m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +
		                    m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);
#pragma endregion

	Matrix4x4 result;
#pragma region 0行目の逆行列を求める

	result.m[0][0] = MatrixA * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] -
		m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);

	result.m[0][1] = MatrixA * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2] +
		m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);

	result.m[0][2] = MatrixA * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] -
		m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);

	result.m[0][3] = MatrixA * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2] +
		m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);

#pragma endregion

#pragma region 1行目の逆行列を求める

	result.m[1][0] = MatrixA * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2] +
		               m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);

	result.m[1][1] = MatrixA * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] -
		              m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);

	result.m[1][2] = MatrixA * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2] +
		               m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);

	result.m[1][3] = MatrixA * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] -
		              m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);

#pragma endregion

#pragma region 2行目の逆行列を求める

	result.m[2][0] = MatrixA * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] -
		              m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);

	result.m[2][1] = MatrixA * (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1] +
		               m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);

	result.m[2][2] = MatrixA * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] -
		              m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);

	result.m[2][3] = MatrixA * (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1] +
		               m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);

#pragma endregion

#pragma region 3行目の逆行列を求める

	result.m[3][0] = MatrixA * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1] +
		               m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);

	result.m[3][1] = MatrixA * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] -
		              m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);

	result.m[3][2] = MatrixA * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1] +
		               m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);

	result.m[3][3] = MatrixA * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] -
		              m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) ;
		               

#pragma endregion 

		return result;

}

/// <summary>
/// 転置行列
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4x4 Calculation::Transpose(const Matrix4x4& m)
{
	Matrix4x4 resultTranspose{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			resultTranspose.m[i][j] = m.m[j][i];
		}
	}

	return resultTranspose;
}

/// <summary>
/// 単位行列
/// </summary>
/// <returns></returns>
Matrix4x4 Calculation::MakeIdentity4x4()
{
	Matrix4x4 identityMatrix{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				identityMatrix.m[i][j] = 1.0f;
			}else
			{
				identityMatrix.m[i][j] = 0.0f;
			}
		}
	}

	return identityMatrix;
}

void Calculation::Update()
{
#pragma region 計算クラスのUpdate関数で行列の演算を行う

	resultAdd_ = Calculation::Add(m1_, m2_);
	resultSubtract_ = Calculation::Subtract(m1_, m2_);
	resultMultiply_ = Calculation::Multiply(m1_, m2_);
	inverseM1_ = Calculation::Inverse(m1_);
	inverseM2_ = Calculation::Inverse(m2_);
	transposeM1_ = Calculation::Transpose(m1_);
	transposeM2_ = Calculation::Transpose(m2_);
	identity_ = Calculation::MakeIdentity4x4();

#pragma endregion
}

void Calculation::Draw()
{
#pragma region //計算クラスのDraw関数で計算結果を表示する

	MatrixScreenPrintf(0, 0, resultAdd_,"Add");// 行列の加法
	MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract_,"Subtract");// 行列の減法
	MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMultiply_,"Multiply");// 行列の積
	MatrixScreenPrintf(0, kRowHeight * 5 * 3, inverseM1_,"inverseM1");// 逆行列1
	MatrixScreenPrintf(0, kRowHeight * 5 * 4, inverseM2_, "inverseM2");// 逆行列2
	MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1_,"transposeM1");// 転置行列1
	MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, transposeM2_,"transposeM2");// 転置行列2
	MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, identity_, "indentity");// 単位行列
#pragma endregion
}