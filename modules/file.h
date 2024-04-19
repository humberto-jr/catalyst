#if !defined(FILE_HEADER)
	#define FILE_HEADER
	#include "essentials.h"

	namespace file {
		static std::FILE* open(c_str filename, c_str mode)
		{
			std::FILE *stream = std::fopen(filename, mode);

			if (stream == nullptr) {
				print::error(WHERE, "Unable to open ", filename);
			}

			return stream;
		}

		static void close(std::FILE* &stream)
		{
			if (stream != nullptr) {
				std::fclose(stream);
				stream = nullptr;
			}
		}

		static void seek_set(std::FILE *stream, usize count = 0)
		{
			auto info = std::fseek(stream, count, SEEK_SET);

			if (info != 0) {
				print::error(WHERE, "Unable to set the position indicator at ", count, " bytes from the beginning");
			}
		}

		static void seek_end(std::FILE *stream, usize count = 0)
		{
			auto info = std::fseek(stream, count, SEEK_END);

			if (info != 0) {
				print::error(WHERE, "Unable to set the position indicator at ", count, " bytes from the end");
			}
		}

		class input {
			public:
			const string filename;

			inline input(c_str filename): filename(filename), stream(nullptr)
			{
				this->stream = file::open(this->filename.as_cstr(), "rb");
			}

			inline input(string &filename): filename(filename.move()), stream(nullptr)
			{
				this->stream = file::open(this->filename.as_cstr(), "rb");
			}

			inline input(input &other): filename(other.filename.as_cstr()), stream(nullptr)
			{
				this->stream = file::open(this->filename.as_cstr(), "rb");
			}

			template<typename T>
			void read_raw(usize count, T *data)
			{
				assert(data != nullptr);

				mut<usize> info = 0;

				#pragma omp critical(stream)
				info = std::fread(&data[0], sizeof(T), count, this->stream);

				if ((info == 0) && this->end()) {
					return;
				}

				if (info != count) {
					print::error(WHERE, "Only ", info/sizeof(T), "/", count, " elements of ", sizeof(T), " bytes read from ", this->filename.as_cstr());
				}
			}

			inline void read(bool &data)
			{
				this->read_raw<bool>(1, &data);
			}

			inline void read(char &data)
			{
				this->read_raw<char>(1, &data);
			}

			inline void read(mut<u8> &data)
			{
				this->read_raw<mut<u8>>(1, &data);
			}

			inline void read(mut<u16> &data)
			{
				this->read_raw<mut<u16>>(1, &data);
			}

			inline void read(mut<u32> &data)
			{
				this->read_raw<mut<u32>>(1, &data);
			}

			inline void read(mut<u64> &data)
			{
				this->read_raw<mut<u64>>(1, &data);
			}

			inline void read(mut<s8> &data)
			{
				this->read_raw<mut<s8>>(1, &data);
			}

			inline void read(mut<s16> &data)
			{
				this->read_raw<mut<s16>>(1, &data);
			}

			inline void read(mut<s32> &data)
			{
				this->read_raw<mut<s32>>(1, &data);
			}

			inline void read(mut<s64> &data)
			{
				this->read_raw<mut<s64>>(1, &data);
			}

			inline void read(mut<f32> &data)
			{
				this->read_raw<mut<f32>>(1, &data);
			}

			inline void read(mut<f64> &data)
			{
				this->read_raw<mut<f64>>(1, &data);
			}

			inline void read(mut<f128> &data)
			{
				this->read_raw<mut<f128>>(1, &data);
			}

			template<typename T>
			inline void read(vector<T> &data)
			{
				this->read_raw<T>(data.length(), &data[0]);
			}

			template<typename T>
			inline void read(matrix<T> &data)
			{
				this->read_raw<mut<T>>(data.rows()*data.cols(), &data[0]);
			}

			template<typename T>
			inline void read(typename matrix<T>::view &data)
			{
				for (mut<usize> n = 0; n < data.rows(); ++n)
					for (mut<usize> m = 0; m < data.cols(); ++m)
						this->read_raw<T>(1, &data(n, m));
			}

			void read_all(vector<byte> &buf)
			{
				this->seek_set();
				auto count = this->size();

				if (count > buf.length()) {
					buf.resize(count);
				}

				this->read<byte>(buf);
			}

			inline void seek_set(usize count = 0)
			{
				file::seek_set(this->stream, count);
			}

			inline void seek_end(usize count = 0)
			{
				file::seek_end(this->stream, count);
			}

			usize size()
			{
				auto caller_offset = std::ftell(this->stream);

				this->seek_end();
				auto count = std::ftell(this->stream);
				this->seek_set(caller_offset);

				return count;
			}

			inline bool end() const
			{
				// NOTE: True only after the first attempt to read past the EOF.
				return (std::feof(this->stream) != 0);
			}

			inline ~input()
			{
				file::close(this->stream);
			}

			private:
			std::FILE *stream;
		};

		class output {
			public:
			const string filename;

			inline output(c_str filename): filename(filename), stream(nullptr)
			{
				this->stream = file::open(this->filename.as_cstr(), "wb");
			}

			inline output(string &filename): filename(filename.move()), stream(nullptr)
			{
				this->stream = file::open(this->filename.as_cstr(), "wb");
			}

			inline output(output &other): filename(other.filename.as_cstr()), stream(nullptr)
			{
				this->stream = file::open(this->filename.as_cstr(), "wb");
			}

			template<typename T>
			void write_raw(usize count, const T *data)
			{
				assert(data != nullptr);

				mut<usize> info = 0;

				#pragma omp critical(stream)
				info = std::fwrite(&data[0], sizeof(T), count, this->stream);

				if (info != count) {
					print::error(WHERE, "Only ", info/sizeof(T), "/", count, " elements of ", sizeof(T), " bytes written to ", this->filename.as_cstr());
				}
			}

			inline void write(const bool &data)
			{
				this->write_raw<bool>(1, &data);
			}

			inline void write(const char &data)
			{
				this->write_raw<char>(1, &data);
			}

			inline void write(u8 &data)
			{
				this->write_raw<u8>(1, &data);
			}

			inline void write(u16 &data)
			{
				this->write_raw<u16>(1, &data);
			}

			inline void write(u32 &data)
			{
				this->write_raw<u32>(1, &data);
			}

			inline void write(u64 &data)
			{
				this->write_raw<u64>(1, &data);
			}

			inline void write(s8 &data)
			{
				this->write_raw<s8>(1, &data);
			}

			inline void write(s16 &data)
			{
				this->write_raw<s16>(1, &data);
			}

			inline void write(s32 &data)
			{
				this->write_raw<s32>(1, &data);
			}

			inline void write(s64 &data)
			{
				this->write_raw<s64>(1, &data);
			}

			inline void write(f32 &data)
			{
				this->write_raw<f32>(1, &data);
			}

			inline void write(f64 &data)
			{
				this->write_raw<f64>(1, &data);
			}

			inline void write(f128 &data)
			{
				this->write_raw<f128>(1, &data);
			}

			template<typename T>
			inline void write(const vector<T> &data)
			{
				this->write_raw<T>(data.length(), &data[0]);
			}

			template<typename T>
			inline void write(const matrix<T> &data)
			{
				this->write_raw<T>(data.rows()*data.cols(), &data[0]);
			}

			template<typename T>
			inline void write(const typename matrix<T>::view &data)
			{
				for (mut<usize> n = 0; n < data.rows(); ++n)
					for (mut<usize> m = 0; m < data.cols(); ++m)
						this->write_raw<T>(1, &data(n, m));
			}

			inline void seek_set(usize count = 0)
			{
				file::seek_set(this->stream, count);
			}

			inline void seek_end(usize count = 0)
			{
				file::seek_end(this->stream, count);
			}

			inline ~output()
			{
				file::close(this->stream);
			}

			private:
			std::FILE *stream;
		};

		template<typename T>
		static constexpr bool is_input()
		{
			return std::is_same<T, file::input>::value;
		}

		template<typename T>
		static constexpr bool is_output()
		{
			return std::is_same<T, file::output>::value;
		}
	}
#endif
