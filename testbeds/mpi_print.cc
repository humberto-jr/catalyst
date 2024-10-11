#include "modules/essentials.h"
#include "modules/libmpi.h"

int main(int argc, char *argv[])
{
	mpi::Frontend mpi(&argc, &argv);

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		print::line("# Ordered MPI printing");
		print::line("# Build details:");
		mpi::about();
	}

	// NOTE: This must be printed in order.
	mpi.print_line("Rank ", mpi.rank(), " says: \"Hello, World!\"");

	return EXIT_SUCCESS;
}
