#include "types.h"
#include <iostream>
#include <emmintrin.h>

class vec4{
public:

	//CONSTRUCTORS
	constexpr vec4() noexcept{}
	constexpr vec4(F32 X, F32 Y, F32 Z, F32 W) noexcept : XYZW{X,Y,Z,W}{}
	constexpr vec4(F32 V) noexcept : XYZW{V,V,V,V}{}

	//MEMBER ACCESS
	constexpr F32 x() const noexcept {return XYZW[0];}
	constexpr F32 y() const noexcept {return XYZW[1];}
	constexpr F32 z() const noexcept {return XYZW[2];}
	constexpr F32 w() const noexcept {return XYZW[3];}

	//BASE MATH		
	vec4 operator + (const vec4& other) const{
		return vec4(_mm_add_ps(M128, other.M128));
	}
	vec4 operator - (const vec4& other) const{
		return vec4(_mm_sub_ps(M128, other.M128));
	}
	vec4 operator * (const vec4& other) const{
		return vec4(_mm_mul_ps(M128, other.M128));
	}
	vec4 operator / (const vec4& other) const{
		return vec4(_mm_div_ps(M128, other.M128));
	}
	
	
	//INCREMENTS
	vec4& operator += (const vec4& other){
		M128 = _mm_add_ps(M128, other.M128);
		return *this;
	}
	vec4& operator -= (const vec4& other){
		M128 = _mm_sub_ps(M128, other.M128);
		return *this;
	}
	vec4& operator *= (const vec4& other){
		M128 = _mm_mul_ps(M128, other.M128);
		return *this;
	}
	vec4& operator /= (const vec4& other){
		M128 = _mm_div_ps(M128, other.M128);
		return *this;
	}
		
	//TO STRING
	friend std::ostream& operator<<(std::ostream& o, const vec4& v) {
			o << "x: " << v.x() << ", y: " << v.y() << ", z: " << v.z() << ", w: " << v.w();
			return o;
	}



private:
	union{
		F32 XYZW[4] = {0};
		__m128 M128;
	};
	constexpr vec4(__m128 _M128) noexcept : M128(_M128){}



};