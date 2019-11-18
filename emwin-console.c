
#include "GUI.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static int console_curx;
static int console_cury;

static int console_topBuffer=0;
static int console_insertLine=0;

static int console_rowsMax;
static int console_columnsMax;
static char **console_textBuffer;

static bool console_updateMode = true;

void console_setUpdateMode(bool mode)
{
    console_updateMode = mode;
}

void console_dumpBuffer()
{
    GUI_GotoXY(0,0);
    int currentLine;

    for(int i=0;i<console_rowsMax;i++)
    {
        currentLine = (console_topBuffer + i) % console_rowsMax;
        GUI_DispString(console_textBuffer[currentLine]);
        GUI_DispCEOL();
        GUI_DispString("\n");
    }
}

void console_clear()
{
    for(int i=0;i<console_rowsMax;i++)
    {
        memset(console_textBuffer[i],' ',console_columnsMax);
        console_textBuffer[i][console_columnsMax] = 0;
    }
    
    console_topBuffer = 0;

    GUI_Clear();

    console_curx= 0;
    console_cury= 0;
}


void console_scroll()
{
    console_cury += 1;
    if(console_cury == console_rowsMax)
    {
        console_cury = console_rowsMax -1;

        console_topBuffer = (console_topBuffer + 1) % console_rowsMax;

    }
    console_insertLine = (console_topBuffer + console_cury)%console_rowsMax;
    memset(console_textBuffer[console_insertLine],' ',console_columnsMax);

}


void console_print(char *text)
{
#ifdef CONSOLE_DEBUG

    printf("inserting %s at %d\n",text,console_insertLine);
#endif

    char *p=text;
    while(*p)
    {
        if(*p == '\r')
        {
            // ignore
        }
        else if(*p == '\n')
        {
            for(int i=console_curx;i<console_columnsMax;i++)
            {
                console_textBuffer[console_insertLine][i] = ' ';
            }
            console_curx = 0;
            console_scroll();
        }
        else
        {
            console_textBuffer[console_insertLine][console_curx] = *p;
            console_curx += 1;
            if(console_curx == console_columnsMax) // Move to the next row
            {
                console_curx = 0;
                console_scroll();
            }
        }
        p++;
    }

    if(console_updateMode)
        console_dumpBuffer();

    //printf("end console firstLine = %d console_numLine %d\n",console_topBuffer,console_numLine);
}

void console_init(const GUI_FONT  *pFont)
{
    GUI_SetTextAlign(GUI_TA_TOP);

    GUI_SetFont(pFont);
    GUI_SetTextAlign(GUI_TA_TOP);
    console_rowsMax = GUI_GetScreenSizeY()/GUI_GetYDistOfFont(pFont);
    console_columnsMax = GUI_GetScreenSizeX()/GUI_GetCharDistX('A');

#ifdef CONSOLE_DEBUG
    printf("-----------------\n");
    printf("Screen X = %d\n",GUI_GetScreenSizeX());
    printf("Screen Y = %d\n",GUI_GetScreenSizeY());
    printf("Font X = %d\n",GUI_GetCharDistX('A'));
    printf("Font Y = %d\n",GUI_GetYDistOfFont(pFont));
    
    printf("Columns = %d\n",console_columnsMax);
    printf("Rows = %d\n",console_rowsMax);
#endif

    console_textBuffer = (char **)malloc(sizeof(char *)*console_rowsMax);
    for(int i=0;i<console_rowsMax;i++)
    {
        console_textBuffer[i]=(char *)malloc(console_columnsMax+1);
    }

    console_clear();


}
