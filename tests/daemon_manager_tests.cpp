#include <criterion/criterion.h>
#include <new>
#include "../lib/DaemonManager.hpp"

TestSuite(daemon_manager, .description = "Suite for testing the DaemonManager class");

Test(daemon_manager, lockFile_creation_and_deletion) {
	DaemonManager *const manager = new(std::nothrow) DaemonManager();
	cr_assert(manager != nullptr,  "Failed to create a DaemonManager");

	cr_assert(access(DaemonManager::lockfile_fullpath.c_str(), F_OK) == 0, "Failed to create lockfile, %s", strerror(errno));
	delete (manager);
	cr_assert(access(DaemonManager::lockfile_fullpath.c_str(), F_OK) != 0, "Lockfile created but not deleted");
}
