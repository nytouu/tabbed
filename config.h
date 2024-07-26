/* See LICENSE file for copyright and license details. */

/* appearance */
static char* font         = "Torus Pro:size=10";
static char* normbgcolor  = "#1D1D1D";
static char* normfgcolor  = "#393939";
static char* selbgcolor   = "#1D1D1D";
static char* selfgcolor   = "#93DDC2";
static char* urgbgcolor   = "#1D1D1D";
static char* urgfgcolor   = "#F66151";
static char before[]      = "<";
static char after[]       = ">";
static char titletrim[]   = "...";
static int  tabwidth      = 200;
static int  focusnew       = 1;
static int urgentswitch   = 0;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int newposition   = 0;
static int npisrelative  = 0;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

ResourcePref resources[] = {
	{ "font",         STRING,  &font},
	{ "normbgcolor",  STRING,  &normbgcolor},
	{ "normfgcolor",  STRING,  &normfgcolor},
	{ "selbgcolor",   STRING,  &selbgcolor},
	{ "selfgcolor",   STRING,  &selfgcolor},
	{ "urgbgcolor",   STRING,  &urgbgcolor},
	{ "urgfgcolor",   STRING,  &urgfgcolor},
	{ "before",       STRING,  &before},
	{ "after",        STRING,  &after},
	{ "titletrim",    STRING,  &titletrim},
	{ "tabwidth",     INTEGER, &tabwidth},
	{ "focusnew",     INTEGER, &focusnew},
	{ "urgentswitch", INTEGER, &urgentswitch},
	{ "newposition",  INTEGER, &newposition},
	{ "npisrelative", INTEGER, &npisrelative},
};

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
