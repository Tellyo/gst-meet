#ifndef gstmeet_h
#define gstmeet_h

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <glib/glib.h>
#include <gst/gst.h>

typedef struct JitsiConnection JitsiConnection;
typedef struct JitsiConference JitsiConference;

typedef struct Context Context;

typedef struct ConferenceConfig {
  const char *muc;
  const char *focus;
  const char *nick;
  const char *region;
  const char *video_codec;
} ConferenceConfig;

typedef struct Participant {
  const char *jid;
  const char *muc_jid;
  const char *nick;
} Participant;

typedef enum {VIDEO, AUDIO} MediaType;

struct Context *gstmeet_init(void);

void gstmeet_init_tracing(const char *level);

void gstmeet_deinit(struct Context *context);

JitsiConnection *gstmeet_connection_new(struct Context *context,
                                        const char *websocket_url,
                                        const char *xmpp_domain);

void gstmeet_connection_free(JitsiConnection *connection);

bool gstmeet_connection_connect(struct Context *context, JitsiConnection *connection);

JitsiConference *gstmeet_connection_join_conference(struct Context *context,
                                                    JitsiConnection *connection,
                                                    GMainContext *glib_main_context,
                                                    const struct ConferenceConfig *config);

bool gstmeet_conference_connected(struct Context *context, JitsiConference *conference);

bool gstmeet_conference_leave(struct Context *context, JitsiConference *conference);

bool gstmeet_conference_set_muted(struct Context *context,
                                  JitsiConference *conference,
                                  MediaType media_type,
                                  bool muted);

GstPipeline *gstmeet_conference_pipeline(struct Context *context, JitsiConference *conference);

GstElement *gstmeet_conference_audio_sink_element(struct Context *context,
                                                  JitsiConference *conference);

GstElement *gstmeet_conference_video_sink_element(struct Context *context,
                                                  JitsiConference *conference);

void gstmeet_conference_on_participant(struct Context *context,
                                       JitsiConference *conference,
                                       GstBin *(*f)(struct Participant, void *),
                                       void *callback_context);

bool gstmeet_conference_set_pipeline_state(struct Context *context,
                                           JitsiConference *conference,
                                           GstState state);

#endif /* gstmeet_h */
