#if !defined(INPUT_HEADER)
	#define INPUT_HEADER
	#include "essentials.h"
	#include "nist.h"
	#include <sstream>
	#include <iostream>

	#if !defined(MAX_INPUT_LENGTH)
		#define MAX_INPUT_LENGTH 2048
	#endif

	namespace input {
		constexpr char LINE_FEED = '\n';

		constexpr char LINE_END = ';';

		constexpr char BLANK_SPACE = ' ';

		template<usize LEN>
		static c_str find_keyword_value(c_str key)
		{
			static bool first_call = true;

			// FIXME: This routine will need to re-read the std::cin many times,
			// but it can't be rewound, so we make our own backup at startup for
			// each LEN-dependent instantiation. However, this solution is not
			// thread-safe and should only be used in a sequential region. The
			// same issue is valid for the internal buffer holding the output.
			static std::stringstream backup;

			#pragma omp critical(first_call)
			if (first_call) {
				first_call = false;
				backup << std::cin.rdbuf();
			} else {
				backup.clear();
				backup.seekg(0);
			}

			static char buf[LEN] = {'\0'};

			constexpr char *MAX_BUFFER_ADDR = &buf[LEN - 1];

			while (backup.eof() == false) {
				backup.read(&buf[0], LEN);

				if (backup.gcount() == 0) {
					break;
				}

				char *start = std::strstr(&buf[0], key);

				if ((start != nullptr) && (start < MAX_BUFFER_ADDR)) {
					start = std::strstr(start, "=");

					if (start == nullptr) {
						break;
					} else {
						++start;
					}

					while ((*start == BLANK_SPACE) && (start < MAX_BUFFER_ADDR)) {
						++start;
					}

					char *end = start;

					while ((*end != LINE_FEED) && (*end != LINE_END) && (*end != BLANK_SPACE) && (end < MAX_BUFFER_ADDR)) {
						++end;
					}

					*end = '\0';
					return start;
				}
			}

			return "\0";
		}

		template<typename T, usize LEN = MAX_INPUT_LENGTH>
		static T keyword(c_str key, T min, T max, T dummy)
		{
			c_str val = find_keyword_value<LEN>(key);

			if (val[0] == '\0') {
				return dummy;
			}

			// NOTE: We interpret the string as f128 in order to preserve high
			// accuracy, if any. Then, we cast the result to a lower precision
			// type or integer, if that is the case.
			T result = static_cast<T>(std::strtold(val, nullptr));

			if (result < min) {
				return min;
			}

			if (result > max) {
				return max;
			}

			return result;
		}

		template<usize LEN = MAX_INPUT_LENGTH>
		static string keyword(c_str key, c_str dummy = "\0")
		{
			c_str val = find_keyword_value<LEN>(key);

			if (val[0] == '\0') {
				return string(dummy);
			}

			return string(&val[0]);
		}

		template<usize LEN = MAX_INPUT_LENGTH>
		static bool keyword(c_str key, bool dummy)
		{
			c_str val = find_keyword_value<LEN>(key);

			if (val[0] == '\0') {
				return dummy;
			}

			bool is_true = std::strcmp(val, "true\0") == 0 || std::strcmp(val, "yes\0") == 0;

			return is_true;
		}

		template<usize LEN = MAX_INPUT_LENGTH>
		static nist::isotope keyword(c_str key, nist::isotope dummy)
		{
			c_str val = find_keyword_value<LEN>(key);

			if (val[0] == '\0') {
				return dummy;
			}

			return nist::isotope_enum(val);
		}
	}

	#undef MAX_INPUT_LENGTH
#endif
