void *
safe_malloc(size_t size)
{
	if (size <= 0) {
		fprintf(stderr, "%stried to pass 0 to malloc.\n", ERRORTAG);
		exit(EXIT_FAILURE);
	}
	void *ptr = malloc(size);
	if (ptr == NULL && size > 0) {
		fprintf(stderr, "%sfailed to malloc.\n", ERRORTAG);
		exit(EXIT_FAILURE);
	}
	return ptr;
}
