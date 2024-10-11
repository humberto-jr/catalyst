#include "modules/essentials.h"
#include "modules/libmpi.h"

constexpr usize MAX_TASK = 100;

int main(int argc, char *argv[])
{
	mpi::Frontend mpi(&argc, &argv);

	mpi.set_tasks(MAX_TASK);

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		print::line("# MPI tasks: ", MAX_TASK, " tasks divided by ", mpi.world_size(), " processes");
		print::line("# Build details:");
		mpi::about();
	}

	const auto start = mpi.first_local_task();
	const auto end = mpi.last_local_task();
	const auto extra = mpi.extra_task();

	print::Fmt log;
	log += "Rank ";
	log += mpi.rank();
	log += ", task index range: [";
	log += start;
	log += ", ";
	log += end;
	log += "]";

	if (extra.has_value()) {
		log += " and ";
		log += extra.value();
	}

	mpi.print_line(log);

	return EXIT_SUCCESS;
}
