#include <X11/XF86keysym.h>
#include <X11/keysym.h>
#include <stdint.h>

#define DWMDEF static const

/* appearance */
DWMDEF uint32_t borderpx  = 1;        /* border pixel of windows */
DWMDEF uint32_t snap      = 32;       /* snap pixel */
DWMDEF int showbar        = 1;        /* 0 means no bar */
DWMDEF int topbar         = 1;        /* 0 means bottom bar */
DWMDEF char dmenufont[]   = "monospace:size=8";
DWMDEF char *fonts[]      = { dmenufont };
DWMDEF char col_gray1[]   = "#222222";
DWMDEF char col_gray2[]   = "#444444";
DWMDEF char col_gray3[]   = "#bbbbbb";
DWMDEF char col_gray4[]   = "#eeeeee";
DWMDEF char col_cyan[]    = "#005577";
DWMDEF char *colors[][3]  = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
DWMDEF char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

DWMDEF Rule rules[] = {
	/* xprop(1):
	   WM_CLASS(STRING) = instance, class
	   WM_NAME(STRING) = title
	*/
	/* class                 instance               title                  tags mask  isfloating  monitor */
	{ "Gimp",                NULL,                  NULL,                  0,         1,          -1 },
	{ "Firefox",             NULL,                  NULL,                  0,         0,          -1 },
	{ "Obsidian",            NULL,                  NULL,                  0,         1,          -1 },
	{ "obs",                 NULL,                  NULL,                  0,         1,          -1 },
	{ "pavucontrol",         NULL,                  NULL,                  0,         1,          -1 },
	{ "Spotify",             NULL,                  NULL,                  0,         1,          -1 },
	{ "Pcmanfm",             NULL,                  NULL,                  0,         1,          -1 },
	{ NULL,                  NULL,                  "Calculator",          0,         1,          -1 },

};

/* layout(s) */
DWMDEF float mfact     = 0.55f; /* factor of master area size [0.05..0.95] */
DWMDEF int nmaster     = 1;     /* number of clients in master area */
DWMDEF int resizehints = 1;     /* 1 means respect size hints in tiled resizals */
DWMDEF int lockfullscreen = 1;  /* 1 will force focus on the fullscreen window */
DWMDEF int refreshrate = 120;   /* refresh rate (per second) for client move/resize */

DWMDEF Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]   = "0"; /* component of dmenucmd, manipulated in spawn() */
DWMDEF char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
DWMDEF char *rebootcmd[]  = { "sudo", "shutdown", "-r", "+0", NULL };
DWMDEF char *termcmd[]    = { "xterm", NULL };
DWMDEF char *browsercmd[] = { "firefox", NULL };

/* PipeWire volume commands */
DWMDEF char wpctl[]  = "/usr/bin/wpctl";
DWMDEF char *upvol[]   = { wpctl, "set-volume", "@DEFAULT_AUDIO_SINK@", "5%+",    NULL };
DWMDEF char *downvol[] = { wpctl, "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-",    NULL };
DWMDEF char *mutevol[] = { wpctl, "set-mute",   "@DEFAULT_AUDIO_SINK@", "toggle", NULL };

/* Audio control commands */
DWMDEF char playerctl[] = "/usr/bin/playerctl";
DWMDEF char *audiostop[] = { playerctl, "stop",       NULL };
DWMDEF char *audioprev[] = { playerctl, "previous",   NULL };
DWMDEF char *audioplay[] = { playerctl, "play-pause", NULL };
DWMDEF char *audionext[] = { playerctl, "next",       NULL };


DWMDEF Key keys[] = {
	/* modifier,        key,                     function,       argument */
	{ 0,                XF86XK_AudioRaiseVolume, spawn,          { .v = upvol      } },
	{ 0,                XF86XK_AudioLowerVolume, spawn,          { .v = downvol    } },
	{ 0,                XF86XK_AudioMute,        spawn,          { .v = mutevol    } },
	{ 0,                XF86XK_AudioStop,        spawn,          { .v = audiostop  } },
	{ 0,                XF86XK_AudioPrev,        spawn,          { .v = audioprev  } },
	{ 0,                XF86XK_AudioPlay,        spawn,          { .v = audioplay  } },
	{ 0,                XF86XK_AudioNext,        spawn,          { .v = audionext  } },
	{ MODKEY,           XK_p,                    spawn,          { .v = dmenucmd   } },
	{ MODKEY|ShiftMask, XK_Return,               spawn,          { .v = termcmd    } },
	{ MODKEY|ShiftMask, XK_f,                    spawn,          { .v = browsercmd } },
	{ MODKEY,           XK_b,                    togglebar,      { 0} },
	{ MODKEY,           XK_j,                    focusstack,     { .i = +1 } },
	{ MODKEY,           XK_k,                    focusstack,     { .i = -1 } },
	{ MODKEY,           XK_i,                    incnmaster,     { .i = +1 } },
	{ MODKEY,           XK_d,                    incnmaster,     { .i = -1 } },
	{ MODKEY,           XK_g,                    setmfact,       { .f = -0.05 } },
	{ MODKEY,           XK_h,                    setmfact,       { .f = +0.05 } },
	{ MODKEY,           XK_Return,               zoom,           { 0 } },
	{ MODKEY,           XK_Tab,                  view,           { 0 } },
	{ MODKEY|ShiftMask, XK_c,                    killclient,     { 0 } },
	{ MODKEY,           XK_t,                    setlayout,      { .v = &layouts[0] } },
	{ MODKEY,           XK_f,                    setlayout,      { .v = &layouts[1] } },
	{ MODKEY,           XK_m,                    setlayout,      { .v = &layouts[2] } },
	{ MODKEY,           XK_space,                setlayout,      { 0 } },
	{ MODKEY|ShiftMask, XK_space,                togglefloating, { 0 } },
	{ MODKEY,           XK_0,                    view,           { .ui = ~0 } },
	{ MODKEY|ShiftMask, XK_0,                    tag,            { .ui = ~0 } },
	{ MODKEY,           XK_comma,                focusmon,       { .i = -1 } },
	{ MODKEY,           XK_period,               focusmon,       { .i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,                tagmon,         { .i = -1 } },
	{ MODKEY|ShiftMask, XK_period,               tagmon,         { .i = +1 } },
	TAGKEYS(            XK_1,                                    0)
	TAGKEYS(            XK_2,                                    1)
	TAGKEYS(            XK_3,                                    2)
	TAGKEYS(            XK_4,                                    3)
	TAGKEYS(            XK_5,                                    4)
	TAGKEYS(            XK_6,                                    5)
	TAGKEYS(            XK_7,                                    6)
	TAGKEYS(            XK_8,                                    7)
	TAGKEYS(            XK_9,                                    8)
	{ MODKEY|ShiftMask, XK_q,                    quit,           { 0 } },
	{ MODKEY|ShiftMask, XK_Delete,               spawn,          { .v = rebootcmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
DWMDEF Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

