#define VOLUMECONTROLS()                                                  \
	{ 0, XF86XK_AudioMute, spawn, { .v = mute_vol } },                \
		{ 0, XF86XK_AudioLowerVolume, spawn, { .v = down_vol } }, \
	{                                                                 \
		0, XF86XK_AudioRaiseVolume, spawn,                        \
		{                                                         \
			.v = up_vol                                       \
		}                                                         \
	}

static const char *up_vol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@",
				"+10%", NULL };
static const char *down_vol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@",
				  "-10%", NULL };
static const char *mute_vol[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@",
				  "toggle", NULL };
