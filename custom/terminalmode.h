#define TERMINALMODE() \
	{ MODKEY | ShiftMask, XK_t, toggleterminalmode, { 0 } }

static int terminalmode = 0;

void toggleterminalmode() {
	terminalmode = terminalmode ? 0 : 1;
}
