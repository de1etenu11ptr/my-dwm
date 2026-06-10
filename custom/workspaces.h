#define SPAWNWORKSPACE(NO)                                    \
	{                                                     \
		MODKEY | ShiftMask, XK_slash, spawnworkspace, \
		{                                             \
			.i = NO                               \
		}                                             \
	}

/* `kitty --class <class>` alone sets the *instance name* and *class name* to the same value
 * `kitty --name <name>` sets the *instance name*
 * `kitty --class <class> --name <name>` sets the *instance name* to <name> and the *class name* to <class>
 */
#define KITTEN(CLASS, NAME, PROGRAM, ...)                             \
	{ "kitty", "--hold",	  "--directory", "~",	   "--title", \
	  "main",  "--class",	  CLASS,	 "--name", NAME,      \
	  PROGRAM, ##__VA_ARGS__, NULL }

struct Workspace {
	char *name;
	const int nprograms;
	const char ***programs;
	const char **programinstances;
	const int nrules;
	const Rule *rules;
};

static const char *ws1main[] = KITTEN(
	"terminalwork", "main", "tail", "-n", "10",
	"-f", ".logs/dwm/tty2.logs", NULL);
static const char *ws1stats[] = KITTEN("terminalwork", "stats", "btop", NULL);
static const Rule ws1rules[] = {
	/* WM_CLASS(STRING) = instance, class */
	/* WM_NAME(STRING) = title */
	/* monitor -1 is the primary display, 0 is the second, and so on. */
	{ .class = "terminalwork",
	  .instance = "main",
	  .title = NULL,
	  .tags = 0,
	  .isfloating = 0,
	  .monitor = -1 },
	{ .class = "terminalwork",
	  .instance = "stats",
	  .title = NULL,
	  .tags = 0,
	  .isfloating = 0,
	  .monitor = -1 },
};
static const struct Workspace ws1 = {
	.name = "terminalwork",
	.nprograms = 2,
	.programs = (const char **[]){ ws1stats, ws1main },
	.rules = ws1rules
};

static int nworkspaces = 1;
static const struct Workspace workspaces[] = { ws1 };

void
applyworkspacerules(const Rule *rules, int nrules)
{
}

void
spawnworkspace(const Arg *arg)
{
	int emptymaskpos;

	if (arg->i >= nworkspaces) {
		errorprint(
			"only %d workspaces are available (requested %d which does not exist in interval [1, %d])\n",
			nworkspaces, arg->i + 1, nworkspaces);
		return;
	}
	const struct Workspace *w = workspaces + arg->i;

	if ((emptymaskpos = getfreetagpos()) == -1) {
		debugprint("no tag with zero clients was found\n");
		return;
	}

	sendalltag(1 << 0, 1 << emptymaskpos);
	view(&(const Arg){ .ui = 1 << 0 });
	setlayout(&(const Arg){ .v = &layouts[0] });
	applyworkspacerules(w->rules, w->nrules);

	spawnprograms(w->programs, w->nprograms);
}
