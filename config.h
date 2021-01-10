/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  =  4;        /* border pixel of windows */
static const unsigned int snap      =  2;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static       int smartgaps          =  0;        /* 1 means no outer gap when there is only one window */
static const int showbar            =  1;        /* 0 means no bar */
static const int topbar             =  1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "SpaceMono Nerd Font:size=12:antialias=true" };
static const char dmenufont[]       =   "SpaceMono Nerd Font:size=13:antialias=true:hinting=slight";
/* colors */
static const char col_bg[]	        = "#cbe3e7";
static const char col_fg[]          = "#1e1c31";
/* Row for kitty copypasta */
/* black */                                               
static const char col_black0[]      = "#565575";
static const char col_black8[]      = "#100e23";
/* red */                                                 
static const char col_red1[]        = "#ff8080";
static const char col_red9[]        = "#ff5458";
/* green */                                               
static const char col_green2[]      = "#95ffa4";
static const char col_green10[]     = "#62d196";
/* yellow */                                  
static const char col_yellow3[]     = "#ffe9aa";
static const char col_yellow11[]    = "#ffb378";
/* blue */                                    
static const char col_blue4[]       = "#91ddff";
static const char col_blue12[]      = "#65b2ff";
/* magenta */                                 
static const char col_magenta5[]    = "#c991e1";
static const char col_magenta13[]   = "#906cff";
/* cyan */                                    
static const char col_cyan6[]       = "#aaffe4";
static const char col_cyan14[]      = "#63f2f1";
/* white */                                   
static const char col_white7[]      = "#cbe3e7";
static const char col_white15[]     = "#a6b3cc";

static const char *colors[][3]      = {
/*                     fg              bg        border   */
	[SchemeNorm] = {        col_bg, col_black0,  col_black8 },
	[SchemeSel]  = { col_magenta13,  col_cyan6,   col_cyan6 },
};

/* tagging */
static const char *tags[]    = { "  1  ﯥ  ", " 2  ﱮ  ", " 3  ﱮ  ", " 4  ﱮ  ", " 5  ﱮ  ", " 6  轢  ", " 7  ﱩ  " };
static const char *alttags[] = { "  1    ", " 2  פּ  ", " 3  參 ", " 4  聆 ", " 5    ", " 6  歷  ", " 7  ﱩ  " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
/*      class    inst     title       tags  sw flt mn fl x,y,w,h    fltb*/
 { "qutebrowser", NULL,       NULL,  1 << 0, 0, 0, 1, 50,50,500,500, 2 },
/* {      "filing", NULL,   "ranger",  1 << 1, 2, 0, -1, 1250,855,700,730, 2 }, */
 {        "feed", NULL,  "neomutt",  1 << 2, 3, 0, 1, 50,50,500,500, 2 },
 {        "feed", NULL, "newsboat",  1 << 2, 3, 0, 1, 50,30,500,500, 2 },
 {       "Slack", NULL,       NULL,  1 << 3, 4, 1, 1, 30,50,950,850, 2 },
 {        "zoom", NULL,       NULL,  1 << 4, 5, 1, 1, 1250,50,950,850, 2 },
 {       "XTerm", NULL,   "server",  1 << 5, 6, 0, 1, 50,50,500,500, 2 },
 {      "system", NULL,    "gotop",  1 << 6, 7, 1, 1, 950,50,800,900, 2 },
 {      "filing", NULL,   "ranger",       0, 0, 1, 1, 950,655,900,730, 2 },
 {      "filing", NULL,     "term",       0, 0, 1, 1, 950,655,900,730, 2 },
 {     "editing", NULL, "note-pad",       0, 0, 1, 1, 950,655,900,730, 2 },
 {        "feed", NULL, "calcurse",       0, 0, 1, 1, 950,30,900,700, 2 },
};

/* layout(s) */
static const float mfact         = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster         =    1; /* number of clients in master area */
static const int resizehints     =    1; /* 1 means respect size hints in tiled resizals */
static const int attachdirection =    3; /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */

static const Layout layouts[] = {
/* symbol  arrange function */
 {  "   ",    tile },    /* first entry is default */
 {  " ﱡ  ", monocle },
 {  "   ",    NULL },    /* no layout function means floating behavior */
 {    NULL,    NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, 

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_magenta5, "-sf", col_white15, NULL };
static const char *webcmd[]      = { "qutebrowser", "reddit.com", NULL };
static const char *zoomcmd[]     = { "zoom", NULL };
static const char *servercmd[]   = { "xterm", "-T",   "server", "-e", "remote-server", NULL };
static const char *slackcmd[]    = { "kitty", "-T",    "Slack", "--class", "slack", "weechat", NULL };
static const char *gotopcmd[]    = { "kitty", "-T",    "gotop", "--class", "system", "gotop", NULL };
static const char *rangercmd[]   = { "kitty", "-T",   "ranger", "--class", "filing", "ranger", NULL };
static const char *calcursecmd[] = { "kitty", "-T", "calcurse", "--class", "feed", "calcurse", NULL };
static const char *neomuttcmd[]  = { "kitty", "-T",  "neomutt", "--class", "feed", "neomutt", NULL };
static const char *newsboatcmd[] = { "kitty", "-T", "newsboat", "--class", "feed", "newsboat", NULL };
static const char *termcmd[]     = { "kitty", "-T",     "term", "--class", "filing", NULL };
static const char *scratchcmd[]  = { "kitty", "-T", "note-pad", "--class", "editing", "nvim", "/home/christian/dox/notes/new-note", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

/* Spawning Clients */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = rangercmd } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = webcmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = slackcmd } },
	{ MODKEY|ShiftMask,             XK_z,      spawn,          {.v = zoomcmd } },
	{ MODKEY|ShiftMask,             XK_g,      spawn,          {.v = gotopcmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = calcursecmd } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = newsboatcmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = neomuttcmd } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = scratchcmd } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = servercmd } },

/* Client Manipulation */
  /* Toggle Panel */
  { MODKEY,                       XK_b,      togglebar,      {0} },
  /* Rotating Clients; Focus Unchanged */
  { MODKEY,                       XK_h,      inplacerotate,  {.i = -2} },
  { MODKEY,                       XK_l,      inplacerotate,  {.i = +2} },
  /* Rotating Focus; Stack Unchanged*/
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  /* Rotating Focus And Stack */
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
  /* Rotating Clients In to and Out of Master Stack */
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },
/* Kill Focused Client */
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

/* Window Manipulation */
  /* Resize Window */
	{ MODKEY|ControlMask,           XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_j,      setcfact,       {.f = +0.25} }, /* Vertical Expand */
	{ MODKEY|ControlMask,           XK_k,      setcfact,       {.f = -0.25} }, /* Vertical Retract */
  { MODKEY|ControlMask,           XK_o,      setcfact,       {.f =  0.00} }, /* Default Size */
  /* Window Layout */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
  /* Resize All Gaps */
  { MODKEY|ControlMask,           XK_u,      incrgaps,       {.i = +1 } },
  { MODKEY|ControlMask|ShiftMask, XK_u,      incrgaps,       {.i = -1 } },
  /* Resize Gaps Between Windows */
  { MODKEY|ControlMask,           XK_i,      incrigaps,      {.i = +1 } },
  { MODKEY|ControlMask|ShiftMask, XK_i,      incrigaps,      {.i = -1 } },
  /* Resize Gaps Outside Windows */
  { MODKEY|ControlMask,           XK_o,      incrogaps,      {.i = +1 } },
  { MODKEY|ControlMask|ShiftMask, XK_o,      incrogaps,      {.i = -1 } },
  /* Toggle Gaps */
  { MODKEY|ControlMask,           XK_0,      togglegaps,     {0} },
  { MODKEY|ControlMask|ShiftMask, XK_0,      defaultgaps,    {0} },
/* Kill Window Manager */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} }, 

/* Tags */
  /* Viewing Tags 
   *   +ShiftMask, XK_(N) adds tags to selected client */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
 /* View Previous Tag*/
	{ MODKEY,                       XK_Tab,    view,           {0} },
  /* View All Tags */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  /* Tag All Clients*/
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  /* Focusing Monitors */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  /* Tagging Monitors */
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
};


/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,         Button4,        resizemousescroll, {.v = &scrollargs[0]} },
	{ ClkClientWin,         MODKEY,         Button5,        resizemousescroll, {.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,         Button6,        resizemousescroll, {.v = &scrollargs[2]} },
	{ ClkClientWin,         MODKEY,         Button7,        resizemousescroll, {.v = &scrollargs[3]} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

