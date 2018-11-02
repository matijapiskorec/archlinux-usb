static const char norm_fg[] = "#d4d5d8";
static const char norm_bg[] = "#0a0a0a";
static const char norm_border[] = "#949597";

static const char sel_fg[] = "#d4d5d8";
static const char sel_bg[] = "#e51a1a";
static const char sel_border[] = "#d4d5d8";

static const char urg_fg[] = "#d4d5d8";
static const char urg_bg[] = "#2183e6";
static const char urg_border[] = "#2183e6";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
