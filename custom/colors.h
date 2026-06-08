/* Default Scheme Colors */
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";

/* Powder Pink + Burgundy */
static const char col_pp_pink[] = "#f2c4ce"; /* powder pink - fg */
static const char col_pp_burgundy[] = "#6b2737"; /* burgundy - bg/accent */
static const char col_pp_blush[] = "#d4a0aa"; /* muted blush - subtle fg */
static const char col_pp_deep[] = "#4a1525"; /* deep burgundy - border */

/* Plum + Pink */
static const char col_pl_pink[] = "#f7b8d2"; /* soft pink - fg */
static const char col_pl_plum[] = "#5c3354"; /* plum - bg/accent */
static const char col_pl_mauve[] = "#c9a0bc"; /* muted mauve - subtle fg */
static const char col_pl_deep[] = "#3d1f38"; /* deep plum - border */

/* Brown + Orange */
static const char col_br_orange[] = "#e8956d"; /* warm orange - fg */
static const char col_br_brown[] = "#4a2f1a"; /* warm brown - bg/accent */
static const char col_br_sand[] = "#c4956a"; /* sandy - subtle fg */
static const char col_br_deep[] = "#2e1a0a"; /* deep brown - border */

static const char *colors[][3] = {
	/*                      fg               bg                border */
	[SchemeNorm] = { col_gray3,	    col_gray1,       col_gray2	 },
	[SchemeSel] = { col_gray4,	   col_cyan,	     col_cyan	      },

	/* Powder Pink + Burgundy */
	[SchemePPNorm] = { col_pp_blush,	 col_pp_deep,     col_pp_burgundy },
	[SchemePPSel] = { col_pp_pink,   col_pp_burgundy, col_pp_pink	    },

	/* Plum + Pink */
	[SchemePLNorm] = { col_pl_mauve,	 col_pl_deep,     col_pl_plum	  },
	[SchemePLSel] = { col_pl_pink,   col_pl_plum,	    col_pl_pink	},

	/* Brown + Orange */
	[SchemeBRNorm] = { col_br_sand,	col_br_deep,     col_br_brown	  },
	[SchemeBRSel] = { col_br_orange, col_br_brown,    col_br_orange   },
};
