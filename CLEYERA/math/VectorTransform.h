#pragma once
#include"Pch.h"

class VectorTransform
{
public:

	static float Length(const Vector3& v);

	static Vector3 Add(const Vector3& v1, const Vector3& v2);
	static Vector3 Subtruct(const Vector3& v1, const Vector3& v2);

	static Vector3 Multiply(const Vector3& v1, const float& v2);
	static Vector3 Multiply(const Vector3& v1, const Vector3& v2);

	static Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
	static Vector3 Normalize(const Vector3& v);
	static Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);
	static float Dot(const Vector3& v1, const Vector3& v2);

	template<typename T>
	static T Lerp(const T& a, const T& b, const float t) {
		return a + t * (b - a);
	}

	static Vector3 SlerpFanc(Vector3 start, Vector3 end, float t);

	static Vector4 Subtruct(const Vector4& v1, const Vector4& v2);

	static Vector3 Cross(const Vector3 v1, const Vector3 v2);

	static Vector3 TransformByMatrix(const Vector3 vector, const Matrix4x4 matrix);

	static Vector3 Catmull_Rom(Vector3& p0, Vector3& p1, Vector3& p2, Vector3& p3, float t);
	static float easeOutBounce(float t);

private:

};

