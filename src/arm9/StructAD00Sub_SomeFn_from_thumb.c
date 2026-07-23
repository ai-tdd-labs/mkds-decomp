// PURPOSE: Starts an animation helper with the current racer animation length.
// The argument points to a substructure whose helper state begins at offset 0x98.
// The current racer manager probably supplies the animation at offset 0x10c.

extern unsigned char *data_0217ad00;
extern unsigned int Animation_GetCurrentLength(void *animation);
extern void Animation_InitializeImpl(void *state, unsigned int length);

void StructAD00Sub_SomeFn_from_thumb(void *sub)
{
    Animation_InitializeImpl((unsigned char *)sub + 0x98,
        Animation_GetCurrentLength(data_0217ad00 + 0x10c));
}
