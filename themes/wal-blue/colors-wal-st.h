const char *colorname[] = {

  /* 8 normal colors */
  [0] = "#0a0a0a", /* black   */
  [1] = "#2183e6", /* red     */
  [2] = "#e51a1a", /* green   */
  [3] = "#358ee8", /* yellow  */
  [4] = "#4b96eb", /* blue    */
  [5] = "#5998ec", /* magenta */
  [6] = "#738cef", /* cyan    */
  [7] = "#d4d5d8", /* white   */

  /* 8 bright colors */
  [8]  = "#949597",  /* black   */
  [9]  = "#2183e6",  /* red     */
  [10] = "#e51a1a", /* green   */
  [11] = "#358ee8", /* yellow  */
  [12] = "#4b96eb", /* blue    */
  [13] = "#5998ec", /* magenta */
  [14] = "#738cef", /* cyan    */
  [15] = "#d4d5d8", /* white   */

  /* special colors */
  [256] = "#0a0a0a", /* background */
  [257] = "#d4d5d8", /* foreground */
  [258] = "#d4d5d8",     /* cursor */
};

/* Default colors (colorname index)
 * foreground, background, cursor */
 unsigned int defaultbg = 0;
 unsigned int defaultfg = 257;
 unsigned int defaultcs = 258;
 unsigned int defaultrcs= 258;
