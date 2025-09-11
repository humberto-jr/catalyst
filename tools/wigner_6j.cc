#include "modules/essentials.h"
#include "modules/input.h"
#include "modules/math.h"

constexpr u8 PAD = 6;

int main(int argc, char *argv[])
{
	if (argc != 7) {
		print::error("# Usage: ", argv[0], " [ja] [jb] [jc] [jd] [je] [jf]");
	}

	s32 ja = std::atoi(argv[1]);
	s32 jb = std::atoi(argv[2]);
	s32 jc = std::atoi(argv[3]);
	s32 jd = std::atoi(argv[4]);
	s32 je = std::atoi(argv[5]);
	s32 jf = std::atoi(argv[6]);

	f64 c = math::wigner_6j(2*ja, 2*jb, 2*jc, 2*jd, 2*je, 2*jf);

	//
	// Output:
	//

	print::line<PAD>(ja, jb, jc, jd, je, jf, ' ', c);

	return EXIT_SUCCESS;
}
