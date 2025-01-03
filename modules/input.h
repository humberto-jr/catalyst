#if !defined(INPUT_HEADER)
	#define INPUT_HEADER
	#include "essentials.h"
	#include "libtoml.h"
	#include "nist.h"
	#include <sstream>
	#include <iostream>
	#include <optional>

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

			const char *MAX_BUFFER_ADDR = &buf[LEN - 1];

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
		static String keyword(c_str key, c_str dummy = "\0")
		{
			c_str val = find_keyword_value<LEN>(key);

			if (val[0] == '\0') {
				return String(dummy);
			}

			return String(&val[0]);
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
		static nist::Isotope keyword(c_str key, nist::Isotope dummy)
		{
			c_str val = find_keyword_value<LEN>(key);

			if (val[0] == '\0') {
				return dummy;
			}

			return nist::isotope_enum(val);
		}

		static std::optional<usize> find_argument_position(s32 argc, char* argv[], const char flag, u8 index = 0)
		{
			if (argc < 2) {
				return {};
			}

			mut<s32> n = 1;
			s32 offset = as_s32(index);

			while ((n + offset) < argc) {
				if ((argv[n][0] == '-') && (std::strlen(argv[n]) > 1)) {
					if (argv[n][1] == flag) {
						return (n + offset);
					}
				}

				++n;
			}

			return {};
		}

		template<typename T>
		static T argument_line(s32 argc, char* argv[], const char flag, u8 index, T min, T max, T dummy)
		{
			auto pos = find_argument_position(argc, argv, flag, index);

			if (pos.has_value()) {
				usize n = pos.value();

				if ((argv[n][0] == '-')
				 && (argv[n][1] != '0')
				 && (argv[n][1] != '1')
				 && (argv[n][1] != '2')
				 && (argv[n][1] != '3')
				 && (argv[n][1] != '4')
				 && (argv[n][1] != '5')
				 && (argv[n][1] != '6')
				 && (argv[n][1] != '7')
				 && (argv[n][1] != '8')
				 && (argv[n][1] != '9')) {
				 	// NOTE: If the entry starts with minus and it is not followed by
				 	// digits, then this is likely another flag in an ill-formed line.
					print::error(WHERE, "Argument ", index, " of flag -", flag, " expected a ", type_name<T>(), " value but received \"", argv[n], "\"");
				}

				if ((argv[n][0] != '-')
				 && (argv[n][0] != '0')
				 && (argv[n][0] != '1')
				 && (argv[n][0] != '2')
				 && (argv[n][0] != '3')
				 && (argv[n][0] != '4')
				 && (argv[n][0] != '5')
				 && (argv[n][0] != '6')
				 && (argv[n][0] != '7')
				 && (argv[n][0] != '8')
				 && (argv[n][0] != '9')) {
				 	// NOTE: If the entry also starts with anything other than
				 	// digits, then this is an ill-formed argument line too.
					print::error(WHERE, "Argument ", index, " of flag -", flag, " expected a ", type_name<T>(), " value but received \"", argv[n], "\"");
				}

				// NOTE: See the note on the same cast used in the keyword<T>() function.
				T result = static_cast<T>(std::strtold(argv[n], nullptr));

				if (result < min) {
					return min;
				}

				if (result > max) {
					return max;
				}

				return result;
			} else {
				return dummy;
			}
		}

		[[maybe_unused]]
		static String argument_line(s32 argc, char* argv[], const char flag, u8 index, c_str dummy = "\0")
		{
			auto pos = find_argument_position(argc, argv, flag, index);

			if (pos.has_value()) {
				usize n = pos.value();

				return String(argv[n]);
			} else {
				return String(dummy);
			}
		}

		[[maybe_unused]]
		static inline bool argument_line(s32 argc, char* argv[], const char flag)
		{
			return find_argument_position(argc, argv, flag).has_value();
		}

		[[maybe_unused]]
		static nist::Isotope argument_line(s32 argc, char* argv[], const char flag, u8 index, nist::Isotope dummy)
		{
			auto pos = find_argument_position(argc, argv, flag, index);

			if (pos.has_value()) {
				usize n = pos.value();

				return nist::isotope_enum(argv[n]);
			} else {
				return dummy;
			}
		}

		static const toml::table& toml_table()
		{
			static toml::table input;
			static bool first_call = true;

			#pragma omp critical(first_call)
			if (first_call) {
				first_call = false;

				auto parsing = toml::parse(std::cin);

				if (parsing.failed()) {
					print::error(WHERE, "Unable to parse the standard input as a TOML configuration file");
				}

				input = std::move(parsing).table();
			}

			return input;
		}

		template<typename T>
		static T toml(c_str block, c_str key, T min, T max, T val)
		{
			static_assert(is_integer<T>() || is_floating_point<T>());

			auto node = input::toml_table()[block][key];

			if (node.type() == toml::node_type::none) {
				return val;
			}

			mut<T> entry = static_cast<T>(0);

			if constexpr(is_integer<T>()) {
				if (node.type() != toml::node_type::integer) {
					print::error(WHERE, "Expecting an integer value at ", block, '.', key);
				}

				entry = static_cast<T>(node.ref<s64>());
			}

			if constexpr(is_floating_point<T>()) {
				if (node.type() != toml::node_type::floating_point) {
					print::error(WHERE, "Expecting a floating point value at ", block, '.', key);
				}

				entry = static_cast<T>(node.ref<f64>());
			}

			if (entry < min) {
				return min;
			} else if (entry > max) {
				return max;
			} else {
				return entry;
			}
		}

		[[maybe_unused]]
		static bool toml(c_str block, c_str key, bool val)
		{
			auto node = input::toml_table()[block][key];

			if (node.type() == toml::node_type::none) {
				return val;
			}

			if (node.type() != toml::node_type::boolean) {
				print::error(WHERE, "Expecting a boolean value at ", block, '.', key);
			}

			return node.ref<bool>();
		}

		[[maybe_unused]]
		static String toml(c_str block, c_str key, c_str val)
		{
			auto node = input::toml_table()[block][key];

			if (node.type() == toml::node_type::none) {
				return String(val);
			}

			if (node.type() != toml::node_type::string) {
				print::error(WHERE, "Expecting a string at ", block, '.', key);
			}

			return String(node.ref<std::string>().c_str());
		}

		[[maybe_unused]]
		static nist::Isotope toml(c_str block, c_str key, nist::Isotope val)
		{
			auto node = input::toml_table()[block][key];

			if (node.type() == toml::node_type::none) {
				return val;
			}

			if (node.type() != toml::node_type::string) {
				print::error(WHERE, "Expecting an isotope symbol string at ", block, '.', key);
			}

			c_str symbol = node.ref<std::string>().c_str();

			return nist::isotope_enum(symbol);
		}
	}

	#undef MAX_INPUT_LENGTH
#endif
