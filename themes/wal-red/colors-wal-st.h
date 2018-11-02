const char *colorname[] = {

  /* 8 normal colors */
  [0] = "#09040c", /* black   */
  [1] = "#2f12a2", /* red     */
  [2] = "#ab1319", /* green   */
  [3] = "#e72e27", /* yellow  */
  [4] = "#e7612e", /* blue    */
  [5] = "#e51a25", /* magenta */
  [6] = "#e98e38", /* cyan    */
  [7] = "#f3c98a", /* white   */

  /* 8 bright colors */
  [8]  = "#aa8c60",  /* black   */
  [9]  = "#2f12a2",  /* red     */
  [10] = "#ab1319", /* green   */
  [11] = "#e72e27", /* yellow  */
  [12] = "#e7612e", /* blue    */
  [13] = "#e51a25", /* magenta */
  [14] = "#e98e38", /* cyan    */
  [15] = "#f3c98a", /* white   */

  /* special colors */
  [256] = "#09040c", /* background */
  [257] = "#f3c98a", /* foreground */
  [258] = "#f3c98a",     /* cursor */
};

/* Default colors (colorname index)
 * foreground, background, cursor */
 unsigned int defaultbg = 0;
 unsigned int defaultfg = 257;
 unsigned int defaultcs = 258;
 unsigned int defaultrcs= 258;
