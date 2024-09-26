/* SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

__attribute__((noreturn)) void die(const char *message)
{
	fprintf(stderr, "error: %s\n", message);
	exit(2);
}

int main(void)
{
	char buff[1024];
	char cmd[1024];
	FILE *prog;
	char *s;

	/* Guess whether we are run in emulation by resolving /proc/self/exe
	 * and matching its basename against our expected program name. We need
	 * to fork another non-emulated process to avoid getting our readlink
	 * syscall emulated too well and assume that coreutils' readlink is not
	 * emulated.
	 */
	snprintf(cmd, sizeof(cmd), "readlink -n /proc/%d/exe", getpid());
	prog = popen(cmd, "r");
	if (!prog)
		die("failed to spawn readlink");
	if (!fgets(buff, sizeof(buff), prog))
		die("failed to read output of readlink");
	if (pclose(prog))
		die("readlink failed");
	s = strrchr(buff, '/');
	if (s)
		++s;
	else
		s = buff;
	return !!strcmp(s, "cross-exe-test");
}
