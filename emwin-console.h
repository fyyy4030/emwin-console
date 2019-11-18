#ifndef EMWIN_CONSOLE_H
#define EMWIN_CONSOLE_H


#ifdef __cplusplus
extern "C"
{
#endif



void console_dumpBuffer();
void console_clear();
void console_scroll();
void console_print(char *text);
void console_init(const GUI_FONT  *pFont);
void console_setUpdateMode(bool mode);

#ifdef __cplusplus
} // extern "C"

#endif

#endif
