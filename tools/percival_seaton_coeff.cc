#include "modules/essentials.h"
#include "modules/input.h"
#include "modules/math.h"

constexpr u8 PAD = 6;

int main(int argc, char *argv[])
{
	if (argc != 7) {
		print::error("# Usage: ", argv[0], " [J] [ja] [jb] [la] [lb] [lambda]");
	}

	s32 J = std::atoi(argv[1]);
	s32 ja = std::atoi(argv[2]);
	s32 jb = std::atoi(argv[3]);
	s32 la = std::atoi(argv[4]);
	s32 lb = std::atoi(argv[5]);
	s32 lambda = std::atoi(argv[6]);

	f64 f = math::percival_seaton_coeff(J, 0, 0, ja, jb, la, lb, lambda, 1);

	//
	// Output:
	//

	// For details see:
	// I. C. Percival and M. J. Seaton. Math. Proc. Camb. Philos. Soc. 53, 3, 654-662 (1975)
	print::line<PAD>(J, ja, jb, la, lb, lambda, ' ', f);

	return EXIT_SUCCESS;
}
