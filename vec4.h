#include "types.h"
#include <iostream>
#include <smmintrin.h>
#include <cmath>

class vec4{
public:

	//CONSTRUCTORS
	vec4() : M128(_mm_set_ps(0,0,0,0)){}
	vec4(F32 X, F32 Y, F32 Z, F32 W) : M128(_mm_set_ps(W,Z,Y,X)){}
	vec4(F32 V) : M128(_mm_set_ps(V,V,V,V)){}

	//MEMBER ACCESS
	F32 x() const {return _mm_cvtss_f32(M128);}
	F32 y() const {return _mm_cvtss_f32(_mm_shuffle_ps(M128,M128, _MM_SHUFFLE(0, 0, 0, 1)));}
	F32 z() const {return _mm_cvtss_f32(_mm_shuffle_ps(M128,M128, _MM_SHUFFLE(0, 0, 0, 2)));}
	F32 w() const {return _mm_cvtss_f32(_mm_shuffle_ps(M128,M128, _MM_SHUFFLE(0, 0, 0, 3)));}

	//MATH OPERATIONS	
	vec4 operator + (const vec4& other) const {return vec4(_mm_add_ps(M128, other.M128));}
	vec4 operator - (const vec4& other) const {return vec4(_mm_sub_ps(M128, other.M128));}
	vec4 operator * (const vec4& other) const {return vec4(_mm_mul_ps(M128, other.M128));}
	vec4 operator / (const vec4& other) const {return vec4(_mm_div_ps(M128, other.M128));}
	
	//INCREMENTS
	vec4& operator += (const vec4& other) {M128 = _mm_add_ps(M128, other.M128);	return *this;}
	vec4& operator -= (const vec4& other) {M128 = _mm_sub_ps(M128, other.M128);	return *this;}
	vec4& operator *= (const vec4& other) {M128 = _mm_mul_ps(M128, other.M128);	return *this;}
	vec4& operator /= (const vec4& other) {M128 = _mm_div_ps(M128, other.M128);	return *this;}

	//VECTOR OPERATIONS
	F32 magnitude() const { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(M128,M128,0xFF)));}
	void normalize() { M128 = _mm_mul_ps(M128, _mm_rsqrt_ps(_mm_dp_ps(M128,M128,0xFF)));}
	vec4 normalized() const {return vec4(_mm_mul_ps(M128, _mm_rsqrt_ps(_mm_dp_ps(M128,M128,0xFF))));}
	F32 dot(const vec4& other) const {return _mm_cvtss_f32(_mm_dp_ps(M128,other.M128,0xF1));}
	

		
	//TO STRING
	friend std::ostream& operator<<(std::ostream& o, const vec4& v) {
			o << "x: " << v.x() << ", y: " << v.y() << ", z: " << v.z() << ", w: " << v.w();
			return o;
	}



private:
	__m128 M128;
	constexpr vec4(__m128 _M128) noexcept : M128(_M128){}



};