#ifndef GUARD_FIELD_MESSAGE_BOX_H
#define GUARD_FIELD_MESSAGE_BOX_H

#include "global.h"

bool8 ShowFieldMessage(const u8 *message);
bool8 sub_8098238(const u8 *message);
bool8 ShowFieldAutoScrollMessage(const u8 *message);
void CloseFieldMessageBox(void);
bool8 WaitFieldMessageBox(void);
bool8 GetFieldMessageBoxType(void);
void InitFieldMessageBoxState(void);

#endif // GUARD_FIELD_MESSAGE_BOX_H
