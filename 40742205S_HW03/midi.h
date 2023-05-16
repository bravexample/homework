// A header for MIDI specification

#ifndef MIDI_H
#define MIDI_H

// Instrument names
#define Acoustic_Grand_Piano 1
#define Bright_Acoustic_Piano 2
#define Electric_Grand_Piano 3
#define Honky_tonk_Piano 4
#define Rhodes_Piano 5
#define Chorused_Piano 6
#define Harpsichord 7
#define Clavinet 8
#define Celesta 9
#define Glockenspiel 10
#define Music_Box 11
#define Vibraphone 12
#define Marimba 13
#define Xylophone 14
#define Tubular_Bells 15
#define Dulcimer 16
#define Drawbar_Organ 17
#define Percussive_Organ 18
#define Rock_Organ 19
#define Church_Organ 20
#define Reed_Organ 21
#define Accordion 22
#define Harmonica 23
#define Tango_Accordion 24
#define Acoustic_Guitar_nylon 25
#define Acoustic_Guitar_steel 26
#define Electric_Guitar_jazz 27
#define Electric_Guitar_clean 28
#define Electric_Guitar_muted 29
#define Overdriven_Guitar 30
#define Distortion_Guitar 31
#define Guitar_harmonics 32
#define Acoustic_Bass 33
#define Electric_Bass_fingered 34
#define Electric_Bass_picked 35
#define Fretless_Bass 36
#define Slap_Bass_1 37
#define Slap Bass_2 38
#define Synth_Bass_1 39
#define Synth_Bass_2 40
#define Violin 41
#define Viola 42
#define Cello 43
#define Contrabass 44
#define Tremolo_Strings 45
#define Pizzicato_Strings 46
#define Orchestral_Harp 47
#define Timpani 48
#define String_Ensemble_1 49
#define String_Ensemble_2 50
#define SynthStrings_1 51
#define SynthStrings_2 52
#define Choir_Aahs 53
#define Voice_Oohs 54
#define Synth_Voice 55
#define Orchestra_Hit 56
#define Trumpet 57
#define Trombone 58
#define Tuba 59
#define Muted_Trumpet 60
#define French_Horn 61
#define Brass_Section 62
#define SynthBrass_1 63
#define SynthBrass_2 64
#define Soprano_Sax 65
#define Alto_Sax 66
#define Tenor_Sax 67
#define Baritone_Sax 68
#define Oboe 69
#define English_Horn 70
#define Bassoon 71
#define Clarinet 72
#define Piccolo 73
#define Flute 74
#define Recorder 75
#define Pan_Flute 76
#define Blown_Bottle 77
#define Shakuhachi 78
#define Whistle 79
#define Ocarina 80
#define Lead_1_square 81
#define Lead_2_sawtooth 82
#define Lead_3_calliope 83
#define Lead_4_chiff 84
#define Lead_5_charang 85
#define Lead_6_voice 86
#define Lead_7_fifths 87
#define Lead_8_bass_and_lead 88
#define Pad_1_new_age 89
#define Pad_2_warm 90
#define Pad_3_polysynth 91
#define Pad_4_choir 92
#define Pad_5_bowed 93
#define Pad_6_metallic 94
#define Pad_7_halo 95
#define Pad_8_sweep 96
#define FX_1_rain 97
#define FX_2_soundtrack 98
#define FX_3_crystal 99
#define FX_4_atmosphere 100
#define FX_5_brightness 101
#define FX_6_goblins 102
#define FX_7_echoes 103
#define FX_8_sci_fi 104
#define Sitar 105
#define Banjo 106
#define Shamisen 107
#define Koto 108
#define Kalimba 109
#define Bagpipe 110
#define Fiddle 111
#define Shanai 112
#define Tinkle_Bell 113
#define Agogo 114
#define Steel_Drums 115
#define Woodblock 116
#define Taiko_Drum 117
#define Melodic_Tom 118
#define Synth_Drum 119
#define Reverse_Cymbal 120
#define Guitar_Fret_Noise 121
#define Breath_Noise 122
#define Seashore 123
#define Bird_Tweet 124
#define Telephone_Ring 125
#define Helicopter 126
#define Applause 127
#define Gunshot 128

// Disable auto align
#pragma pack(1)

// Header chunk
typedef struct {
    char chunk_id[4];
    int32_t chunk_size;
    int16_t format_type;
    int16_t track_count;
    int16_t time_division;
} sMIDIHeader;

#endif