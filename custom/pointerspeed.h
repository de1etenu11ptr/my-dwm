#define POINTERSPEED()                                                    \
	{ MODKEY, XK_backslash, setpointerspeed, { .i = 1 } },            \
		{ MODKEY, XK_bracketright, setpointerspeed, { .i = 2 } }, \
	{                                                                 \
		MODKEY, XK_bracketleft, setpointerspeed, { .i = 3 }       \
	}
#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
/* in ms */
#define REFRESH 2000

struct Point {
	int x;
	int y;
};

static double pointerscale = 1.0;

Monitor *
crecttomon(int x, int y, int w, int h)
{
	Monitor *m, *r = NULL;
	int a, area = 0;

	for (m = mons; m; m = m->next)
		if ((a = INTERSECT(x, y, w, h, m)) > area) {
			area = a;
			r = m;
		}
	return r;
}

void
boundedcoordinates(struct Point *cur, struct Point *prev)
{
	Monitor *m;

	/* try to find if the current (x, y) fall into a monitor */
	m = crecttomon(cur->x, cur->y, 1, 1);

	/* fallback to the previous (x, y) since they SHOULD fall into one
	 * and if not will default to the selected monitor by dwm's implementation */
	if (!m)
		m = recttomon(prev->x, prev->y, 1, 1);

	cur->x = CLAMP(cur->x, m->mx, m->mx + m->mw);
	cur->y = CLAMP(cur->y, m->my, m->my + m->mh);
}

void
scalepointermotion(struct Point *prev)
{
	struct Point cur, delta, target;
	int tmp;
	unsigned int mask;
	Window dummy;

	XQueryPointer(dpy, root, &dummy, &dummy, &cur.x, &cur.y, &tmp, &tmp,
		      &mask);
	if (prev->x == -1 && prev->y == -1) {
		prev->x = cur.x;
		prev->y = cur.y;
		return;
	}

	delta.x = cur.x - prev->x;
	delta.y = cur.y - prev->y;
	if (delta.x != 0 || delta.y != 0) {
		target.x = prev->x + (int)(delta.x * pointerscale);
		target.y = prev->y + (int)(delta.y * pointerscale);
		boundedcoordinates(&target, prev);

		XWarpPointer(dpy, None, root, 0, 0, 0, 0, target.x, target.y);

		XFlush(dpy);
		prev->x = target.x;
		prev->y = target.y;
	}
}

/* arg->i will be what determines how we are adjusting the speed */
void
setpointerspeed(const Arg *arg)
{
	switch (arg->i) {
	case 1:
		pointerscale = 1.0;
		break;
	case 2:
		pointerscale += 0.1;
		break;
	case 3:
		if (pointerscale > 0.1)
			pointerscale -= 0.1;
		break;
	default:
		printerror(
			"invalid modifier passed for setting pointer speed (%d)\n",
			arg->i);
		return;
	}
	pointerscale = MAX(0.1, MIN(pointerscale, 10.0));
	printdebug("set pointerscale to %.2f\n", pointerscale);
}
