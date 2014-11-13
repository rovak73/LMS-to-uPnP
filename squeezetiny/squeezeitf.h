#ifndef __SQUEEZEITF_H
#define __SQUEEZEITF_H

#include "squeezedefs.h"
#include "util_common.h"

#define SQ_STR_LENGTH	256

typedef enum {SQ_SETURI, SQ_RESETURI, SQ_SETNEXTURI, SQ_PLAY, SQ_PAUSE, SQ_UNPAUSE, SQ_STOP, SQ_SEEK,
			  SQ_VOLUME, SQ_TIME, SQ_TRACK_CHANGE, SQ_ONOFF} sq_action_t;
typedef enum {SQ_LMSUPNP = 0, SQ_DIRECT = 1, SQ_STREAM = 2, SQ_FULL = 3} sq_mode_t;
typedef	sq_action_t sq_event_t;

#define MAX_SUPPORTED_SAMPLERATES 11
#define TEST_RATES = { 96000, 48000, 44100, 32000, 24000, 22500, 16000, 12000, 11025, 8000, 0 }


			   SQ_RATE_32000 = 32000, SQ_RATE_24000 = 24000, SQ_RATE_22500 = 22500,
			   SQ_RATE_16000 = 16000, SQ_RATE_12000 = 12000, SQ_RATE_11025 = 11025,
			   SQ_RATE_8000 = 8000, SQ_RATE_DEFAULT = 0} sq_rate_e;
typedef	int	sq_dev_handle_t;
typedef unsigned sq_rate_t;

typedef	struct sq_dev_param_s {
	unsigned 	stream_buf_size;
	unsigned 	output_buf_size;
	sq_mode_t	mode;
	sq_rate_t	rate[MAX_SUPPORTED_SAMPLERATES];
	bool		can_pause;
	int			max_get_bytes;		 // max size allowed in a single read
	int			max_read_wait;
	char		codecs[SQ_STR_LENGTH];
	sq_rate_e	sample_rate;
	char		buffer_dir[SQ_STR_LENGTH];
} sq_dev_param_t;

typedef struct sq_log_level_s {		// must be one of lERROR, lINFO, lDEBUG or lSDEBUG
	log_level	general;
	log_level	slimproto;
	log_level	output;
	log_level	stream;
	log_level	decode;
	log_level	main;
	log_level	upnp;
	log_level	sq2mr;
	log_level	web;
} sq_log_level_t;

typedef struct
{
	char	urn[SQ_STR_LENGTH];
	char	ip[16];
	unsigned port;
	u8_t	channels;
	u8_t	sample_size;
	u16_t	sample_rate;
	char	format[5];
	char	content_type[SQ_STR_LENGTH];
} sq_seturi_t;

extern unsigned gl_slimproto_stream_port;

typedef bool (*sq_callback_t)(sq_dev_handle_t handle, void *caller_id, sq_action_t action, int cookie, void *param);

char*				sq_parse_args(int argc, char**argv);
// all params can be NULL
void				sq_init(char *server, u8_t mac[6], sq_log_level_t *);
void				sq_stop(void);

// only name cannot be NULL
bool			 	sq_run_device(sq_dev_handle_t handle, char *name, u8_t *mac, sq_dev_param_t *param);
bool				sq_delete_device(sq_dev_handle_t);
sq_dev_handle_t		sq_reserve_device(void *caller_id, sq_callback_t callback);

bool				sq_call(sq_dev_handle_t handle, sq_action_t action, void *param);
void				sq_notify(sq_dev_handle_t handle, void *caller_id, sq_event_t event, int cookie, void *param);
u32_t 				sq_get_time(sq_dev_handle_t handle);
bool 				sq_set_time(sq_dev_handle_t handle, u32_t time);
void*				sq_urn2MR(const char *urn);
char*				sq_content_type(const char *urn);	// string must be released by caller
void*				sq_open(const char *urn);
bool				sq_close(void *desc);
int					sq_read(void *desc, void *dst, unsigned bytes);
int					sq_seek(void *desc, unsigned bytes, unsigned from);
void				sq_reset(sq_dev_handle_t);

void stream_loglevel(log_level level);
void slimproto_loglevel(log_level level);
void output_loglevel(log_level level);
void output_mr_loglevel(log_level level);
void decode_loglevel(log_level level);
void main_loglevel(log_level level);
#endif
