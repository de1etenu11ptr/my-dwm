#define DYNAMICMENU() { MODKEY, XK_p, spawn, { .v = dmenucmd } },
#define TERMINALLAUNCH() \
	{ MODKEY | ShiftMask, XK_Return, spawn, { .v = termcmd } },

static const char *dmenucmd[] = { "/home/electro/bin/dmenu_cached",
				  "-m",
				  dmenumon,
				  "-fn",
				  dmenufont,
				  "-nb",
				  col_pl_deep,
				  "-nf",
				  col_pl_mauve,
				  "-sb",
				  col_pl_plum,
				  "-sf",
				  col_pl_pink,
				  NULL };
static const char *termcmd[] = { "kitty", NULL };

/* TODO: Implement a terminal mode which has submappings
 * for different **terminal** programs/scripts */
