#include <iostream>
#include <smmintrin.h>

class V4{
	using F = float;
	using M128 = __m128;
public:

	//CONSTRUCTORS
	V4(F X, F Y, F Z, F W) noexcept : R(SET4(W,Z,Y,X)){}
	V4(F V) noexcept : R(SET1(V)){}
	V4() noexcept : R(ZERO()){}
	V4(const V4& O) noexcept {R = O.R;}
	V4& operator = (const V4& O) noexcept {R = O.R;	return *this;}
	~V4() noexcept {}

	//MEMBERS ACCESS (faster without intrinsics)
	F x() const {return XYZW[0];}
	F y() const {return XYZW[1];}
	F z() const {return XYZW[2];}
	F w() const {return XYZW[3];}

	//MEMBERS SET (faster with intrinsics)
	void x(F V) { R = INSERT(R,SETFIRST(V), 0x00);}
	void y(F V) { R = INSERT(R,SETFIRST(V), 0x10);}
	void z(F V) { R = INSERT(R,SETFIRST(V), 0x20);}
	void w(F V) { R = INSERT(R,SETFIRST(V), 0x30);}

	//MATH OPERATIONS	
	V4 operator + (const V4& O) const {return V4(ADD(R, O.R));}
	V4 operator - (const V4& O) const {return V4(SUB(R, O.R));}
	V4 operator * (const V4& O) const {return V4(MUL(R, O.R));}
	V4 operator / (const V4& O) const {return V4(DIV(R, O.R));}
	
	//INCREMENTS
	V4& operator += (const V4& O) {R = ADD(R, O.R);	return *this;}
	V4& operator -= (const V4& O) {R = SUB(R, O.R);	return *this;}
	V4& operator *= (const V4& O) {R = MUL(R, O.R);	return *this;}
	V4& operator /= (const V4& O) {R = DIV(R, O.R);	return *this;}

	//SIGNS
	V4 operator + () const {return *this;}
	V4 operator - () const{	return XOR(SET1(-0.f),R);}

	//VECTOR OPERATIONS
	void clear() { R = ZERO();}
	F length3() const { return GETX(SQRT(DOT(R,R,0x77)));}
	F length4() const { return GETX(SQRT(DOT(R,R,0xFF)));}
	F length_sqr3() const { return GETX(DOT(R,R,0x77));}
	F length_sqr4() const { return GETX(DOT(R,R,0xFF));}
	void normalize3() { R = MUL(RSQRT(DOT(R,R,0x77)),R);}
	void normalize4() { R = MUL(RSQRT(DOT(R,R,0xFF)),R);}
	V4 normalized3() const {return V4(MUL(RSQRT(DOT(R,R,0x77)),R));}
	V4 normalized4() const {return V4(MUL(RSQRT(DOT(R,R,0xFF)),R));}
	F dot3(const V4& O) const {return GETX(DOT(R,O.R,0x71));}
	F dot4(const V4& O) const {return GETX(DOT(R,O.R,0xF1));}
	V4 cross(const V4& O) const {auto t = SUB(MUL(R,PERM(O.R,O.R,0xC9)),MUL(O.R,PERM(R,R,0xC9))); return PERM(t,t,0xC9); }

	//TO STRING
	friend std::ostream& operator<<(std::ostream& o, const V4& v) {
			o << "x: " << v.x() << ", y: " << v.y() << ", z: " << v.z() << ", w: " << v.w();
			return o;
	}

private:
	union{
		M128 R;
		F XYZW[4];
	};
	constexpr V4(M128 _R) noexcept : R(_R){}

	//Alias of function names, to make code cleaner
	static constexpr auto SETFIRST = _mm_set_ss;
	static constexpr auto SET1 = _mm_set1_ps;
	static constexpr auto SET4 = _mm_set_ps;
	static constexpr auto PERM = _mm_shuffle_ps;
	static constexpr auto GETX = _mm_cvtss_f32;
	static constexpr auto ADD = _mm_add_ps;
	static constexpr auto SUB = _mm_sub_ps;
	static constexpr auto MUL = _mm_mul_ps;
	static constexpr auto DIV = _mm_div_ps;
	static constexpr auto DOT = _mm_dp_ps;
	static constexpr auto SQRT = _mm_sqrt_ss;
	static constexpr auto RSQRT = _mm_rsqrt_ss;
	static constexpr auto XOR = _mm_xor_ps;
	static constexpr auto AND = _mm_and_ps;
	static constexpr auto OR = _mm_or_ps;
	static constexpr auto ZERO = _mm_setzero_ps;
	static constexpr auto INSERT = _mm_insert_ps;
};