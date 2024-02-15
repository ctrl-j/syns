#ifndef __SOUND_H__
#define __SOUND_H__


typedef unsigned char BYTE;
typedef unsigned short int WORD;

// Information regarding the NSF file format and header 
// construction was acquired from https://www.nesdev.org/wiki/NSF

// NSF file header structure
// Fields are in the order they are written in the header
typedef struct _NSF_HEADER {
    // 'N', 'E', 'S', 'M', $1A
    BYTE FILE_FORMAT[5];
    
    // $01 ($02 to denote NSF2 file)
    BYTE VERSION;

    // 1 = 1 song, 2 = 2 songs, ...
    BYTE TOTAL_SONGS;
    // 1 = first song, 2 = second song, ...
    BYTE START_SONG;

    // (lo, hi) LOAD address of DATA ($8000-FFFF)
    WORD LOAD_ADDR;
    // (lo, hi) INIT address of DATA ($8000-FFFF)
    WORD INIT_ADDR;
    // (lo, hi) PLAY address of DATA ($8000-FFFF)
    WORD PLAY_ADDR;

    // 32 char name of the song; NULL terminated
    BYTE TITLE[32];
    // 32 char artist, if known; NULL terminated
    BYTE ARTIST[32];
    // 32 char copyright holder; NULL terminated
    BYTE COPYRIGHT[32];

    // Common audio playback rates:
    // 60.002Hz:    $411A (16666) - original NSF spec, close to APU timer IRQ rate
    // 60.099Hz:    $40FF (16639) - actual NTSC NES framerate
    // 50.007Hz:    $4E1D (19997) - suggested PAL NES framerate
    
    // (lo, hi) NTSC Play speed, in 1/1000000th sec ticks
    WORD PLAY_SPEED_NTSC;

    // If any of these bytes are nonzero, bankswitching will be used for audio data
    // APU will take logical AND of LOAD_ADDR with $0FFF
    BYTE BANKSWITCH_INIT[8];

    // (lo, hi) PAL Play speed, in 1/1000000th sec ticks
    WORD PLAY_SPEED_PAL;
    BYTE PAL_NTSC_FLAGS;
    BYTE SOUND_CHIP_FLAGS;
    BYTE NSF2;
    BYTE LENGTH[3];
} NSF_HEADER;

// Writes header to *AUDIO_FILE, returns pointer to end of
// file header to continue writing data
void WRITE_NSF_HEADER(FILE* AUDIO_OUT, NSF_HEADER* HEADER);

void WRITE_NSF_DATA(FILE* AUDIO_OUT, char* DATA);

// Calls above two functions to write complete NSF file
// DATA can be raw (.ac or .nsf) or converted from file (.mp3 or .wav)
// Caller function responsible for allocating/deallocating memory for and initializing HEADER
int WRITE_NSF_FILE(char* AUDIO_OUT, NSF_HEADER* HEADER, char* DATA);

#endif