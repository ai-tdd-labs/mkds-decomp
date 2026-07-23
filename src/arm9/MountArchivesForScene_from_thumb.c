// PURPOSE: Mounts the archives needed for a scene.
// The scene argument selects which groups of archives are loaded.
// Download-play mode skips some archives, and scene 6 also checks current progress.

typedef struct CupProgressState {
    unsigned char unknown_00[0x74];
    int field_74;
} CupProgressState;

extern CupProgressState *data_0217b488;

extern void Arc_MountArchive_from_thumb(int idx, int scene);

void MountArchivesForScene_from_thumb(int scene)
{
    if (*(volatile unsigned short *)0x027ffc40 != 2 ||
        scene != 6 || data_0217b488->field_74 != 0) {
        Arc_MountArchive_from_thumb(1, scene);
    }

    switch (scene) {
    case 1:
    case 12:
        Arc_MountArchive_from_thumb(5, scene);
        Arc_MountArchive_from_thumb(14, scene);
        Arc_MountArchive_from_thumb(16, scene);
        break;

    case 10:
        Arc_MountArchive_from_thumb(0, scene);
        Arc_MountArchive_from_thumb(5, scene);
        Arc_MountArchive_from_thumb(16, scene);
        Arc_MountArchive_from_thumb(18, scene);
        break;

    case 2:
        Arc_MountArchive_from_thumb(18, scene);
        Arc_MountArchive_from_thumb(6, scene);
        Arc_MountArchive_from_thumb(8, scene);
        break;

    case 3:
        Arc_MountArchive_from_thumb(0, scene);
        Arc_MountArchive_from_thumb(5, scene);
        Arc_MountArchive_from_thumb(16, scene);
        break;

    case 5:
        Arc_MountArchive_from_thumb(5, scene);
        Arc_MountArchive_from_thumb(14, scene);
        Arc_MountArchive_from_thumb(16, scene);
        break;

    case 0:
    case 7:
    case 8:
    case 9:
    case 11:
    case 13:
    case 14:
    case 15:
        Arc_MountArchive_from_thumb(5, scene);
        Arc_MountArchive_from_thumb(16, scene);
        break;

    case 4:
        if (*(volatile unsigned short *)0x027ffc40 != 2) {
            Arc_MountArchive_from_thumb(5, scene);
            Arc_MountArchive_from_thumb(16, scene);
        }
        break;

    case 6:
        if (*(volatile unsigned short *)0x027ffc40 != 2) {
            Arc_MountArchive_from_thumb(5, scene);
            Arc_MountArchive_from_thumb(16, scene);
        }
        break;
    }
}
