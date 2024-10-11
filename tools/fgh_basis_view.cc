#include "modules/essentials.h"
#include "modules/file.h"
#include "modules/fgh.h"

int main(int argc, const char *argv[])
{
	if (argc != 2) {
		print::error("# Usage: ", argv[0], " [filename]");
	}

	fgh::Basis result;

	file::Input buf(argv[1]);

	u32 total = fgh::is_valid(buf);

	print::timestamp();
	print::line("# Number of eigenvectors = ", total);

	for (mut<u32> count = 0; count < total; ++count) {
		fgh::load_basis(count, buf, result);

		print::line("# Eigenvalue(", count, ") = ", result.eigenval, " a.u., J = ", result.J, ", v = ", result.v, ", j = ", result.j,
		            ", l = ", result.l, ", parity = ", result.p, ", comp. = ", result.comp, ", norm. = ", result.norm, ", size = ", result.eigenvec.length());

		for (mut<u32> n = 0; n < result.eigenvec.length(); ++n) {
			f64 r = result.r_min + as_f64(result.n_min + n)*result.r_step;

			print::line<24>(r, result[n]);
		}

		print::line();
	}

	return EXIT_SUCCESS;
}
