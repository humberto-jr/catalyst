#if !defined(LIBTOML_HEADER)
	#define LIBTOML_HEADER
	#include "essentials.h"
	#include "libmpi.h"
	#include "file.h"
	#include "nist.h"
	#include "pes.h"
	#include <iostream>

	#define TOML_EXCEPTIONS 0

	#define TOML_ENABLE_FORMATTERS 1

	#define TOML_ASSERT(expr)                                    \
	{                                                            \
	  if (!(expr)) {                                             \
	    print::error(WHERE, "toml++ assertion failed: ", #expr); \
	  }                                                          \
	}

	// NOTE: The toml namespace is now available. The toml++ documentation can
	// be found at https://marzer.github.io/tomlplusplus/namespacetoml.html
	#include "../vendors/toml.hpp"

	namespace toml {
		class Cin {
			public:
			Cin(bool verbose = true)
			{
				// NOTE: Since the MPI runtime redirects the stdin to rank 0 only, the methods below will allow the
				// MPI frontend object to broadcast the TOML configuration entries to other ranks. A raw pointer of
				// the frontend is used instead of a reference so as not to duplicate each version of these methods
				// unnecessarily. All the logic is handled at runtime, but since we are reading files and sending
				// data over a network, any extra time added due to the use of raw pointers is likely meaningless.
				auto parsing = toml::parse(std::cin);

				if (parsing.failed()) {
					print::error(WHERE, "Unable to parse the standard input as a TOML configuration file");
				}

				this->input = std::move(parsing).table();

				if (verbose) {
					std::cout << this->input << "\n";
				}
			}

			#define MEMBER_VALUE_IMPL(type)                                                                             \
			inline type value(c_str block0, type dummy, mpi::Frontend *mpi = nullptr) const                             \
			{                                                                                                           \
				return this->node_value<type>(block0, dummy, mpi);                                                      \
			}                                                                                                           \
			                                                                                                            \
			inline type value(c_str block0, c_str block1, type dummy, mpi::Frontend *mpi = nullptr) const               \
			{                                                                                                           \
				return this->node_value<type>(block0, block1, dummy, mpi);                                              \
			}                                                                                                           \
			                                                                                                            \
			inline type value(c_str block0, c_str block1, c_str block2, type dummy, mpi::Frontend *mpi = nullptr) const \
			{                                                                                                           \
				return this->node_value<type>(block0, block1, block2, dummy, mpi);                                      \
			}

			MEMBER_VALUE_IMPL(bool)
			MEMBER_VALUE_IMPL(u8)
			MEMBER_VALUE_IMPL(u16)
			MEMBER_VALUE_IMPL(u32)
			MEMBER_VALUE_IMPL(u64)
			MEMBER_VALUE_IMPL(s8)
			MEMBER_VALUE_IMPL(s16)
			MEMBER_VALUE_IMPL(s32)
			MEMBER_VALUE_IMPL(s64)
			MEMBER_VALUE_IMPL(f32)
			MEMBER_VALUE_IMPL(f64)

			#undef MEMBER_VALUE_IMPL

			// NOTE: Below, if type is unsigned and any of min, max, or entry were negative,
			// they are overflown in here and may cause bugs. See more cases below.

			#define MEMBER_VALUE_IMPL(type)                                                                                          \
			type value(c_str block0, type min, type max, type dummy, mpi::Frontend *mpi = nullptr) const                             \
			{                                                                                                                        \
				type entry = this->value(block0, dummy, mpi);                                                                        \
				                                                                                                                     \
				if (entry < min) {                                                                                                   \
					return min;                                                                                                      \
				} else if (entry > max) {                                                                                            \
					return max;                                                                                                      \
				} else {                                                                                                             \
					return entry;                                                                                                    \
				}                                                                                                                    \
			}                                                                                                                        \
                                                                                                                                     \
			type value(c_str block0, c_str block1, type min, type max, type dummy, mpi::Frontend *mpi = nullptr) const               \
			{                                                                                                                        \
				type entry = this->value(block0, block1, dummy, mpi);                                                                \
				                                                                                                                     \
				if (entry < min) {                                                                                                   \
					return min;                                                                                                      \
				} else if (entry > max) {                                                                                            \
					return max;                                                                                                      \
				} else {                                                                                                             \
					return entry;                                                                                                    \
				}                                                                                                                    \
			}                                                                                                                        \
                                                                                                                                     \
			type value(c_str block0, c_str block1, c_str block2, type min, type max, type dummy, mpi::Frontend *mpi = nullptr) const \
			{                                                                                                                        \
				type entry = this->value(block0, block1, block2, dummy, mpi);                                                        \
				                                                                                                                     \
				if (entry < min) {                                                                                                   \
					return min;                                                                                                      \
				} else if (entry > max) {                                                                                            \
					return max;                                                                                                      \
				} else {                                                                                                             \
					return entry;                                                                                                    \
				}                                                                                                                    \
			}

			MEMBER_VALUE_IMPL(u8)
			MEMBER_VALUE_IMPL(u16)
			MEMBER_VALUE_IMPL(u32)
			MEMBER_VALUE_IMPL(u64)
			MEMBER_VALUE_IMPL(s8)
			MEMBER_VALUE_IMPL(s16)
			MEMBER_VALUE_IMPL(s32)
			MEMBER_VALUE_IMPL(s64)
			MEMBER_VALUE_IMPL(f32)
			MEMBER_VALUE_IMPL(f64)

			#undef MEMBER_VALUE_IMPL

			c_str string(c_str block0, c_str dummy) const
			{
				auto node = this->input[block0];

				if (node.type() == toml::node_type::none) {
					return dummy;
				}

				if (node.type() != toml::node_type::string) {
					print::error(WHERE, "Expecting a string at ", block0);
				}

				return node.ref<std::string>().c_str();
			}

			c_str string(c_str block0, c_str block1, c_str dummy) const
			{
				auto node = this->input[block0][block1];

				if (node.type() == toml::node_type::none) {
					return dummy;
				}

				if (node.type() != toml::node_type::string) {
					print::error(WHERE, "Expecting a string at ", block0, '.', block1);
				}

				return node.ref<std::string>().c_str();
			}

			c_str string(c_str block0, c_str block1, c_str block2, c_str dummy) const
			{
				auto node = this->input[block0][block1][block2];

				if (node.type() == toml::node_type::none) {
					return dummy;
				}

				if (node.type() != toml::node_type::string) {
					print::error(WHERE, "Expecting a string at ", block0, '.', block1, '.', block2);
				}

				return node.ref<std::string>().c_str();
			}

			nist::Isotope isotope(c_str block0, nist::Isotope dummy = nist::Isotope::atom_unknown) const
			{
				auto node = this->input[block0];

				if (node.type() == toml::node_type::none) {
					return dummy;
				}

				if (node.type() != toml::node_type::string) {
					print::error(WHERE, "Expecting an isotope symbol string at ", block0);
				}

				c_str symbol = node.ref<std::string>().c_str();

				return nist::isotope_enum(symbol);
			}

			nist::Isotope isotope(c_str block0, c_str block1, nist::Isotope dummy = nist::Isotope::atom_unknown) const
			{
				auto node = this->input[block0][block1];

				if (node.type() == toml::node_type::none) {
					return dummy;
				}

				if (node.type() != toml::node_type::string) {
					print::error(WHERE, "Expecting an isotope symbol string at ", block0, '.', block1);
				}

				c_str symbol = node.ref<std::string>().c_str();

				return nist::isotope_enum(symbol);
			}

			nist::Isotope isotope(c_str block0, c_str block1, c_str block2, nist::Isotope dummy = nist::Isotope::atom_unknown) const
			{
				auto node = this->input[block0][block1][block2];

				if (node.type() == toml::node_type::none) {
					return dummy;
				}

				if (node.type() != toml::node_type::string) {
					print::error(WHERE, "Expecting an isotope symbol string at ", block0, '.', block1, '.', block2);
				}

				c_str symbol = node.ref<std::string>().c_str();

				return nist::isotope_enum(symbol);
			}

			inline file::Output output_filename(c_str block0, c_str dummy) const
			{
				c_str filename = this->string(block0, "filename", dummy);

				return file::Output(filename);
			}

			inline file::Output output_filename(c_str block0, c_str block1, c_str dummy) const
			{
				c_str filename = this->string(block0, block1, "filename", dummy);

				return file::Output(filename);
			}

			inline file::Input input_filename(c_str block0, c_str dummy) const
			{
				c_str filename = this->string(block0, "filename", dummy);

				return file::Input(filename);
			}

			inline file::Input input_filename(c_str block0, c_str block1, c_str dummy) const
			{
				c_str filename = this->string(block0, block1, "filename", dummy);

				return file::Input(filename);
			}

			inline char pes_arrangement() const
			{
				return as_char(96 + this->value("pes", "arrang", 1, 3, 1));
			}

			pes::Frontend pes_extern_lib() const
			{
				auto atom_a = this->isotope("pes", "atom_a");
				auto atom_b = this->isotope("pes", "atom_b");
				auto atom_c = this->isotope("pes", "atom_c");

				c_str filename = this->string("pes", "extern_lib", "\0");

				if (filename[0] == '\0') {
					print::error(WHERE, "Expecting the filename of the PES shared library at pes.extern_lib");
				}

				return pes::Frontend(filename, atom_a, atom_b, atom_c);
			}

			inline Range<u32> pes_legendre_expansion() const
			{
				return this->range("pes", "legendre_expansion", 0u, u32_max);
			}

			#define MEMBER_RANGE_IMPL(type)                                                                                  \
			Range<type> range(c_str block0, type min, type max, type step, mpi::Frontend *mpi = nullptr) const               \
			{                                                                                                                \
				type new_min = this->value(block0, "min", min, max, min, mpi);                                               \
				type new_max = this->value(block0, "max", new_min, max, new_min, mpi);                                       \
				type new_step = this->value(block0, "step", step, mpi);                                                      \
				                                                                                                             \
				return Range<type>(new_min, new_max, new_step);                                                              \
			}                                                                                                                \
                                                                                                                             \
			Range<type> range(c_str block0, c_str block1, type min, type max, type step, mpi::Frontend *mpi = nullptr) const \
			{                                                                                                                \
				type new_min = this->value(block0, block1, "min", min, max, min, mpi);                                       \
				type new_max = this->value(block0, block1, "max", new_min, max, new_min, mpi);                               \
				type new_step = this->value(block0, block1, "step", step, mpi);                                              \
				                                                                                                             \
				return Range<type>(new_min, new_max, new_step);                                                              \
			}

			MEMBER_RANGE_IMPL(u8)
			MEMBER_RANGE_IMPL(u16)
			MEMBER_RANGE_IMPL(u32)
			MEMBER_RANGE_IMPL(u64)
			MEMBER_RANGE_IMPL(s8)
			MEMBER_RANGE_IMPL(s16)
			MEMBER_RANGE_IMPL(s32)
			MEMBER_RANGE_IMPL(s64)
			MEMBER_RANGE_IMPL(f32)
			MEMBER_RANGE_IMPL(f64)

			#undef MEMBER_RANGE_IMPL

			private:
			toml::table input;

			template<typename T>
			T node_value(c_str block0, mut<T> entry, mpi::Frontend *mpi = nullptr) const
			{
				auto node = this->input[block0];

				if (mpi != nullptr) {
					if (mpi->rank() != mpi::MASTER_PROCESS_RANK) {
						goto meeting_point;
					}
				}

				if (node.type() == toml::node_type::none) {
					goto meeting_point;
				}

				if constexpr(::is_integer<T>()) {
					if (node.type() != toml::node_type::integer) {
						print::error(WHERE, "Expecting an integer value at ", block0);
					}

					if (::is_unsigned<T>() && (node.ref<s64>() < 0)) {
						print::error(WHERE, "Expecting an unsigned value at ", block0);
					}

					entry = static_cast<T>(node.ref<s64>());
				}

				if constexpr(::is_floating_point<T>()) {
					if (node.type() != toml::node_type::floating_point) {
						print::error(WHERE, "Expecting a floating point value at ", block0);
					}

					entry = static_cast<T>(node.ref<f64>());
				}

				meeting_point:
				if (mpi != nullptr) {
					mpi->broadcast(mpi::MASTER_PROCESS_RANK, 1, &entry);
				}

				return entry;
			}

			template<typename T>
			T node_value(c_str block0, c_str block1, mut<T> entry, mpi::Frontend *mpi = nullptr) const
			{
				auto node = this->input[block0][block1];

				if (mpi != nullptr) {
					if (mpi->rank() != mpi::MASTER_PROCESS_RANK) {
						goto meeting_point;
					}
				}

				if (node.type() == toml::node_type::none) {
					goto meeting_point;
				}

				if constexpr(::is_integer<T>()) {
					if (node.type() != toml::node_type::integer) {
						print::error(WHERE, "Expecting an integer value at ", block0, '.', block1);
					}

					if (::is_unsigned<T>() && (node.ref<s64>() < 0)) {
						print::error(WHERE, "Expecting an unsigned value at ", block0, '.', block1);
					}

					entry = static_cast<T>(node.ref<s64>());
				}

				if constexpr(::is_floating_point<T>()) {
					if (node.type() != toml::node_type::floating_point) {
						print::error(WHERE, "Expecting a floating point value at ", block0, '.', block1);
					}

					entry = static_cast<T>(node.ref<f64>());
				}

				meeting_point:
				if (mpi != nullptr) {
					mpi->broadcast(mpi::MASTER_PROCESS_RANK, 1, &entry);
				}

				return entry;
			}

			template<typename T>
			T node_value(c_str block0, c_str block1, c_str block2, mut<T> entry, mpi::Frontend *mpi = nullptr) const
			{
				auto node = this->input[block0][block1][block2];

				if (mpi != nullptr) {
					if (mpi->rank() != mpi::MASTER_PROCESS_RANK) {
						goto meeting_point;
					}
				}

				if (node.type() == toml::node_type::none) {
					goto meeting_point;
				}

				if constexpr(::is_integer<T>()) {
					if (node.type() != toml::node_type::integer) {
						print::error(WHERE, "Expecting an integer value at ", block0, '.', block1, '.', block2);
					}

					if (::is_unsigned<T>() && (node.ref<s64>() < 0)) {
						print::error(WHERE, "Expecting an unsigned value at ", block0, '.', block1, '.', block2);
					}

					entry = static_cast<T>(node.ref<s64>());
				}

				if constexpr(::is_floating_point<T>()) {
					if (node.type() != toml::node_type::floating_point) {
						print::error(WHERE, "Expecting a floating point value at ", block0, '.', block1, '.', block2);
					}

					entry = static_cast<T>(node.ref<f64>());
				}

				meeting_point:
				if (mpi != nullptr) {
					mpi->broadcast(mpi::MASTER_PROCESS_RANK, 1, &entry);
				}

				return entry;
			}
		};
	}
#endif
