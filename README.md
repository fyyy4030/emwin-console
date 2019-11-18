# emwin-console

The emwin console library provides a console like functionality to a display that is being driven by emwin.  The functionality includes scrolling and printing.

To use the console you must add:
* https://github.com/cypresssemiconductorco/emwin.git
* https://github.com/cypresssemiconductorco/CY8CKIT-028-TFT.git
* https://github.com/iotexpert/emwin-console.git

Then you can then call

```
    GUI_Init();
    GUI_SetColor(GUI_WHITE);
    GUI_SetBkColor(GUI_BLACK);

    console_init(GUI_FONT_8X16_ASCII);
    console_setUpdateMode(true);
    console_print("Hello World");
```

