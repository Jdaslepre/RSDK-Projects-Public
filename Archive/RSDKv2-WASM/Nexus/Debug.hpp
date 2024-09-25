#ifndef DEBUG_H
#define DEBUG_H

inline void printLog(const char *msg, ...) // wanted to modify this to print to the browser with EM_ASM_, but it already prints fine, so that's wonderful :)
{
    if (engineDebugMode) {
        char buffer[0x100];

        // make the full string
        va_list args;
        va_start(args, msg);
        vsprintf(buffer, msg, args);
        printf("%s\n", buffer);
        sprintf(buffer, "%s\n", buffer);

        char pathBuffer[0x100];

        sprintf(pathBuffer, BASE_PATH"log.txt");

        FileIO *file = fOpen(pathBuffer, "a");
        if (file) {
            fWrite(&buffer, 1, StrLength(buffer), file);
            fClose(file);
        }
    }
}

enum DevMenuMenus {
    DEVMENU_MAIN,
    DEVMENU_PLAYERSEL,
    DEVMENU_STAGELISTSEL,
    DEVMENU_STAGESEL,
    DEVMENU_MODMENU,
};

void InitSystemMenu();
void initErrorMessage();
void ProcessSystemMenu();

#endif //!DEBUG_H
