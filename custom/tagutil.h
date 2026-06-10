void
sendalltag(int from, int to)
{
	/* `TAGMASK` is just a bit mask of all the available tags.
	 * `from & TAGMASK` ensures that the `from` mask (the tags)
	 * are valid in the display. */
	if (!(from & TAGMASK) || !(to & TAGMASK))
		return;
	int i, z;
	i = z = 0;
	while ((to >> i) != 1)
		i++;
	while ((from >> z) != 1)
		z++;
	Monitor *m;
	Client *c;
	Client *next;

	m = selmon;
	for (c = m->clients; c; c = next) {
		next = c->next;
		/* Checking if `c` has the tags we would like to move
		 * and that they are valid if they do */
		if ((c->tags & from) & TAGMASK) {
			/* From `void tag(const Arg *arg)` in `dwm.c` */
			/* Overrides all its tags and keeps only one tag,
			 * the dest tag */
			c->tags = to & TAGMASK;
			focus(NULL);
			arrange(m);
		}
	}
}

int
getfreetagpos()
{
	Monitor *m;
	Client *c;
	unsigned int i;
	unsigned int size;
	int emptytag;

	i = 0;
	emptytag = -1;
	size = sizeof(tags) / sizeof(char *);

	for (; i < size; i++) {
		unsigned int tag = 1 << i;
		m = selmon;
		for (c = m->clients; c; c = c->next)
			if (c->tags & tag)
				goto tag_occupied;
		emptytag = i;
		break;
	tag_occupied:;
	}
	return emptytag;
}
