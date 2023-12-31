/*---------------------------------------------------------------------------*\

  FILE........: dump.h
  AUTHOR......: David Rowe
  DATE CREATED: 25/8/09

  Routines to dump data to text files for Octave analysis.

\*---------------------------------------------------------------------------*/

/*
  All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 2.1, as
  published by the Free Software Foundation.  This program is
  distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __DUMP__
#define __DUMP__

#include "codec2_fft.h"
#include "codec2_internal.h"
#include "comp.h"
#include "defines.h"

void dump_on(char filename_prefix[]);
void dump_off();

void dump_Sn(int m_pitch, float Sn[]);
void dump_Sw(COMP Sw[]);
void dump_Sw_(COMP Sw_[]);
void dump_Ew(COMP Ew[]);
void dump_softdec(float *softdec, int n);

/* amplitude modelling */

void dump_model(MODEL *m);
void dump_quantised_model(MODEL *m);
void dump_Pwn(COMP Pw[]);
void dump_Pw(float Pw[]);
void dump_Rw(float Rw[]);
void dump_lsp(float lsp[]);
void dump_weights(float w[], int ndim);
void dump_lsp_(float lsp_[]);
void dump_mel(float mel[], int order);
void dump_mel_indexes(int mel_indexes[], int order);
void dump_ak(float ak[], int order);
void dump_ak_(float ak[], int order);
void dump_E(float E);
void dump_lpc_snr(float snr);

/* phase modelling */

void dump_snr(float snr);
void dump_phase(float phase[], int L);
void dump_phase_(float phase[], int L);
void dump_hephase(int ind[], int dim);

/* NLP states */

void dump_sq(int m_pitch, float sq[]);
void dump_dec(COMP Fw[]);
void dump_Fw(COMP Fw[]);
void dump_e(float e_hz[]);
#if 0
void dump_Rk(float Rk[]);
#endif

/* post filter */

void dump_bg(float e, float bg_est, float percent_uv);
void dump_Pwb(float Pwb[]);

#endif
