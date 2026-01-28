#ifndef FMGEN_C_H
#define FMGEN_C_H

#include <stdint.h>

/*
  fmgen C API (bridge)

  - Sample type is fixed to int32_t
  - Mix writes stereo interleaved (L,R,L,R,...) and adds into dest
  - Strings are UTF-8
  - C++ classes are not exposed (opaque handles)

  NOTE: OPN2 is not provided (no implementation in this repository).
*/

#if defined(_WIN32) || defined(__CYGWIN__)
  #if defined(FMGEN_C_EXPORTS)
    #define FMGEN_C_API __declspec(dllexport)
  #else
    #define FMGEN_C_API __declspec(dllimport)
  #endif
#else
  #if defined(__GNUC__) || defined(__clang__)
    #define FMGEN_C_API __attribute__((visibility("default")))
  #else
    #define FMGEN_C_API
  #endif
#endif

#ifdef __cplusplus
  #define FMGEN_C_BEGIN_DECLS extern "C" {
  #define FMGEN_C_END_DECLS }
#else
  #define FMGEN_C_BEGIN_DECLS
  #define FMGEN_C_END_DECLS
#endif

FMGEN_C_BEGIN_DECLS

typedef struct PSGHandle PSGHandle;
typedef struct OPNHandle OPNHandle;
typedef struct OPNAHandle OPNAHandle;
typedef struct OPNBHandle OPNBHandle;
typedef struct OPMHandle OPMHandle;

/* PSG */
FMGEN_C_API PSGHandle* PSG_Create(void);
FMGEN_C_API void PSG_Destroy(PSGHandle* psg);
FMGEN_C_API void PSG_Reset(PSGHandle* psg);
FMGEN_C_API void PSG_SetClock(PSGHandle* psg, int32_t clock, int32_t rate);
FMGEN_C_API void PSG_SetReg(PSGHandle* psg, uint32_t regnum, uint8_t data);
FMGEN_C_API uint32_t PSG_GetReg(PSGHandle* psg, uint32_t regnum);
FMGEN_C_API void PSG_SetVolume(PSGHandle* psg, int32_t vol);
FMGEN_C_API void PSG_SetChannelMask(PSGHandle* psg, int32_t mask);
FMGEN_C_API void PSG_Mix(PSGHandle* psg, int32_t* dest, int32_t nsamples);

/* OPN (YM2203) */
FMGEN_C_API OPNHandle* OPN_Create(void);
FMGEN_C_API void OPN_Destroy(OPNHandle* opn);
FMGEN_C_API int OPN_Init(OPNHandle* opn, uint32_t clock, uint32_t rate, int interpolation, const char* rhythmpath_utf8);
FMGEN_C_API int OPN_SetRate(OPNHandle* opn, uint32_t clock, uint32_t rate, int interpolation);
FMGEN_C_API void OPN_Reset(OPNHandle* opn);
FMGEN_C_API void OPN_SetReg(OPNHandle* opn, uint32_t addr, uint32_t data);
FMGEN_C_API uint32_t OPN_GetReg(OPNHandle* opn, uint32_t addr);
FMGEN_C_API uint32_t OPN_ReadStatus(OPNHandle* opn);
FMGEN_C_API void OPN_SetChannelMask(OPNHandle* opn, uint32_t mask);
FMGEN_C_API void OPN_SetVolumeFM(OPNHandle* opn, int32_t db);
FMGEN_C_API void OPN_SetVolumePSG(OPNHandle* opn, int32_t db);
FMGEN_C_API void OPN_Mix(OPNHandle* opn, int32_t* dest, int32_t nsamples);
FMGEN_C_API int OPN_Count(OPNHandle* opn, int32_t us);
FMGEN_C_API int32_t OPN_GetNextEvent(OPNHandle* opn);

/* OPNA (YM2608) */
FMGEN_C_API OPNAHandle* OPNA_Create(void);
FMGEN_C_API void OPNA_Destroy(OPNAHandle* opna);
FMGEN_C_API int OPNA_Init(OPNAHandle* opna, uint32_t clock, uint32_t rate, int interpolation, const char* rhythmpath_utf8);
FMGEN_C_API int OPNA_LoadRhythmSample(OPNAHandle* opna, const char* rhythmpath_utf8);
FMGEN_C_API int OPNA_SetRate(OPNAHandle* opna, uint32_t clock, uint32_t rate, int interpolation);
FMGEN_C_API void OPNA_Reset(OPNAHandle* opna);
FMGEN_C_API void OPNA_SetReg(OPNAHandle* opna, uint32_t addr, uint32_t data);
FMGEN_C_API uint32_t OPNA_GetReg(OPNAHandle* opna, uint32_t addr);
FMGEN_C_API uint32_t OPNA_ReadStatus(OPNAHandle* opna);
FMGEN_C_API uint32_t OPNA_ReadStatusEx(OPNAHandle* opna);
FMGEN_C_API void OPNA_SetChannelMask(OPNAHandle* opna, uint32_t mask);
FMGEN_C_API void OPNA_SetVolumeFM(OPNAHandle* opna, int32_t db);
FMGEN_C_API void OPNA_SetVolumePSG(OPNAHandle* opna, int32_t db);
FMGEN_C_API void OPNA_SetVolumeADPCM(OPNAHandle* opna, int32_t db);
FMGEN_C_API void OPNA_SetVolumeRhythmTotal(OPNAHandle* opna, int32_t db);
FMGEN_C_API void OPNA_SetVolumeRhythm(OPNAHandle* opna, int32_t index, int32_t db);
FMGEN_C_API uint8_t* OPNA_GetADPCMBuffer(OPNAHandle* opna);
FMGEN_C_API void OPNA_Mix(OPNAHandle* opna, int32_t* dest, int32_t nsamples);
FMGEN_C_API int OPNA_Count(OPNAHandle* opna, int32_t us);
FMGEN_C_API int32_t OPNA_GetNextEvent(OPNAHandle* opna);

/* OPNB (YM2610/B)

  NOTE: ADPCMA/ADPCMB buffers passed to OPNB_Init are owned by the caller.
        OPNB_Destroy does NOT free them.
*/
FMGEN_C_API OPNBHandle* OPNB_Create(void);
FMGEN_C_API void OPNB_Destroy(OPNBHandle* opnb);
FMGEN_C_API int OPNB_Init(OPNBHandle* opnb, uint32_t clock, uint32_t rate, int interpolation,
                          uint8_t* adpcma, int32_t adpcma_size,
                          uint8_t* adpcmb, int32_t adpcmb_size);
FMGEN_C_API int OPNB_SetRate(OPNBHandle* opnb, uint32_t clock, uint32_t rate, int interpolation);
FMGEN_C_API void OPNB_Reset(OPNBHandle* opnb);
FMGEN_C_API void OPNB_SetReg(OPNBHandle* opnb, uint32_t addr, uint32_t data);
FMGEN_C_API uint32_t OPNB_GetReg(OPNBHandle* opnb, uint32_t addr);
FMGEN_C_API uint32_t OPNB_ReadStatus(OPNBHandle* opnb);
FMGEN_C_API uint32_t OPNB_ReadStatusEx(OPNBHandle* opnb);
FMGEN_C_API void OPNB_SetChannelMask(OPNBHandle* opnb, uint32_t mask);
FMGEN_C_API void OPNB_SetVolumeFM(OPNBHandle* opnb, int32_t db);
FMGEN_C_API void OPNB_SetVolumePSG(OPNBHandle* opnb, int32_t db);
FMGEN_C_API void OPNB_SetVolumeADPCMATotal(OPNBHandle* opnb, int32_t db);
FMGEN_C_API void OPNB_SetVolumeADPCMA(OPNBHandle* opnb, int32_t index, int32_t db);
FMGEN_C_API void OPNB_SetVolumeADPCMB(OPNBHandle* opnb, int32_t db);
FMGEN_C_API void OPNB_Mix(OPNBHandle* opnb, int32_t* dest, int32_t nsamples);
FMGEN_C_API int OPNB_Count(OPNBHandle* opnb, int32_t us);
FMGEN_C_API int32_t OPNB_GetNextEvent(OPNBHandle* opnb);

/* OPM (YM2151) */
FMGEN_C_API OPMHandle* OPM_Create(void);
FMGEN_C_API void OPM_Destroy(OPMHandle* opm);
FMGEN_C_API int OPM_Init(OPMHandle* opm, uint32_t clock, uint32_t rate, int interpolation);
FMGEN_C_API int OPM_SetRate(OPMHandle* opm, uint32_t clock, uint32_t rate, int interpolation);
FMGEN_C_API void OPM_Reset(OPMHandle* opm);
FMGEN_C_API void OPM_SetReg(OPMHandle* opm, uint32_t addr, uint32_t data);
FMGEN_C_API uint32_t OPM_ReadStatus(OPMHandle* opm);
FMGEN_C_API void OPM_SetChannelMask(OPMHandle* opm, uint32_t mask);
FMGEN_C_API void OPM_SetVolume(OPMHandle* opm, int32_t db);
FMGEN_C_API void OPM_Mix(OPMHandle* opm, int32_t* dest, int32_t nsamples);
FMGEN_C_API int OPM_Count(OPMHandle* opm, int32_t us);
FMGEN_C_API int32_t OPM_GetNextEvent(OPMHandle* opm);

FMGEN_C_END_DECLS

#endif /* FMGEN_C_H */
