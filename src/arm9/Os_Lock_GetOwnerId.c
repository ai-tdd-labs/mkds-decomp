typedef unsigned short u16;
typedef struct OSLockWord { char pad[4]; u16 ownerId; } OSLockWord;
u16 Os_Lock_GetOwnerId(OSLockWord *lock) { return lock->ownerId; }
