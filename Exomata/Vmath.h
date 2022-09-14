#pragma once

namespace Framework
{
	Vector_2D::Vector_2D() : vector{ 0,0 } ///defualt cotr
	{

	}

	Vector_2D::Vector_2D(float _x, float _y) : value{ _x, _y }///para ctor
	{
	}

	//operators
	Vector_2D Vector_2D::operator += (const Vector_2D& rhs) ///function to add vector together
	{
		value.x += rhs.value.x;
		value.y += rhs.value.y;

		return *this;
	}


	Vector_2D Vector_2D::operator -= (const Vector_2D& rhs)/// function to subtract vectors
	{
		{
			value.x -= rhs.value.x;
			value.y -= rhs.value.y;

			return *this;
		}
	}
	Vector_2D  Vector_2D::operator *= (const Vector_2D& rhs) ///function to multiply vectors
	{
		value.x *= rhs.value.x;
		value.y *= rhs.value.y;

		return *this;
	}
	Vector_2D  Vector_2D::operator /= (const Vector_2D& rhs) ///functions to divide vectors
	{
		value.x /= rhs.value.x;
		value.y /= rhs.value.y;

		return *this;
	}

	Vector_2D  Vector_2D::operator -() const /// function to make vector into negative
	{
		return Vector_2D(-value.x, -value.y);
	}

	Vector_2D operator + (const Vector_2D& lhs, const Vector_2D& rhs)///adding 2 vector together
	{
		return Vector_2D(lhs.value.x + rhs.value.x, lhs.value.y + rhs.value.y);// return a vector created by the elements from computing the sum of each individual elements of the vector

	}
	Vector_2D operator - (const Vector_2D& lhs, const Vector_2D& rhs) ///subtractiong 2 vector
	{
		return Vector_2D(lhs.value.x - rhs.value.x, lhs.value.y - rhs.value.y);//return a vector created by the elements from computing the diffrence of each
	}

	Vector_2D operator * (const Vector_2D& lhs, float rhs) ///multiplying 2 vector
	{
		return Vector_2D(lhs.value.x * rhs, lhs.value.y * rhs);//return a vector created by the elements that result from the multiplication of the lhs vector 
												  // and the rhs float
	}

	Vector_2D operator*(float lhs, const Vector_2D& rhs) ///multiplying a vector with a float
	{
		return Vector_2D(rhs.value.x * lhs, rhs.value.y * lhs);//return a vector created by the elements that result from the multiplication of the rhs vector 
												  // and the lhs float
	}

	Vector_2D operator / (const Vector_2D& lhs, float rhs) ///dividing a float from a vector
	{
		return Vector_2D(lhs.value.x / rhs, lhs.value.y / rhs);//return a vector created by the elements that result from the division of the lhs vector with the rhs float
	}

	// Tool functions
	void Vec2Set(Vec2& curr, float x_, float y_) ///set value for current vector
	{
		curr.value.x = x_;
		curr.value.y = y_;
	}


	void Normalize(Vector_2D& result, const Vector_2D Vec0)///normaize the current vector
	{
		float mag = sqrtf((Vec0.value.x * Vec0.value.x) + (Vec0.value.y * Vec0.value.y));
		result.value.x = Vec0.value.x / mag;
		result.value.y = Vec0.value.y / mag;
	}//normalize the vector

	float length(const Vector_2D& Vec0) ///calculate the length of the vector
	{
		return (float)(sqrt(powf(Vec0.value.x, 2.0f) + powf(Vec0.value.y, 2.0f)));
	}

	float squarelength(const Vector_2D& Vec0) ///calculate the square length of the vector 
	{
		return (float)(powf(Vec0.value.x, 2.0f) + powf(Vec0.value.y, 2.0f));
	}

	float distance(const Vector_2D& vec_p0, const Vector_2D& vec_p1) ///find the distance between 2 point
	{
		Vector_2D temp = vec_p1 - vec_p0;//find the vector between the 2 point

		return length(temp);//return the result after running the temp value through Vector2DLength();
	}

	float squaredistance(const Vector_2D& vec_p0, const Vector_2D& vec_p1) ///find the square distance between 2 point
	{
		Vector_2D temp = vec_p1 - vec_p0;//find the vector between the 2 point

		return length(temp);//return the result after running the temp value through Vector2DLength();

	}

	float dotProduct(const Vector_2D& Vec0, const Vector_2D& Vec1) ///calculate the dot product of 2 vectors
	{
		return (Vec0.value.x * Vec1.value.x + Vec0.value.y * Vec1.value.y);
	}

	float crossproduct(const Vector_2D& Vec0, const Vector_2D& Vec1) ///calculate the cross product between 2 vectors
	{
		return (Vec0.value.x * Vec1.value.y - Vec0.value.y * Vec1.value.x);
	}
}