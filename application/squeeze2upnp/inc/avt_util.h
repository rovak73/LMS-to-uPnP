/*
 *  Squeeze2upnp - LMS to uPNP gateway
 *
 *  Squeezelite : (c) Adrian Smith 2012-2014, triode1@btinternet.com
 *  Additions & gateway : (c) Philippe 2014, philippe_44@outlook.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __AVT_UTIL_H
#define __AVT_UTIL_H

#include "util_common.h"
#include "util.h"

struct sq_metadata_s;
struct sMRConfig;
struct sMR;

typedef struct sAction {
	struct sMR *Device;
	void   *ActionNode;
	union {
		u8_t Volume;
	} Param;
} tAction;

void 	AVTInit(log_level level);
bool 	AVTSetURI(struct sMR *Device);
bool 	AVTSetNextURI(struct sMR *Device);
int 	AVTCallAction(struct sMR *Device, char *Var, void *Cookie);
bool 	AVTPlay(struct sMR *Device);
bool 	AVTSetPlayMode(struct sMR *Device);
bool 	AVTSeek(struct sMR *Device, unsigned Interval);
bool 	AVTBasic(struct sMR *Device, char *Action);
bool 	AVTStop(struct sMR *Device);
void	AVTActionFlush(tQueue *Queue);
int 	CtrlSetVolume(struct sMR *Device, u8_t Volume, void *Cookie);
int 	CtrlSetMute(struct sMR *Device, bool Mute, void *Cookie);
int 	GetProtocolInfo(struct sMR *Device, void *Cookie);

#endif

