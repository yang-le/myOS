#ifndef __DEMO_VESA_H__
#define __DEMO_VESA_H__

#define IS_VBE2(sig) (sig[0] == 'V' && sig[1] == 'B' && sig[2] == 'E' && sig[3] == '2')
#define IS_STEREOSCOPIC_SUPPORT(cap) (cap & 0x08)

void dump_svga_mode(uint16 mode, uint8 ver);
void dump_svga_mode_list(uint32 far_pointer, uint8 ver);
void show_svga_info();

#endif
