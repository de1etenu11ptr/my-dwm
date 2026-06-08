void
spawnprograms(const char ***programs, int nprograms)
{
	int i;
	for (i = 0; i < nprograms; i++) {
		debugprint("spawning \"%s\".\n", programs[i][0]);
		spawn(&(const Arg){ .v = programs[i] });
		sleep(1);
	}
}
