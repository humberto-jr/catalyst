#if !defined(TIMER_HEADER)
	#define TIMER_HEADER
	#include "essentials.h"
	#include <chrono>
	#include <thread>

	#if !defined(DEFAULT_TIMER_LENGTH)
		#define DEFAULT_TIMER_LENGTH 1024
	#endif

	static constexpr std::chrono::duration<mut<f64>> as_duration(f64 time_s)
	{
		return std::chrono::duration<mut<f64>>(time_s);
	}

	template<usize MAX_LEN = DEFAULT_TIMER_LENGTH>
	class Timer {
		public:
		inline Timer(): len(0), buf{as_duration(0.0)}
		{
			static_assert(MAX_LEN > 0);
		}

		inline usize capacity() const
		{
			return MAX_LEN;
		}

		inline usize count() const
		{
			return this->len;
		}

		inline void clear()
		{
			this->len = 0;
			this->buf[0] = as_duration(0.0);
		}

		inline void start()
		{
			this->begin = std::chrono::high_resolution_clock::now();
		}

		inline void stop()
		{
			const auto end = std::chrono::high_resolution_clock::now();
			this->buf[this->len] = end - this->begin;
			++this->len;
		}

		inline f64 first() const
		{
			return this->buf[0].count();
		}

		inline f64 last() const
		{
			assert(this->len > 0);
			return this->buf[this->len - 1].count();
		}

		f64 total() const
		{
			mut<f64> sum = 0.0;

			for (mut<usize> n = 0; n < this->len; ++n) {
				sum += this->buf[n].count();
			}

			return sum;
		}

		inline f64 average() const
		{
			return (this->len > 0? this->total()/as_f64(this->len) : 0.0);
		}

		inline void wait(f64 time_s) const
		{
			std::this_thread::sleep_for(as_duration(time_s));
		}

		inline f64 operator[](usize n) const
		{
			assert(n < this->len);
			return this->buf[n].count();
		}

		private:
		mut<usize> len;
		std::chrono::duration<mut<f64>> buf[MAX_LEN];
		std::chrono::time_point<std::chrono::high_resolution_clock> begin;
	};

	#undef DEFAULT_TIMER_LENGTH
#endif
