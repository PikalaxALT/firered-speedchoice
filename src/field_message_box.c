#include "global.h"
#include "gflib.h"
#include "new_menu_helpers.h"
#include "quest_log.h"
#include "script.h"
#include "text_window.h"

static EWRAM_DATA u8 sMessageBoxType = 0;

static void ExpandPlaceholdersAndPrintFieldMessage(const u8 *str);
static void PrintFieldMessage(void);

void InitFieldMessageBoxState(void)
{
    sMessageBoxType = 0;
    gTextFlags.canABSpeedUpPrint = FALSE;
    gTextFlags.useAlternateDownArrow = FALSE;
    gTextFlags.autoScroll = FALSE;
}

static void Task_RunFieldMessageBoxPrinter(u8 taskId)
{
    struct Task * task = &gTasks[taskId];
    switch (task->data[0])
    {
    case 0:
        if (gQuestLogState == QL_STATE_PLAYBACK)
        {
            gTextFlags.autoScroll = TRUE;
            TextWindow_LoadTilesStdFrame1(0, 0x200);
        }
        else if (!IsMsgSignPost())
        {
            LoadStdWindowFrameGfx();
        }
        else
        {
            LoadSignPostWindowFrameGfx();
        }
        task->data[0]++;
        break;
    case 1:
        DrawDialogueFrame(0, TRUE);
        task->data[0]++;
        break;
    case 2:
        if (RunTextPrinters_CheckPrinter0Active() != TRUE)
        {
            sMessageBoxType = 0;
            DestroyTask(taskId);
        }
        break;
    }
}

static void CreateFieldMessageBoxPrinterTask(void)
{
    CreateTask(Task_RunFieldMessageBoxPrinter, 80);
}

static void DestroyFieldMessageBoxPrinterTask(void)
{
    u8 taskId = FindTaskIdByFunc(Task_RunFieldMessageBoxPrinter);
    if (taskId != 0xFF)
        DestroyTask(taskId);
}

bool8 ShowFieldMessage(const u8 *str)
{
    if (sMessageBoxType != 0)
        return FALSE;
    ExpandPlaceholdersAndPrintFieldMessage(str);
    sMessageBoxType = 2;
    return TRUE;
}

bool8 ShowFieldAutoScrollMessage(const u8 *str)
{
    if (sMessageBoxType != 0)
        return FALSE;
    sMessageBoxType = 3;
    ExpandPlaceholdersAndPrintFieldMessage(str);
    return TRUE;
}

UNUSED
bool8 Override_ShowFieldAutoScrollMessage(const u8 *str)
{
    sMessageBoxType = 3;
    ExpandPlaceholdersAndPrintFieldMessage(str);
    return TRUE;
}

UNUSED
bool8 ShowFieldMessagePreloaded(void)
{
    if (sMessageBoxType != 0)
        return FALSE;
    sMessageBoxType = 2;
    PrintFieldMessage();
    return TRUE;
}

static void ExpandPlaceholdersAndPrintFieldMessage(const u8 *str)
{
    StringExpandPlaceholders(gStringVar4, str);
    AddTextPrinterDiffStyle(TRUE);
    CreateFieldMessageBoxPrinterTask();
}

static void PrintFieldMessage(void)
{
    AddTextPrinterDiffStyle(TRUE);
    CreateFieldMessageBoxPrinterTask();
}

void CloseFieldMessageBox(void)
{
    DestroyFieldMessageBoxPrinterTask();
    ClearDialogWindowAndFrame(0, TRUE);
    sMessageBoxType = 0;
}

u8 GetFieldMessageBoxType(void)
{
    return sMessageBoxType;
}

bool8 WaitFieldMessageBox(void)
{
    if (sMessageBoxType == 0)
        return TRUE;
    else
        return FALSE;
}

UNUSED
void UnusedDuplicate_CloseFieldMessageBox(void)
{
    DestroyFieldMessageBoxPrinterTask();
    DrawStdWindowFrame(0, TRUE);
    sMessageBoxType = 0;
}
