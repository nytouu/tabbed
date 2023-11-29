/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "monospace:size=10";
static const char* normbgcolor  = "#1d2021";
static const char* normfgcolor  = "#665c54";
static const char* selbgcolor   = "#1d2021";
static const char* selfgcolor   = "#458588";
static const char* urgbgcolor   = "#1d2021";
static const char* urgfgcolor   = "#fb4934";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 0;
static Bool npisrelative  = False;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

#define MODKEY ControlMask
static const Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY|ShiftMask,     XK_Return, focusonce,   { 0 } },
	{ MODKEY|ShiftMask,     XK_Return, spawn,       { 0 } },

	{ MODKEY|ShiftMask,     XK_j,      rotate,      { .i = +1 } },
	{ MODKEY|ShiftMask,     XK_k,      rotate,      { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_h,      movetab,     { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_l,      movetab,     { .i = +1 } },
	/* { MODKEY,               XK_Tab,    rotate,      { .i = 0 } }, */

	{ MODKEY,               XK_grave,  spawn,       SETPROP("_TABBED_SELECT_TAB") },

	{ MODKEY|ShiftMask,     XK_x,      killclient,  { 0 } },

	{ MODKEY|ShiftMask,     XK_u,      focusurgent, { 0 } },
	/* { MODKEY|ShiftMask,     XK_u,      toggle,      { .v = (void*) &urgentswitch } }, */

	/* { 0,                    XK_F11,    fullscreen,  { 0 } }, */
};
