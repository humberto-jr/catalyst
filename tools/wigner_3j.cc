#include "modules/essentials.h"
#include "modules/input.h"
#include "modules/math.h"

constexpr u8 PAD = 6;

int main(int argc, char *argv[])
{
	if (argc != 7) {
		print::error("# Usage: ", argv[0], " [ja] [jb] [jc] [ma] [mb] [mc]");
	}

	s32 ja = std::atoi(argv[1]);
	s32 jb = std::atoi(argv[2]);
	s32 jc = std::atoi(argv[3]);
	s32 ma = std::atoi(argv[4]);
	s32 mb = std::atoi(argv[5]);
	s32 mc = std::atoi(argv[6]);

	f64 c = math::wigner_3j(2*ja, 2*jb, 2*jc, 2*ma, 2*mb, 2*mc);

	//
	// Output:
	//

	print::line<PAD>(ja, jb, jc, ma, mb, mc, ' ', c);

	return EXIT_SUCCESS;
}
