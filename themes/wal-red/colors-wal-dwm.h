static const char norm_fg[] = "#f3c98a";
static const char norm_bg[] = "#09040c";
static const char norm_border[] = "#aa8c60";

static const char sel_fg[] = "#f3c98a";
static const char sel_bg[] = "#ab1319";
static const char sel_border[] = "#f3c98a";

static const char urg_fg[] = "#f3c98a";
static const char urg_bg[] = "#2f12a2";
static const char urg_border[] = "#2f12a2";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
