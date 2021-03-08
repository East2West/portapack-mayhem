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

#include "encoder.hpp"

#include "utility.hpp"

static const int8_t transition_map[] = {
	 0,	// 0000: noop
	 0,	// 0001: start
	 0,	// 0010: start
	 0,	// 0011: rate
	 0,	// 0100: end
	 0,	// 0101: noop
	 0,	// 0110: rate
	 0,	// 0111: end
	 0,	// 1000: end
	 0,	// 1001: rate
	 0,	// 1010: noop
	 0,	// 1011: end
	 0,	// 1100: rate
	 0,	// 1101: start
	 0,	// 1110: start
	 0,	// 1111: noop
};


int_fast8_t Encoder::update(
	const uint_fast8_t phase_0,
	const uint_fast8_t phase_1,
	const uint64_t update_phase,
	const uint_fast8_t changed_switches
) {
	//state <<= 1;
	//state |= phase_0;
	//state <<= 1;
	//state |= phase_1;
	
	if((changed_switches >> 5) & 0x1){		
		if(!phase_0){
			neg_pos_delta = update_phase - phase1_pos_neg_time;
			phase0_neg_pos_time = update_phase;
		}
		else {
			phase0_pos_neg_time = update_phase;
		}

/*
		if(phase_0 && (pos_neg_delta == 0)){
			return 0;
		}
		
		if(!phase_0 && !phase_1){
			neg_pos_delta = 0;
			return 0;
		}
		if(phase_0 && !phase_1){
			pos_neg_delta = 0;
			return 0;
		}
*/

		if(neg_pos_delta > pos_neg_delta){			
			state <<= 1;
			state |= 1;

			if( state == 0x0f){
				state = 0x0;
				return 1;
			}

			return 0;
		}
		else { 
			state <<= 1;
			state |= 0;	
			if( state == 0xF0){
				state = 0xFF;
				return -1;
			}		

			return 0;			
		}

	}
	else if((changed_switches >> 6) & 0x1){		
		if(!phase_1){
			pos_neg_delta = update_phase - phase0_pos_neg_time;
			phase1_neg_pos_time = update_phase;
		}
		else {
			phase1_pos_neg_time = update_phase;
		}

/*
		if(phase_1 && (neg_pos_delta == 0)){
			return 0;
		}

		if(!phase_1 && !phase_0){
			pos_neg_delta = 0;
			return 0;
		}
		if(phase_1 && !phase_0){
			neg_pos_delta = 0;
			return 0;
		}
*/

		if(neg_pos_delta > pos_neg_delta){			
			state <<= 1;
			state |= 1;

			if( (state & 0xF) == 0xf){
				return 1;
			}

			return 0;
		}
		else { 
			state <<= 1;
			state |= 0;	
			if( (state & 0xF) == 0){
				return -1;
			}		

			return 0;			
		}

	}
	else {
		return 0;
	}
	

	//return transition_map[state & 0xf];
}
