#include "modules/essentials.h"
#include "modules/input.h"
#include "modules/math.h"

constexpr u8 PAD = 6;

int main(int argc, char *argv[])
{
	if (argc != 10) {
		print::error("# Usage: ", argv[0], " [ja] [jb] [jc] [jd] [je] [jf] [jg] [jh] [ji]");
	}

	s32 ja = std::atoi(argv[1]);
	s32 jb = std::atoi(argv[2]);
	s32 jc = std::atoi(argv[3]);
	s32 jd = std::atoi(argv[4]);
	s32 je = std::atoi(argv[5]);
	s32 jf = std::atoi(argv[6]);
	s32 jg = std::atoi(argv[7]);
	s32 jh = std::atoi(argv[8]);
	s32 ji = std::atoi(argv[9]);

	f64 c = math::wigner_9j(ja, jb, jc, jd, je, jf, jg, jh, ji);

	//
	// Output:
	//

	print::line<PAD>(ja, jb, jc, jd, je, jf, jg, jh, ji, ' ', c);

	return EXIT_SUCCESS;
}
