/*
 * Copyright (C) 2014 Jared Boone, ShareBrained Technology, Inc.
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <cstdint>

class Encoder {
public:
	int_fast8_t update(
		const uint_fast8_t phase_0,
		const uint_fast8_t phase_1,
		const uint64_t update_phase,
		const uint_fast8_t changed_switches
	);

private:
	uint_fast8_t state { 0 };

	uint32_t neg_pos_delta { 0 };
	uint32_t pos_neg_delta { 0 };
	uint32_t phase0_neg_pos_time { 0 };
	uint32_t phase1_neg_pos_time { 0 };
	uint32_t phase0_pos_neg_time { 0 };
	uint32_t phase1_pos_neg_time { 0 };
};

#endif/*__ENCODER_H__*/
