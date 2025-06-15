#if !defined(TYPES_HEADER)
	#define TYPES_HEADER
	#include "libc.h"
	#include <limits>
	#include <complex>
	#include <type_traits>

	//
	// Immutable primitives:
	//

	using u8  = const uint8_t;
	using u16 = const uint16_t;
	using u32 = const uint32_t;
	using u64 = const uint64_t;

	using usize = const size_t;

	using s8  = const int8_t;
	using s16 = const int16_t;
	using s32 = const int32_t;
	using s64 = const int64_t;

	using f32  = const float;
	using f64  = const double;
	using f128 = const long double;

	using c32  = const std::complex<float>;
	using c64  = const std::complex<double>;
	using c128 = const std::complex<long double>;

	using c_str = const char*;

	using byte = u8;

	//
	// Mutable primitives:
	//

	template<typename T>
	using mut = typename std::remove_const<T>::type;

	//
	// Utils:
	//

	template<typename T>
	static constexpr bool as_bool(const T x)
	{
		return static_cast<bool>(x);
	}

	template<typename T>
	static constexpr u8 as_u8(const T x)
	{
		return static_cast<u8>(x);
	}

	template<typename T>
	static constexpr u16 as_u16(const T x)
	{
		return static_cast<u16>(x);
	}

	template<typename T>
	static constexpr u32 as_u32(const T x)
	{
		return static_cast<u32>(x);
	}

	template<typename T>
	static constexpr u64 as_u64(const T x)
	{
		return static_cast<u64>(x);
	}

	template<typename T>
	static constexpr usize as_usize(const T x)
	{
		return static_cast<usize>(x);
	}

	template<typename T>
	static constexpr s8 as_s8(const T x)
	{
		return static_cast<s8>(x);
	}

	template<typename T>
	static constexpr s16 as_s16(const T x)
	{
		return static_cast<s16>(x);
	}

	template<typename T>
	static constexpr s32 as_s32(const T x)
	{
		return static_cast<s32>(x);
	}

	template<typename T>
	static constexpr s64 as_s64(const T x)
	{
		return static_cast<s64>(x);
	}

	template<typename T>
	static constexpr char as_char(const T x)
	{
		return static_cast<char>(x);
	}

	template<typename T>
	static constexpr f32 as_f32(const T x)
	{
		return static_cast<f32>(x);
	}

	static inline f32 as_f32(c_str x)
	{
		return std::strtof(x, nullptr);
	}

	template<typename T>
	static constexpr f64 as_f64(const T x)
	{
		return static_cast<f64>(x);
	}

	static inline f64 as_f64(c_str x)
	{
		return std::strtod(x, nullptr);
	}

	template<typename T>
	static constexpr f128 as_f128(const T x)
	{
		return static_cast<f128>(x);
	}

	static inline f128 as_f128(c_str x)
	{
		return std::strtold(x, nullptr);
	}

	template<typename T>
	static constexpr c32 as_c32(const T re_x, const T im_x)
	{
		return c32(as_f32(re_x), as_f32(im_x));
	}

	template<typename T>
	static constexpr c64 as_c64(const T re_x, const T im_x)
	{
		return c64(as_f64(re_x), as_f64(im_x));
	}

	template<typename T>
	static constexpr c128 as_c128(const T re_x, const T im_x)
	{
		return c128(as_f128(re_x), as_f128(im_x));
	}

	template<typename T>
	static constexpr const void* as_void(const T *x_ptr)
	{
		return static_cast<const void*>(x_ptr);
	}

	template<typename T>
	static constexpr void* as_void(T *x_ptr)
	{
		return static_cast<void*>(x_ptr);
	}

	template<typename T>
	static constexpr std::uintptr_t as_address(const T &object)
	{
		return reinterpret_cast<std::uintptr_t>(&object);
	}

	template<typename T>
	static constexpr bool is_bool()
	{
		return std::is_same<T, bool>::value || std::is_same<T, const bool>::value;
	}

	template<typename T>
	static constexpr bool is_u8()
	{
		return std::is_same<T, u8>::value || std::is_same<T, mut<u8>>::value;
	}

	template<typename T>
	static constexpr bool is_u16()
	{
		return std::is_same<T, u16>::value || std::is_same<T, mut<u16>>::value;
	}

	template<typename T>
	static constexpr bool is_u32()
	{
		return std::is_same<T, u32>::value || std::is_same<T, mut<u32>>::value;
	}

	template<typename T>
	static constexpr bool is_u64()
	{
		return std::is_same<T, u64>::value || std::is_same<T, mut<u64>>::value;
	}

	template<typename T>
	static constexpr bool is_usize()
	{
		return std::is_same<T, usize>::value || std::is_same<T, mut<usize>>::value;
	}

	template<typename T>
	static constexpr bool is_s8()
	{
		return std::is_same<T, s8>::value || std::is_same<T, mut<s8>>::value;
	}

	template<typename T>
	static constexpr bool is_s16()
	{
		return std::is_same<T, s16>::value || std::is_same<T, mut<s16>>::value;
	}

	template<typename T>
	static constexpr bool is_s32()
	{
		return std::is_same<T, s32>::value || std::is_same<T, mut<s32>>::value;
	}

	template<typename T>
	static constexpr bool is_s64()
	{
		return std::is_same<T, s64>::value || std::is_same<T, mut<s64>>::value;
	}

	template<typename T>
	static constexpr bool is_f32()
	{
		return std::is_same<T, f32>::value || std::is_same<T, mut<f32>>::value;
	}

	template<typename T>
	static constexpr bool is_f64()
	{
		return std::is_same<T, f64>::value || std::is_same<T, mut<f64>>::value;
	}

	template<typename T>
	static constexpr bool is_f128()
	{
		return std::is_same<T, f128>::value || std::is_same<T, mut<f128>>::value;
	}

	template<typename T>
	static constexpr bool is_c32()
	{
		return std::is_same<T, c32>::value || std::is_same<T, mut<c32>>::value;
	}

	template<typename T>
	static constexpr bool is_c64()
	{
		return std::is_same<T, c64>::value || std::is_same<T, mut<c64>>::value;
	}

	template<typename T>
	static constexpr bool is_c128()
	{
		return std::is_same<T, c128>::value || std::is_same<T, mut<c128>>::value;
	}

	template<typename T>
	static constexpr bool is_char()
	{
		return std::is_same<T, char>::value || std::is_same<T, const char>::value;
	}

	template<typename T>
	static constexpr bool is_cstr()
	{
		return std::is_same<T, c_str>::value || std::is_same<T, char*>::value;
	}

	template<typename T>
	static constexpr bool is_void()
	{
		return std::is_same<T, void*>::value || std::is_same<T, const void*>::value;
	}

	template<typename T>
	static constexpr bool is_pointer()
	{
		return std::is_pointer<T>::value;
	}

	template<typename T>
	static constexpr bool is_array()
	{
		return std::is_array<T>::value;
	}

	template<typename T>
	static constexpr bool is_enum()
	{
		return std::is_enum<T>::value;
	}

	template<typename T>
	static constexpr bool is_class()
	{
		return std::is_class<T>::value;
	}

	template<typename T>
	static constexpr bool is_union()
	{
		return std::is_union<T>::value;
	}

	template<typename T>
	static constexpr bool is_primitive()
	{
		return (
		        is_bool<T>()
		     || is_u8<T>()
		     || is_u16<T>()
		     || is_u32<T>()
		     || is_u64<T>()
		     || is_usize<T>()
		     || is_s8<T>()
		     || is_s16<T>()
		     || is_s32<T>()
		     || is_s64<T>()
		     || is_f32<T>()
		     || is_f64<T>()
		     || is_f128<T>()
		     || is_c32<T>()
		     || is_c64<T>()
		     || is_c128<T>()
		     || is_cstr<T>()
		     || is_char<T>()
		     || is_void<T>()
		);
	}

	template<typename T>
	static constexpr bool is_integer()
	{
		return (
		        is_u8<T>()
		     || is_u16<T>()
		     || is_u32<T>()
		     || is_u64<T>()
		     || is_usize<T>()
		     || is_s8<T>()
		     || is_s16<T>()
		     || is_s32<T>()
		     || is_s64<T>()
		     || is_char<T>()
		);
	}

	template<typename T>
	static constexpr bool is_unsigned()
	{
		return (
		        is_u8<T>()
		     || is_u16<T>()
		     || is_u32<T>()
		     || is_u64<T>()
		     || is_usize<T>()
		);
	}

	template<typename T>
	static constexpr bool is_floating_point()
	{
		return (
		        is_f32<T>()
		     || is_f64<T>()
		     || is_f128<T>()
		     || is_c32<T>()
		     || is_c64<T>()
		     || is_c128<T>()
		);
	}

	template<typename T>
	static constexpr bool is_mut()
	{
		return is_primitive<T>() && (std::is_const<T>::value == false);
	}

	constexpr bool is_32bit = (sizeof(usize) == sizeof(u32));

	constexpr bool is_64bit = (sizeof(usize) == sizeof(u64));

	template<typename T>
	static constexpr c_str type_name()
	{
		if constexpr(is_bool<T>()) {
			return "bool\0";
		} else if constexpr(is_u8<T>()) {
			return "u8\0";
		} else if constexpr(is_u16<T>()) {
			return "u16\0";
		}  else if constexpr(is_u32<T>()) {
			return "u32\0";
		} else if constexpr(is_u64<T>()) {
			return "u64\0";
		} else if constexpr(is_usize<T>()) {
			return "usize\0";
		} else if constexpr(is_s8<T>()) {
			return "s8\0";
		} else if constexpr(is_s16<T>()) {
			return "s16\0";
		} else if constexpr(is_s32<T>()) {
			return "s32\0";
		} else if constexpr(is_s64<T>()) {
			return "s64\0";
		} else if constexpr(is_f32<T>()) {
			return "f32\0";
		} else if constexpr(is_f64<T>()) {
			return "f64\0";
		} else if constexpr(is_f128<T>()) {
			return "f128\0";
		} else if constexpr(is_c32<T>()) {
			return "c32\0";
		} else if constexpr(is_c64<T>()) {
			return "c64\0";
		} else if constexpr(is_c128<T>()) {
			return "c128\0";
		} else if constexpr(is_char<T>()) {
			return "char\0";
		} else if constexpr(is_cstr<T>()) {
			return "c_str\0";
		} else if constexpr(is_void<T>()) {
			return "void\0";
		} else {
			return "\0";
		}

		// NOTE: The Intel icpc compiler requires
		// yet another default return value here.
		return "\0";
	}

	template<typename T>
	static constexpr c_str type_fmt()
	{
		static_assert(is_primitive<T>());

		// NOTE: For the number of decimal digits used for f32, f64 and f128, see
		// the macros FLT_DIG, DBL_DIG and LDBL_DIG from the float.h header.

		if constexpr(is_u8<T>() || is_u16<T>() || is_u32<T>() || (is_usize<T>() && is_32bit)) {
			return "%*u";
		}

		if constexpr(is_s8<T>() || is_s16<T>() || is_s32<T>() || is_bool<T>()) {
			return "%*d";
		}

		if constexpr(is_u64<T>() || (is_usize<T>() && is_64bit)) {
			return "%*lu";
		}

		if constexpr(is_enum<T>()) {
			return "%*d";
		}

		if constexpr(is_s64<T>()) {
			return "%*ld";
		}

		if constexpr(is_f32<T>()) {
			return "%*.6E";
		}

		if constexpr(is_f64<T>()) {
			return "%*.15E";
		}

		if constexpr(is_f128<T>()) {
			return "%*.18Lf";
		}

		if constexpr(is_cstr<T>()) {
			return "%*s";
		}

		if constexpr(is_char<T>()) {
			return "%*c";
		}

		if constexpr(is_void<T>()) {
			return "%*p";
		}

		return "";
	}

	template<typename T>
	static inline void type_zeroed(T *object, usize count = 1u)
	{
		std::memset(as_void(object), 0, sizeof(T)*count);
	}

	template<typename T>
	static inline void type_zeroed(T &object)
	{
		type_zeroed(&object, 1u);
	}

	template<typename T>
	static inline T type_zeroed()
	{
		T object;
		type_zeroed(&object, 1u);
		return object;
	}

	//
	// Limits:
	//

	static constexpr u8 u8_min = std::numeric_limits<u8>::min();
	static constexpr u8 u8_max = std::numeric_limits<u8>::max();

	static constexpr u16 u16_min = std::numeric_limits<u16>::min();
	static constexpr u16 u16_max = std::numeric_limits<u16>::max();

	static constexpr u32 u32_min = std::numeric_limits<u32>::min();
	static constexpr u32 u32_max = std::numeric_limits<u32>::max();

	static constexpr u64 u64_min = std::numeric_limits<u64>::min();
	static constexpr u64 u64_max = std::numeric_limits<u64>::max();

	static constexpr usize usize_min = std::numeric_limits<usize>::min();
	static constexpr usize usize_max = std::numeric_limits<usize>::max();

	static constexpr s8 s8_min = std::numeric_limits<s8>::min();
	static constexpr s8 s8_max = std::numeric_limits<s8>::max();

	static constexpr s16 s16_min = std::numeric_limits<s16>::min();
	static constexpr s16 s16_max = std::numeric_limits<s16>::max();

	static constexpr s32 s32_min = std::numeric_limits<s32>::min();
	static constexpr s32 s32_max = std::numeric_limits<s32>::max();

	static constexpr s64 s64_min = std::numeric_limits<s64>::min();
	static constexpr s64 s64_max = std::numeric_limits<s64>::max();

	static constexpr f32 f32_min = std::numeric_limits<f32>::min();
	static constexpr f32 f32_max = std::numeric_limits<f32>::max();

	static constexpr f64 f64_min = std::numeric_limits<f64>::min();
	static constexpr f64 f64_max = std::numeric_limits<f64>::max();

	static constexpr f128 f128_min = std::numeric_limits<f128>::min();
	static constexpr f128 f128_max = std::numeric_limits<f128>::max();

	//
	// Auxiliary basic types:
	//

	template<typename T>
	using Target = typename std::remove_pointer<T>::type;

	enum class Primitive: u8 {
		type_u8,
		type_u16,
		type_u32,
		type_u64,
		type_s8,
		type_s16,
		type_s32,
		type_s64,
		type_f32,
		type_f64,
		type_f128,
		type_c32,
		type_c64,
		type_c128,
		type_bool,
		type_char,
		type_cstr,
		type_void,
		type_usize,
		type_unknown
	};

	template<typename T>
	static constexpr Primitive type_enum()
	{
		if constexpr(is_bool<T>()) {
			return Primitive::type_bool;
		} else if constexpr(is_u8<T>()) {
			return Primitive::type_u8;
		} else if constexpr(is_u16<T>()) {
			return Primitive::type_u16;
		}  else if constexpr(is_u32<T>()) {
			return Primitive::type_u32;
		} else if constexpr(is_u64<T>()) {
			return Primitive::type_u64;
		} else if constexpr(is_usize<T>()) {
			return Primitive::type_usize;
		} else if constexpr(is_s8<T>()) {
			return Primitive::type_s8;
		} else if constexpr(is_s16<T>()) {
			return Primitive::type_s16;
		} else if constexpr(is_s32<T>()) {
			return Primitive::type_s32;
		} else if constexpr(is_s64<T>()) {
			return Primitive::type_s64;
		} else if constexpr(is_f32<T>()) {
			return Primitive::type_f32;
		} else if constexpr(is_f64<T>()) {
			return Primitive::type_f64;
		} else if constexpr(is_f128<T>()) {
			return Primitive::type_f128;
		} else if constexpr(is_c32<T>()) {
			return Primitive::type_c32;
		} else if constexpr(is_c64<T>()) {
			return Primitive::type_c64;
		} else if constexpr(is_c128<T>()) {
			return Primitive::type_c128;
		} else if constexpr(is_char<T>()) {
			return Primitive::type_char;
		} else if constexpr(is_cstr<T>()) {
			return Primitive::type_cstr;
		} else if constexpr(is_void<T>()) {
			return Primitive::type_void;
		} else {
			return Primitive::type_unknown;
		}

		// NOTE: The Intel icpc compiler requires
		// yet another default return value here.
		return Primitive::type_unknown;
	}

	template<typename T = usize>
	struct Range {
		mut<T> min;
		mut<T> max;
		mut<T> step;

		constexpr Range(T start = static_cast<T>(0), T end = static_cast<T>(0), T step = static_cast<T>(1)):
			min(start), max(end), step(step)
		{
		}

		inline bool is_divided_evenly() const
		{
			// NOTE: As of C++17, std::remainder() is not a constexpr function.
			return std::remainder(this->max - this->min, this->step) == static_cast<T>(0);
		}

		inline usize count() const
		{
			if (this->step == static_cast<T>(0)) {
				return 0;
			} else {
				T count = (this->max - this->min)/this->step;
				return (this->is_divided_evenly()? as_usize(count) : as_usize(count) + 1u);
			}
		}

		constexpr Range<T> as_range_inclusive() const
		{
			return Range<T>(this->min, this->max + this->step, this->step);
		}

		constexpr bool operator==(const Range<T> &rhs) const
		{
			return (this->min == rhs.min) && (this->max == rhs.max) && (this->step == rhs.step);
		}

		constexpr T operator[](usize n) const
		{
			return this->min + static_cast<T>(n)*this->step;
		}

		// NOTE: The Range<T>::Iterator below only exists so that the compiler can
		// generate range-based for-loops from a Range<T>. It is not intended for
		// manual use outside this context.

		struct Iterator {
			mut<T> value;
			const Range<T> &owner;

			constexpr Iterator(const Range<T> &owner): value(owner.min), owner(owner)
			{
			}

			constexpr bool operator!=(const T rhs) const
			{
				// NOTE: The actual operation does not correspond the operator in
				// order to enforce that the compiler generates finite range-based
				// for-loops when T is an integer with step greater than 1 and also
				// floating-points. Here, rhs must be the output of Range<T>::end().
				return (this->value < rhs);
			}

			constexpr T operator*() const
			{
				return this->value;
			}

			constexpr void operator++()
			{
				this->value += this->owner.step;
			}
		};

		constexpr Range<T>::Iterator begin() const
		{
			return Range<T>::Iterator(*this);
		}

		constexpr T end() const
		{
			return this->max;
		}

		// In addition, it is often valuable that range-based for-loops from a
		// Range<T> can produce both the value of type T and its index. The pair
		// is wrapped in the type IndexedEntry below. Thus, instead of Range<T>,
		// a Range<IndexedEntry<I>> is used to build the iterator when calling
		// the Range<T>::indexed() member defined below. Where I is the integer
		// type.

		template<typename I = usize>
		struct IndexedEntry {
			mut<T> value;
			mut<I> index;

			constexpr IndexedEntry(T value, I index): value(value), index(index)
			{
			}

			constexpr bool operator<(const Range<T>::IndexedEntry<I> &rhs) const
			{
				// NOTE: Operation required exclusively by the operator != of
				// Range<U>::Iterator. Where U = Range<T>::IndexedEntry<I>.
				return (this->value < rhs.value);
			}

			constexpr void operator+=(const Range<T>::IndexedEntry<I> &rhs)
			{
				// NOTE: Operation required exclusively by the operator ++ of
				// Range<U>::Iterator. Where U = Range<T>::IndexedEntry<I>.
				this->index += rhs.index;
				this->value += rhs.value;
			}
		};

		template<typename I = usize>
		constexpr auto indexed() const
		{
			usize count = this->count();

			Range<T>::IndexedEntry<I> min(this->min, static_cast<I>(0));
			Range<T>::IndexedEntry<I> max(this->max, static_cast<I>(count));
			Range<T>::IndexedEntry<I> step(this->step, static_cast<I>(1));

			return Range<Range<T>::IndexedEntry<I>>(min, max, step);
		}
	};
#endif
