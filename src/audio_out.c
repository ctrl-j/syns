#include <stdio.h>
#include <stdlib.h>

#include "sound.h"

// For functions related to playback and writing/converting audio files

void WRITE_NSF_HEADER(FILE* AUDIO_OUT, NSF_HEADER* HEADER) {
    // 5 byte file FILE_FORMAT
    fwrite(HEADER->FILE_FORMAT, 1, 5, AUDIO_OUT);

    // 1 byte NSF version #
    fputc(HEADER->VERSION, AUDIO_OUT);

    // 1 byte total song count
    fputc(HEADER->TOTAL_SONGS, AUDIO_OUT);

    // 1 byte starting song #
    fputc(HEADER->START_SONG, AUDIO_OUT);

    // 2 byte word (lo, hi) LOAD address of data
    fwrite(HEADER->LOAD_ADDR, 2, 1, AUDIO_OUT);
    // 2 byte word (lo, hi) INIT address of data
    fwrite(HEADER->INIT_ADDR, 2, 1, AUDIO_OUT);
    // 2 byte word (lo, hi) PLAY address of data
    fwrite(HEADER->PLAY_ADDR, 2, 1, AUDIO_OUT);

    // 32 char TITLE
    fwrite(HEADER->TITLE, 1, 32, AUDIO_OUT);
    // 32 char ARTIST
    fwrite(HEADER->ARTIST, 1, 32, AUDIO_OUT);
    // 32 char COPYRIGHT
    fwrite(HEADER->COPYRIGHT, 1, 32, AUDIO_OUT);

    // 2 byte word (lo, hi) NTSC play speed
    // In 1/1000000th sec ticks
    fwrite(HEADER->PLAY_SPEED_NTSC, AUDIO_OUT);

    // 1 byte of BANKSWITCH_INIT flags
    fputc(HEADER->BANKSWITCH_INIT, AUDIO_OUT);

    // 2 byte word (lo, hi) PAL play speed
    // In 1/1000000th sec ticks
    fwrite(HEADER->PLAY_SPEED_PAL, AUDIO_OUT);

    // 1 byte of PAL/NTSC flags
    fputc(HEADER->PAL_NTSC_FLAGS, AUDIO_OUT);
    // 1 byte of sound chip flags
    fputc(HEADER->SOUND_CHIP_FLAGS, AUDIO_OUT);

    // 1 byte reserved for NSF2
    fputc(HEADER->NSF2, AUDIO_OUT);

    // 3 bytes (24 bit number) length of contained program data
    fwrite(HEADER->LENGTH, 1, 3, AUDIO_OUT);

}

void WRITE_NSF_DATA() {

}

int WRITE_NSF_FILE(char* AUDIO_OUT, NSF_HEADER* HEADER, char* DATA) {
    FILE* AUDIO_OUT = fopen(FILENAME, "wb");
    if (FILE == NULL) {
        return 1;
    }

    WRITE_NSF_HEADER(AUDIO_OUT, HEADER);
    WRITE_NSF_DATA(AUDIO_OUT, DATA);

}