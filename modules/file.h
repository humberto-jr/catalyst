#if !defined(FILE_HEADER)
	#define FILE_HEADER
	#include "essentials.h"
	#include "struct.h"

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

		// NOTE: Overloaded versions of the write() and read() members for types
		// Vec<T>, Mat<T> and Mat<T>::View are used below, instead of templates,
		// so that the caller won't need to specify the inner primitive type T.

		class Input {
			public:
			const String filename;

			inline Input(c_str filename): filename(filename), stream(nullptr)
			{
				this->stream = file::open(this->filename.as_cstr(), "rb");
			}

			inline Input(String &filename): filename(filename.move()), stream(nullptr)
			{
				this->stream = file::open(this->filename.as_cstr(), "rb");
			}

			inline Input(file::Input &other): filename(other.filename.as_cstr()), stream(nullptr)
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

			inline void read(Vec<u8> &data)
			{
				this->read_raw<mut<u8>>(data.length(), &data[0]);
			}

			inline void read(Vec<u16> &data)
			{
				this->read_raw<mut<u16>>(data.length(), &data[0]);
			}

			inline void read(Vec<u32> &data)
			{
				this->read_raw<mut<u32>>(data.length(), &data[0]);
			}

			inline void read(Vec<u64> &data)
			{
				this->read_raw<mut<u64>>(data.length(), &data[0]);
			}

			inline void read(Vec<s8> &data)
			{
				this->read_raw<mut<s8>>(data.length(), &data[0]);
			}

			inline void read(Vec<s16> &data)
			{
				this->read_raw<mut<s16>>(data.length(), &data[0]);
			}

			inline void read(Vec<s32> &data)
			{
				this->read_raw<mut<s32>>(data.length(), &data[0]);
			}

			inline void read(Vec<s64> &data)
			{
				this->read_raw<mut<s64>>(data.length(), &data[0]);
			}

			inline void read(Vec<f64> &data)
			{
				this->read_raw<mut<f64>>(data.length(), &data[0]);
			}

			inline void read(Vec<f32> &data)
			{
				this->read_raw<mut<f32>>(data.length(), &data[0]);
			}

			inline void read(Vec<f128> &data)
			{
				this->read_raw<mut<f128>>(data.length(), &data[0]);
			}

			inline void read(String &data)
			{
				this->read_raw<char>(data.length(), data.as_ptr());
			}

			inline void read(Mat<bool> &data)
			{
				this->read_raw<bool>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<char> &data)
			{
				this->read_raw<char>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<u8> &data)
			{
				this->read_raw<mut<u8>>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<u16> &data)
			{
				this->read_raw<mut<u16>>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<u32> &data)
			{
				this->read_raw<mut<u32>>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<u64> &data)
			{
				this->read_raw<mut<u64>>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<s8> &data)
			{
				this->read_raw<mut<s8>>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<s16> &data)
			{
				this->read_raw<mut<s16>>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<s32> &data)
			{
				this->read_raw<mut<s32>>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<s64> &data)
			{
				this->read_raw<mut<s64>>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<f32> &data)
			{
				this->read_raw<mut<f32>>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<f64> &data)
			{
				this->read_raw<mut<f64>>(data.rows()*data.cols(), &data[0]);
			}

			inline void read(Mat<f128> &data)
			{
				this->read_raw<mut<f128>>(data.rows()*data.cols(), &data[0]);
			}

			template<typename T>
			void read_mat_view(typename Mat<T>::View &data)
			{
				// NOTE: Elements of a Mat<T>::View may not be stored contiguously
				// in memory. Therefore, a loop is needed.

				for (mut<usize> n = 0; n < data.rows(); ++n)
					for (mut<usize> m = 0; m < data.cols(); ++m)
						this->read_raw<mut<T>>(1, &data(n, m));
			}

			inline void read(typename Mat<bool>::View &data)
			{
				this->read_mat_view<bool>(data);
			}

			inline void read(typename Mat<char>::View &data)
			{
				this->read_mat_view<char>(data);
			}

			inline void read(typename Mat<u8>::View &data)
			{
				this->read_mat_view<u8>(data);
			}

			inline void read(typename Mat<u16>::View &data)
			{
				this->read_mat_view<u16>(data);
			}

			inline void read(typename Mat<u32>::View &data)
			{
				this->read_mat_view<u32>(data);
			}

			inline void read(typename Mat<u64>::View &data)
			{
				this->read_mat_view<u64>(data);
			}

			inline void read(typename Mat<s8>::View &data)
			{
				this->read_mat_view<s8>(data);
			}

			inline void read(typename Mat<s16>::View &data)
			{
				this->read_mat_view<s16>(data);
			}

			inline void read(typename Mat<s32>::View &data)
			{
				this->read_mat_view<s32>(data);
			}

			inline void read(typename Mat<s64>::View &data)
			{
				this->read_mat_view<s64>(data);
			}

			inline void read(typename Mat<f32>::View &data)
			{
				this->read_mat_view<f32>(data);
			}

			inline void read(typename Mat<f64>::View &data)
			{
				this->read_mat_view<f64>(data);
			}

			inline void read(typename Mat<f128>::View &data)
			{
				this->read_mat_view<f128>(data);
			}

			template<typename T>
			void read_range(Range<T> &data)
			{
				mut<T> list[3];
				type_zeroed(list, 3);

				this->read_raw<mut<T>>(3, list);

				data = Range<T>(list[0], list[1], list[2]);
			}

			inline void read(Range<char> &data)
			{
				this->read_range<char>(data);
			}

			inline void read(Range<u8> &data)
			{
				this->read_range<u8>(data);
			}

			inline void read(Range<u16> &data)
			{
				this->read_range<u16>(data);
			}

			inline void read(Range<u32> &data)
			{
				this->read_range<u32>(data);
			}

			inline void read(Range<u64> &data)
			{
				this->read_range<u64>(data);
			}

			inline void read(Range<s8> &data)
			{
				this->read_range<s8>(data);
			}

			inline void read(Range<s16> &data)
			{
				this->read_range<s16>(data);
			}

			inline void read(Range<s32> &data)
			{
				this->read_range<s32>(data);
			}

			inline void read(Range<s64> &data)
			{
				this->read_range<s64>(data);
			}

			inline void read(Range<f32> &data)
			{
				this->read_range<f32>(data);
			}

			inline void read(Range<f64> &data)
			{
				this->read_range<f64>(data);
			}

			inline void read(Range<f128> &data)
			{
				this->read_range<f128>(data);
			}

			inline void read(Struct &data)
			{
				this->read_raw<mut<byte>>(data.size(), &data[0]);
			}

			void read_all(Vec<byte> &buf)
			{
				this->seek_set();
				auto count = this->size();

				if (count > buf.length()) {
					buf.resize(count);
				}

				this->read(buf);
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

			inline ~Input()
			{
				file::close(this->stream);
			}

			private:
			std::FILE *stream;
		};

		class Output {
			public:
			const String filename;

			inline Output(c_str filename): filename(filename), stream(nullptr)
			{
				this->stream = file::open(this->filename.as_cstr(), "wb");
			}

			inline Output(String &filename): filename(filename.move()), stream(nullptr)
			{
				this->stream = file::open(this->filename.as_cstr(), "wb");
			}

			inline Output(file::Output &other): filename(other.filename.as_cstr()), stream(nullptr)
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

			inline void write(const bool data)
			{
				this->write_raw<bool>(1, &data);
			}

			inline void write(const char data)
			{
				this->write_raw<char>(1, &data);
			}

			inline void write(c_str data)
			{
				this->write_raw<char>(std::strlen(data), data);
			}

			inline void write(u8 data)
			{
				this->write_raw<u8>(1, &data);
			}

			inline void write(u16 data)
			{
				this->write_raw<u16>(1, &data);
			}

			inline void write(u32 data)
			{
				this->write_raw<u32>(1, &data);
			}

			inline void write(u64 data)
			{
				this->write_raw<u64>(1, &data);
			}

			inline void write(s8 data)
			{
				this->write_raw<s8>(1, &data);
			}

			inline void write(s16 data)
			{
				this->write_raw<s16>(1, &data);
			}

			inline void write(s32 data)
			{
				this->write_raw<s32>(1, &data);
			}

			inline void write(s64 data)
			{
				this->write_raw<s64>(1, &data);
			}

			inline void write(f32 data)
			{
				this->write_raw<f32>(1, &data);
			}

			inline void write(f64 data)
			{
				this->write_raw<f64>(1, &data);
			}

			inline void write(f128 data)
			{
				this->write_raw<f128>(1, &data);
			}

			inline void write(const Vec<bool> &data)
			{
				this->write_raw<bool>(data.length(), &data[0]);
			}

			inline void write(const Vec<char> &data)
			{
				this->write_raw<char>(data.length(), &data[0]);
			}

			inline void write(const Vec<u8> &data)
			{
				this->write_raw<mut<u8>>(data.length(), &data[0]);
			}

			inline void write(const Vec<u16> &data)
			{
				this->write_raw<mut<u16>>(data.length(), &data[0]);
			}

			inline void write(const Vec<u32> &data)
			{
				this->write_raw<mut<u32>>(data.length(), &data[0]);
			}

			inline void write(const Vec<u64> &data)
			{
				this->write_raw<mut<u64>>(data.length(), &data[0]);
			}

			inline void write(const Vec<s8> &data)
			{
				this->write_raw<mut<s8>>(data.length(), &data[0]);
			}

			inline void write(const Vec<s16> &data)
			{
				this->write_raw<mut<s16>>(data.length(), &data[0]);
			}

			inline void write(const Vec<s32> &data)
			{
				this->write_raw<mut<s32>>(data.length(), &data[0]);
			}

			inline void write(const Vec<s64> &data)
			{
				this->write_raw<mut<s64>>(data.length(), &data[0]);
			}

			inline void write(const Vec<f64> &data)
			{
				this->write_raw<mut<f64>>(data.length(), &data[0]);
			}

			inline void write(const Vec<f32> &data)
			{
				this->write_raw<mut<f32>>(data.length(), &data[0]);
			}

			inline void write(const Vec<f128> &data)
			{
				this->write_raw<mut<f128>>(data.length(), &data[0]);
			}

			inline void write(const String &data)
			{
				this->write_raw<char>(data.length(), data.as_cstr());
			}

			inline void write(const Mat<bool> &data)
			{
				this->write_raw<bool>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<char> &data)
			{
				this->write_raw<char>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<u8> &data)
			{
				this->write_raw<mut<u8>>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<u16> &data)
			{
				this->write_raw<mut<u16>>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<u32> &data)
			{
				this->write_raw<mut<u32>>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<u64> &data)
			{
				this->write_raw<mut<u64>>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<s8> &data)
			{
				this->write_raw<mut<s8>>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<s16> &data)
			{
				this->write_raw<mut<s16>>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<s32> &data)
			{
				this->write_raw<mut<s32>>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<s64> &data)
			{
				this->write_raw<mut<s64>>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<f32> &data)
			{
				this->write_raw<mut<f32>>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<f64> &data)
			{
				this->write_raw<mut<f64>>(data.rows()*data.cols(), &data[0]);
			}

			inline void write(const Mat<f128> &data)
			{
				this->write_raw<mut<f128>>(data.rows()*data.cols(), &data[0]);
			}

			template<typename T>
			void write_mat_view(const typename Mat<T>::View &data)
			{
				// NOTE: Elements of a Mat<T>::View may not be stored contiguously
				// in memory. Therefore, a loop is needed.

				for (mut<usize> n = 0; n < data.rows(); ++n)
					for (mut<usize> m = 0; m < data.cols(); ++m)
						this->write_raw<mut<T>>(1, &data(n, m));
			}

			inline void write(const typename Mat<bool>::View &data)
			{
				this->write_mat_view<bool>(data);
			}

			inline void write(const typename Mat<char>::View &data)
			{
				this->write_mat_view<char>(data);
			}

			inline void write(const typename Mat<u8>::View &data)
			{
				this->write_mat_view<u8>(data);
			}

			inline void write(const typename Mat<u16>::View &data)
			{
				this->write_mat_view<u16>(data);
			}

			inline void write(const typename Mat<u32>::View &data)
			{
				this->write_mat_view<u32>(data);
			}

			inline void write(const typename Mat<u64>::View &data)
			{
				this->write_mat_view<u64>(data);
			}

			inline void write(const typename Mat<s8>::View &data)
			{
				this->write_mat_view<s8>(data);
			}

			inline void write(const typename Mat<s16>::View &data)
			{
				this->write_mat_view<s16>(data);
			}

			inline void write(const typename Mat<s32>::View &data)
			{
				this->write_mat_view<s32>(data);
			}

			inline void write(const typename Mat<s64>::View &data)
			{
				this->write_mat_view<s64>(data);
			}

			inline void write(const typename Mat<f32>::View &data)
			{
				this->write_mat_view<f32>(data);
			}

			inline void write(const typename Mat<f64>::View &data)
			{
				this->write_mat_view<f64>(data);
			}

			inline void write(const typename Mat<f128>::View &data)
			{
				this->write_mat_view<f128>(data);
			}

			template<typename T>
			inline void write_range(const Range<T> &data)
			{
				T list[] = {data.min, data.max, data.step};
				this->write_raw<mut<T>>(3, list);
			}

			inline void write(const Range<char> &data)
			{
				this->write_range<char>(data);
			}

			inline void write(const Range<u8> &data)
			{
				this->write_range<u8>(data);
			}

			inline void write(const Range<u16> &data)
			{
				this->write_range<u16>(data);
			}

			inline void write(const Range<u32> &data)
			{
				this->write_range<u32>(data);
			}

			inline void write(const Range<u64> &data)
			{
				this->write_range<u64>(data);
			}

			inline void write(const Range<s8> &data)
			{
				this->write_range<s8>(data);
			}

			inline void write(const Range<s16> &data)
			{
				this->write_range<s16>(data);
			}

			inline void write(const Range<s32> &data)
			{
				this->write_range<s32>(data);
			}

			inline void write(const Range<s64> &data)
			{
				this->write_range<s64>(data);
			}

			inline void write(const Range<f32> &data)
			{
				this->write_range<f32>(data);
			}

			inline void write(const Range<f64> &data)
			{
				this->write_range<f64>(data);
			}

			inline void write(const Range<f128> &data)
			{
				this->write_range<f128>(data);
			}

			inline void write(const Struct &data)
			{
				this->write_raw<byte>(data.size(), &data[0]);
			}

			inline void seek_set(usize count = 0)
			{
				file::seek_set(this->stream, count);
			}

			inline void seek_end(usize count = 0)
			{
				file::seek_end(this->stream, count);
			}

			inline ~Output()
			{
				file::close(this->stream);
			}

			private:
			std::FILE *stream;
		};

		template<typename T>
		static constexpr bool is_input()
		{
			return std::is_same<T, file::Input>::value;
		}

		template<typename T>
		static constexpr bool is_output()
		{
			return std::is_same<T, file::Output>::value;
		}
	}
#endif
