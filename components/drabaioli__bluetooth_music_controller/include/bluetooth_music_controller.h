void setup_bluetooth_controller(void);


typedef enum
{
  MEDIA_METADATA_SONG = 0,
  MEDIA_METADATA_ARTIST,
  MEDIA_METADATA_ALBUM,
} media_metadata_key_t;

typedef void (* media_metadata_cb_t)( media_metadata_key_t media_metadata_key, char * media_metadata_value );

void bl_controller_register_media_metadata_cb( media_metadata_cb_t media_metadata_cb );


BT_DEVICE_CONNECTED
BT_DEVICE_DISCONNECTED
BT_METADATA
  MEDIA_METADATA_SONG = 0,
  MEDIA_METADATA_ARTIST,
  MEDIA_METADATA_ALBUM,

