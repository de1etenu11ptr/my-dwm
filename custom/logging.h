void
setfallbacktimestamp(char *str)
{
	str[0] = '[';
	memset(str + 1, '0', 8);
	str[9] = ' ';
	memset(str + 10, '0', 2);
	str[12] = ':';
	memset(str + 13, '0', 2);
	str[15] = ':';
	memset(str + 16, '0', 2);
	str[18] = ']';
	str[19] = '\0';
}

char *
gettimestamp()
{
	struct timespec tp;
	struct tm *tm;
	char *str = safe_malloc(sizeof(char) * timestamp_len + 1);
	if (clock_gettime(CLOCK_REALTIME, &tp) == -1) {
		setfallbacktimestamp(str);
		return str;
	}
	if (!(tm = localtime(&tp.tv_sec))) {
		setfallbacktimestamp(str);
		return str;
	}
	strftime(str, timestamp_len + 1, timestamp_fmt, tm);
	str[timestamp_len] = '\0';

	return str;
}

/* prints to `stream` and flushes immediately after
 */
void
dprint(FILE *stream, const char *ctag, const char *fmt, va_list args)
{
	char *timestamp = gettimestamp();
	const int ctag_len = strlen(ctag);
	const int fmt_len = strlen(fmt);
	const int format_len = timestamp_len + ctag_len + fmt_len;
	char *format;

	format = safe_malloc(sizeof(char) * format_len + 1);
	memcpy(format, timestamp, timestamp_len);
	memcpy(format + timestamp_len, ctag, ctag_len);
	memcpy(format + timestamp_len + ctag_len, fmt, fmt_len);
	format[format_len] = '\0';

	vfprintf(stream, format, args);
	fflush(stream);

	free(format);
	free(timestamp);
}

void
printdebug(const char *fmt, ...)
{
	const char *ctag = DEBUGTAG;
	va_list args;

	va_start(args, fmt);
	dprint(stdout, ctag, fmt, args);
	va_end(args);
}

void
printerror(const char *fmt, ...)
{
	const char *ctag = ERRORTAG;
	va_list args;

	va_start(args, fmt);
	dprint(stderr, ctag, fmt, args);
	va_end(args);
}
