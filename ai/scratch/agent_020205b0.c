// PURPOSE: Calculates the CRC for profile information.
// It passes the profile data and two parameters to the shared CRC routine.
// The helper writes the probably raw CRC into a local output word.
// This wrapper returns the inverted value used by the profile format.

extern void ComputeProfileInfoCrcImpl(void *profile, int *result, int arg2, int arg3);

int ComputeProfileInfoCrc(void *profile, int arg2, int arg3) {
    int volatile result = -1;

    ComputeProfileInfoCrcImpl(profile, (int *)&result, arg2, arg3);
    return ~result;
}
