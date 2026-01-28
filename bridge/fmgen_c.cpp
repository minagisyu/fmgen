#include "bridge/fmgen_c.h"

#include <new>

#include "fmgen/opna.h"
#include "fmgen/opm.h"
#include "fmgen/psg.h"

struct PSGHandle { PSG* p; };
struct OPNHandle { FM::OPN* p; };
struct OPNAHandle { FM::OPNA* p; };
struct OPNBHandle { FM::OPNB* p; };
struct OPMHandle { FM::OPM* p; };

static PSG* as_psg(PSGHandle* h) { return h ? h->p : 0; }
static FM::OPN* as_opn(OPNHandle* h) { return h ? h->p : 0; }
static FM::OPNA* as_opna(OPNAHandle* h) { return h ? h->p : 0; }
static FM::OPNB* as_opnb(OPNBHandle* h) { return h ? h->p : 0; }
static FM::OPM* as_opm(OPMHandle* h) { return h ? h->p : 0; }

PSGHandle* PSG_Create(void)
{
    PSGHandle* h = new (std::nothrow) PSGHandle;
    if (!h) return 0;
    h->p = new (std::nothrow) PSG;
    if (!h->p) { delete h; return 0; }
    return h;
}

void PSG_Destroy(PSGHandle* psg)
{
    if (!psg) return;
    delete psg->p;
    delete psg;
}

void PSG_Reset(PSGHandle* psg)
{
    PSG* p = as_psg(psg);
    if (!p) return;
    p->Reset();
}

void PSG_SetClock(PSGHandle* psg, int32_t clock, int32_t rate)
{
    PSG* p = as_psg(psg);
    if (!p) return;
    p->SetClock((int)clock, (int)rate);
}

void PSG_SetReg(PSGHandle* psg, uint32_t regnum, uint8_t data)
{
    PSG* p = as_psg(psg);
    if (!p) return;
    p->SetReg((uint)regnum, data);
}

uint32_t PSG_GetReg(PSGHandle* psg, uint32_t regnum)
{
    PSG* p = as_psg(psg);
    if (!p) return 0;
    return (uint32_t)p->GetReg((uint)regnum);
}

void PSG_SetVolume(PSGHandle* psg, int32_t vol)
{
    PSG* p = as_psg(psg);
    if (!p) return;
    p->SetVolume((int)vol);
}

void PSG_SetChannelMask(PSGHandle* psg, int32_t mask)
{
    PSG* p = as_psg(psg);
    if (!p) return;
    p->SetChannelMask((int)mask);
}

void PSG_Mix(PSGHandle* psg, int32_t* dest, int32_t nsamples)
{
    PSG* p = as_psg(psg);
    if (!p || !dest || nsamples <= 0) return;
    p->Mix((PSG::Sample*)dest, (int)nsamples);
}

OPNHandle* OPN_Create(void)
{
    OPNHandle* h = new (std::nothrow) OPNHandle;
    if (!h) return 0;
    h->p = new (std::nothrow) FM::OPN;
    if (!h->p) { delete h; return 0; }
    return h;
}

void OPN_Destroy(OPNHandle* opn)
{
    if (!opn) return;
    delete opn->p;
    delete opn;
}

int OPN_Init(OPNHandle* opn, uint32_t clock, uint32_t rate, int interpolation, const char*)
{
    FM::OPN* p = as_opn(opn);
    if (!p) return 0;
    return p->Init((uint)clock, (uint)rate, interpolation != 0, 0) ? 1 : 0;
}

int OPN_SetRate(OPNHandle* opn, uint32_t clock, uint32_t rate, int interpolation)
{
    FM::OPN* p = as_opn(opn);
    if (!p) return 0;
    return p->SetRate((uint)clock, (uint)rate, interpolation != 0) ? 1 : 0;
}

void OPN_Reset(OPNHandle* opn)
{
    FM::OPN* p = as_opn(opn);
    if (!p) return;
    p->Reset();
}

void OPN_SetReg(OPNHandle* opn, uint32_t addr, uint32_t data)
{
    FM::OPN* p = as_opn(opn);
    if (!p) return;
    p->SetReg((uint)addr, (uint)data);
}

uint32_t OPN_GetReg(OPNHandle* opn, uint32_t addr)
{
    FM::OPN* p = as_opn(opn);
    if (!p) return 0;
    return (uint32_t)p->GetReg((uint)addr);
}

uint32_t OPN_ReadStatus(OPNHandle* opn)
{
    FM::OPN* p = as_opn(opn);
    if (!p) return 0;
    return (uint32_t)p->ReadStatus();
}

void OPN_SetChannelMask(OPNHandle* opn, uint32_t mask)
{
    FM::OPN* p = as_opn(opn);
    if (!p) return;
    p->SetChannelMask((uint)mask);
}

void OPN_SetVolumeFM(OPNHandle* opn, int32_t db)
{
    FM::OPN* p = as_opn(opn);
    if (!p) return;
    p->SetVolumeFM((int)db);
}

void OPN_SetVolumePSG(OPNHandle* opn, int32_t db)
{
    FM::OPN* p = as_opn(opn);
    if (!p) return;
    p->SetVolumePSG((int)db);
}

void OPN_Mix(OPNHandle* opn, int32_t* dest, int32_t nsamples)
{
    FM::OPN* p = as_opn(opn);
    if (!p || !dest || nsamples <= 0) return;
    p->Mix((FM::Sample*)dest, (int)nsamples);
}

int OPN_Count(OPNHandle* opn, int32_t us)
{
    FM::OPN* p = as_opn(opn);
    if (!p) return 0;
    return p->Count((int32)us) ? 1 : 0;
}

int32_t OPN_GetNextEvent(OPNHandle* opn)
{
    FM::OPN* p = as_opn(opn);
    if (!p) return 0;
    return (int32_t)p->GetNextEvent();
}

OPNAHandle* OPNA_Create(void)
{
    OPNAHandle* h = new (std::nothrow) OPNAHandle;
    if (!h) return 0;
    h->p = new (std::nothrow) FM::OPNA;
    if (!h->p) { delete h; return 0; }
    return h;
}

void OPNA_Destroy(OPNAHandle* opna)
{
    if (!opna) return;
    delete opna->p;
    delete opna;
}

int OPNA_Init(OPNAHandle* opna, uint32_t clock, uint32_t rate, int interpolation, const char* rhythmpath_utf8)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return 0;
    return p->Init((uint)clock, (uint)rate, interpolation != 0, rhythmpath_utf8) ? 1 : 0;
}

int OPNA_LoadRhythmSample(OPNAHandle* opna, const char* rhythmpath_utf8)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return 0;
    return p->LoadRhythmSample(rhythmpath_utf8) ? 1 : 0;
}

int OPNA_SetRate(OPNAHandle* opna, uint32_t clock, uint32_t rate, int interpolation)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return 0;
    return p->SetRate((uint)clock, (uint)rate, interpolation != 0) ? 1 : 0;
}

void OPNA_Reset(OPNAHandle* opna)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return;
    p->Reset();
}

void OPNA_SetReg(OPNAHandle* opna, uint32_t addr, uint32_t data)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return;
    p->SetReg((uint)addr, (uint)data);
}

uint32_t OPNA_GetReg(OPNAHandle* opna, uint32_t addr)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return 0;
    return (uint32_t)p->GetReg((uint)addr);
}

uint32_t OPNA_ReadStatus(OPNAHandle* opna)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return 0;
    return (uint32_t)p->ReadStatus();
}

uint32_t OPNA_ReadStatusEx(OPNAHandle* opna)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return 0;
    return (uint32_t)p->ReadStatusEx();
}

void OPNA_SetChannelMask(OPNAHandle* opna, uint32_t mask)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return;
    p->SetChannelMask((uint)mask);
}

void OPNA_SetVolumeFM(OPNAHandle* opna, int32_t db)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return;
    p->SetVolumeFM((int)db);
}

void OPNA_SetVolumePSG(OPNAHandle* opna, int32_t db)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return;
    p->SetVolumePSG((int)db);
}

void OPNA_SetVolumeADPCM(OPNAHandle* opna, int32_t db)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return;
    p->SetVolumeADPCM((int)db);
}

void OPNA_SetVolumeRhythmTotal(OPNAHandle* opna, int32_t db)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return;
    p->SetVolumeRhythmTotal((int)db);
}

void OPNA_SetVolumeRhythm(OPNAHandle* opna, int32_t index, int32_t db)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return;
    p->SetVolumeRhythm((int)index, (int)db);
}

uint8_t* OPNA_GetADPCMBuffer(OPNAHandle* opna)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return 0;
    return p->GetADPCMBuffer();
}

void OPNA_Mix(OPNAHandle* opna, int32_t* dest, int32_t nsamples)
{
    FM::OPNA* p = as_opna(opna);
    if (!p || !dest || nsamples <= 0) return;
    p->Mix((FM::Sample*)dest, (int)nsamples);
}

int OPNA_Count(OPNAHandle* opna, int32_t us)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return 0;
    return p->Count((int32)us) ? 1 : 0;
}

int32_t OPNA_GetNextEvent(OPNAHandle* opna)
{
    FM::OPNA* p = as_opna(opna);
    if (!p) return 0;
    return (int32_t)p->GetNextEvent();
}

OPNBHandle* OPNB_Create(void)
{
    OPNBHandle* h = new (std::nothrow) OPNBHandle;
    if (!h) return 0;
    h->p = new (std::nothrow) FM::OPNB;
    if (!h->p) { delete h; return 0; }
    return h;
}

void OPNB_Destroy(OPNBHandle* opnb)
{
    if (!opnb) return;
    delete opnb->p;
    delete opnb;
}

int OPNB_Init(OPNBHandle* opnb, uint32_t clock, uint32_t rate, int interpolation,
             uint8_t* adpcma, int32_t adpcma_size,
             uint8_t* adpcmb, int32_t adpcmb_size)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return 0;
    return p->Init((uint)clock, (uint)rate, interpolation != 0,
                   adpcma, (int)adpcma_size,
                   adpcmb, (int)adpcmb_size) ? 1 : 0;
}

int OPNB_SetRate(OPNBHandle* opnb, uint32_t clock, uint32_t rate, int interpolation)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return 0;
    return p->SetRate((uint)clock, (uint)rate, interpolation != 0) ? 1 : 0;
}

void OPNB_Reset(OPNBHandle* opnb)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return;
    p->Reset();
}

void OPNB_SetReg(OPNBHandle* opnb, uint32_t addr, uint32_t data)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return;
    p->SetReg((uint)addr, (uint)data);
}

uint32_t OPNB_GetReg(OPNBHandle* opnb, uint32_t addr)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return 0;
    return (uint32_t)p->GetReg((uint)addr);
}

uint32_t OPNB_ReadStatus(OPNBHandle* opnb)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return 0;
    return (uint32_t)p->ReadStatus();
}

uint32_t OPNB_ReadStatusEx(OPNBHandle* opnb)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return 0;
    return (uint32_t)p->ReadStatusEx();
}

void OPNB_SetChannelMask(OPNBHandle* opnb, uint32_t mask)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return;
    p->SetChannelMask((uint)mask);
}

void OPNB_SetVolumeFM(OPNBHandle* opnb, int32_t db)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return;
    p->SetVolumeFM((int)db);
}

void OPNB_SetVolumePSG(OPNBHandle* opnb, int32_t db)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return;
    p->SetVolumePSG((int)db);
}

void OPNB_SetVolumeADPCMATotal(OPNBHandle* opnb, int32_t db)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return;
    p->SetVolumeADPCMATotal((int)db);
}

void OPNB_SetVolumeADPCMA(OPNBHandle* opnb, int32_t index, int32_t db)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return;
    p->SetVolumeADPCMA((int)index, (int)db);
}

void OPNB_SetVolumeADPCMB(OPNBHandle* opnb, int32_t db)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return;
    p->SetVolumeADPCMB((int)db);
}

void OPNB_Mix(OPNBHandle* opnb, int32_t* dest, int32_t nsamples)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p || !dest || nsamples <= 0) return;
    p->Mix((FM::Sample*)dest, (int)nsamples);
}

int OPNB_Count(OPNBHandle* opnb, int32_t us)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return 0;
    return p->Count((int32)us) ? 1 : 0;
}

int32_t OPNB_GetNextEvent(OPNBHandle* opnb)
{
    FM::OPNB* p = as_opnb(opnb);
    if (!p) return 0;
    return (int32_t)p->GetNextEvent();
}

OPMHandle* OPM_Create(void)
{
    OPMHandle* h = new (std::nothrow) OPMHandle;
    if (!h) return 0;
    h->p = new (std::nothrow) FM::OPM;
    if (!h->p) { delete h; return 0; }
    return h;
}

void OPM_Destroy(OPMHandle* opm)
{
    if (!opm) return;
    delete opm->p;
    delete opm;
}

int OPM_Init(OPMHandle* opm, uint32_t clock, uint32_t rate, int interpolation)
{
    FM::OPM* p = as_opm(opm);
    if (!p) return 0;
    return p->Init((uint)clock, (uint)rate, interpolation != 0) ? 1 : 0;
}

int OPM_SetRate(OPMHandle* opm, uint32_t clock, uint32_t rate, int interpolation)
{
    FM::OPM* p = as_opm(opm);
    if (!p) return 0;
    return p->SetRate((uint)clock, (uint)rate, interpolation != 0) ? 1 : 0;
}

void OPM_Reset(OPMHandle* opm)
{
    FM::OPM* p = as_opm(opm);
    if (!p) return;
    p->Reset();
}

void OPM_SetReg(OPMHandle* opm, uint32_t addr, uint32_t data)
{
    FM::OPM* p = as_opm(opm);
    if (!p) return;
    p->SetReg((uint)addr, (uint)data);
}

uint32_t OPM_ReadStatus(OPMHandle* opm)
{
    FM::OPM* p = as_opm(opm);
    if (!p) return 0;
    return (uint32_t)p->ReadStatus();
}

void OPM_SetChannelMask(OPMHandle* opm, uint32_t mask)
{
    FM::OPM* p = as_opm(opm);
    if (!p) return;
    p->SetChannelMask((uint)mask);
}

void OPM_SetVolume(OPMHandle* opm, int32_t db)
{
    FM::OPM* p = as_opm(opm);
    if (!p) return;
    p->SetVolume((int)db);
}

void OPM_Mix(OPMHandle* opm, int32_t* dest, int32_t nsamples)
{
    FM::OPM* p = as_opm(opm);
    if (!p || !dest || nsamples <= 0) return;
    p->Mix((FM::Sample*)dest, (int)nsamples);
}

int OPM_Count(OPMHandle* opm, int32_t us)
{
    FM::OPM* p = as_opm(opm);
    if (!p) return 0;
    return p->Count((int32)us) ? 1 : 0;
}

int32_t OPM_GetNextEvent(OPMHandle* opm)
{
    FM::OPM* p = as_opm(opm);
    if (!p) return 0;
    return (int32_t)p->GetNextEvent();
}
