#include <stdio.h>
#include <string.h>

#include <librpmem.h>

#define POOL_SIZE	(32 * 1024 * 1024)
#define NLANES		4
unsigned char pool[POOL_SIZE];

		int
main(int argc, char *argv[])
{

		int ret;
		unsigned nlanes = NLANES;

		/* fill pool_attributes */
		struct rpmem_pool_attr pool_attr;
		memset(&pool_attr, 0, sizeof(pool_attr));

		/* create a remote pool */
		RPMEMpool *rpp = rpmem_create("localhost", "pool.set",
						pool, POOL_SIZE, &nlanes, &pool_attr);
		if (!rpp) {

				fprintf(stderr, "rpmem_create: %s\n", rpmem_errormsg());
				return 1;
		}

		/* store data on local pool */
		memset(pool, 0, POOL_SIZE);

		/* make local data persistent on remote node */
		ret = rpmem_persist(rpp, 0, POOL_SIZE, 0);
		if (ret) {

				fprintf(stderr, "rpmem_persist: %s\n", rpmem_errormsg());
				return 1;
		}

		/* close the remote pool */
		ret = rpmem_close(rpp);
		if (ret) {

				fprintf(stderr, "rpmem_close: %s\n", rpmem_errormsg());
				return 1;
		}

		return 0;
}
