#define MEDIACONTROLS()                                              \
	{ 0, XF86XK_AudioNext, spawn, { .v = next_media } },         \
		{ 0, XF86XK_AudioPrev, spawn, { .v = prev_media } }, \
	{                                                            \
		0, XF86XK_AudioPlay, spawn,                          \
		{                                                    \
			.v = pause_media                             \
		}                                                    \
	}

static const char *next_media[] = { "playerctl", "next", NULL };
static const char *prev_media[] = { "playerctl", "previous", NULL };
static const char *pause_media[] = { "playerctl", "play-pause", NULL };
