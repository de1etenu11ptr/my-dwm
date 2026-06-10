void
spawnprograms(const char ***programs, int nprograms)
{
	int i;
	for (i = 0; i < nprograms; i++) {
		spawn(&(const Arg){ .v = programs[i] });
		sleep(1);
	}
}
