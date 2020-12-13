/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  =  3;        /* border pixel of windows */
static const unsigned int snap      =  2;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          =  0;        /* 1 means no outer gap when there is only one window */
static const int showbar            =  1;        /* 0 means no bar */
static const int topbar             =  1;        /* 0 means bottom bar */
static const int vertpad            =  5;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "InconsolataGo Nerd Font:size=12" };
static const char dmenufont[]       =   "InconsolataGo Nerd Font:size=14";
/* colors */
static const char col_fg[]	        = "#cbe3e7";
static const char col_bg[]          = "#1e1c31";
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
	/*               fg           bg               border   */
	[SchemeNorm] = { col_cyan14,  col_black8,     col_black0 },
	[SchemeSel]  = { col_black8,  col_magenta5,  col_blue12  },
};

/* tagging */
static const char *tags[] = { " 1   ", " 2   ", " 3   ", " 4   ", " 5   ", " 6   ", " 7   ", " 8   "};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor  float x,y,w,h         floatborderpx*/
  { "kitty",    NULL,       "project",    1 << 1,       0,           -1,    50,50,500,500,        5 },
  { "kitty",    NULL,       "gh-cli",     1 << 2,       1,           -1,    50,50,500,500,        5 },
	{ "Slack",    NULL,       NULL,         1 << 4,       1,           -1,    50,50,500,500,        5 },
	{ "zoom",     NULL,       NULL,         1 << 5,       1,           -1,    50,50,500,500,        5 },
	{ "kitty",    NULL,       "calcurse",   ~0,           1,           -1,    1250,500,500,500,     5 },
	{ "kitty",    NULL,       "neomutt",    1 << 6,       0,           -1,    50,50,500,500,        5 },
	{ "kitty",    NULL,       "newsboat",   1 << 6,       0,           -1,    50,50,500,500,        5 },
	{ "kitty",    NULL,       "gotop",      1 << 7,       1,           -1,    50,50,500,500,        5 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 3;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
  { ":::",      gaplessgrid },
	{ "[M]",      monocle },
  { "[@]",      spiral },
  { "[\\]",     dwindle },
  { "H[]",      deck },
  { "TTT",      bstack },
  { "===",      bstackhoriz },
  { "HHH",      grid },
  { "###",      nrowgrid },
  { "---",      horizgrid },
  { "|M|",      centeredmaster },
  { ">M>",      centeredfloatingmaster },
  { "><>",      NULL },    /* no layout function means floating behavior */
  { NULL,       NULL },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_cyan14, "-nf", col_black0, "-sb", col_magenta13, "-sf", col_cyan6, NULL };
static const char *termcmd[]      = { "kitty", NULL };
static const char *chromiumcmd[]  = { "chromium", NULL };
static const char *slackcmd[]     = { "slack", NULL };
static const char *zoomcmd[]      = { "zoom", NULL };
static const char *gotopcmd[]     = { "kitty", "--title", "gotop", "gotop", NULL };
static const char *nvimcmd[]      = { "kitty", "--title", "nvim", "nvim", NULL };
static const char *calcursecmd[]  = { "kitty", "--title", "calcurse", "calcurse", NULL };
static const char *rangercmd[]    = { "kitty", "--title", "ranger", "ranger", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

/* Spawning Clients */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = rangercmd } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = chromiumcmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = slackcmd } },
	{ MODKEY|ShiftMask,             XK_z,      spawn,          {.v = zoomcmd } },
	{ MODKEY|ShiftMask,             XK_g,      spawn,          {.v = gotopcmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = nvimcmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = calcursecmd } },

/* Client Manipulation Within Current Stack */
  /* Toggle Panel */
  { MODKEY,                       XK_b,      togglebar,      {0} },
  /* Rotating Clients; Focus Unchanged */
  { MODKEY,                       XK_h,      inplacerotate,  {.i = +2} },
  { MODKEY,                       XK_l,      inplacerotate,  {.i = -2} },
  /* Rotating Focus; Stack Unchanged*/
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  /* Rotating Focus And Stack */
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
  /* Rotating Clients In to and Out of Master Stack */
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },

/* Window Manipulation Within Current Stack */
  /* Resize Window */
	{ MODKEY|ControlMask,           XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_j,      setcfact,       {.f = +0.25} }, /* Vertical Expand */
	{ MODKEY|ControlMask,           XK_k,      setcfact,       {.f = -0.25} }, /* Vertical Retract */ { MODKEY|ControlMask,           XK_o,      setcfact,       {.f =  0.00} }, /* Default Size */
  /* Window Layout */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[4]} },
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
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
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

/* Kill Clients */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} }, 
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

/* DEPRECATED or Unnecessary */
  /*
   *Swaps with master 
	 *{ MODKEY,                       XK_Return, zoom,           {0} }, 
   * Resize Horizontal Gaps Between Windows 
   *{ MODKEY|ControlMask,           XK_6,      incrihgaps,     {.i = +1 } },
   *{ MODKEY|ControlMask|ShiftMask, XK_6,      incrihgaps,     {.i = -1 } },
   * Resize Vertical Gaps Between Windows 
   *{ MODKEY|ControlMask,           XK_7,      incrivgaps,     {.i = +1 } },
   *{ MODKEY|ControlMask|ShiftMask, XK_7,      incrivgaps,     {.i = -1 } },
   * Resize Horizontal Gaps Outside Windows 
   *{ MODKEY|ControlMask,           XK_8,      incrohgaps,     {.i = +1 } },
   *{ MODKEY|ControlMask|ShiftMask, XK_8,      incrohgaps,     {.i = -1 } },
   * Resize Vertical Gaps Outside Windows 
   *{ MODKEY|ControlMask,           XK_9,      incrovgaps,     {.i = +1 } },
   *{ MODKEY|ControlMask|ShiftMask, XK_9,      incrovgaps,     {.i = -1 } },
   *{ MODKEY|ShiftMask,             XK_j,      inplacerotate,  {.i = +1} },
   *{ MODKEY|ShiftMask,             XK_k,      inplacerotate,  {.i = -1} },
   */
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
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
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

