#include "modules/essentials.h"
#include "modules/libmpi.h"

int main(int argc, char *argv[])
{
	mpi::frontend mpi(&argc, &argv);

	u32 this_rank = mpi.rank();
	u32 next_rank = this_rank + 1;
	u32 prev_rank = this_rank - 1;
	u32 last_rank = mpi.world_size() - 1;

	if (this_rank == mpi::MASTER_PROCESS_RANK) {
		print::line("# Circular message passing to test MPI communication");
		print::line("# Build details:");
		mpi::about();

		if (mpi::is_used()) {
			s64 now = std::time(nullptr);

			std::srand(as_u32(now));

			s32 tag = std::rand();

			mpi.send(next_rank, 1, &tag);

			print::line("# Process ", this_rank, ": created tag ", tag, " and sent to ", next_rank);

			mut<s32> recv_tag = 0;

			auto count = mpi.receive(last_rank, 1, &recv_tag);
			assert(count == 1);

			print::line("# Process ", this_rank, ": received tag ", tag, " from ", last_rank);

			if (recv_tag != tag) {
				print::error(WHERE, "Master process didn't receive the original tag");
			}
		}
	} else {
		mut<s32> recv_tag = 0;

		auto count = mpi.receive(prev_rank, 1, &recv_tag);
		assert(count == 1);

		if (this_rank == last_rank) {
			mpi.send(mpi::MASTER_PROCESS_RANK, 1, &recv_tag);

			print::line("# Process ", this_rank, ": received tag ", recv_tag, " from ", prev_rank, " and sent to ", mpi::MASTER_PROCESS_RANK);
		} else {
			mpi.send(next_rank, 1, &recv_tag);

			print::line("# Process ", this_rank, ": received tag ", recv_tag, " from ", prev_rank, " and sent to ", next_rank);
		}
	}

	return EXIT_SUCCESS;
}
