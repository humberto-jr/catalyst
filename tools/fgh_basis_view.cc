#include "modules/essentials.h"
#include "modules/file.h"
#include "modules/fgh.h"

int main(int argc, const char *argv[])
{
	if (argc != 2) {
		print::error("# Usage: ", argv[0], " [filename]");
	}

	fgh::Basis basis(argv[1]);

	print::timestamp();
	print::line("# Number of eigenvectors = ", basis.count());

	mut<usize> count = 0;

	for (auto &entry : basis) {
		print::line("# Eigenvalue(", count, ") = ", entry.eigenval, " a.u.",
		            ", J = ", entry.J,
		            ", v = ", entry.v,
		            ", j = ", entry.j,
		            ", l = ", entry.l,
		            ", p = ", entry.p,
		            ", n = ", entry.n,
		            ", norm. = ", entry.norm,
		            ", size = ", entry.eigenvec.length());

		for (auto r : entry.r_list.indexed()) {
			print::line<24>(r.value, entry.norm*entry.eigenvec[r.index]);
		}

		print::line();
		++count;
	}

	return EXIT_SUCCESS;
}
