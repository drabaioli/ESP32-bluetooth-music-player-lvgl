idf_component_register(SRCS "bluetooth_music_controller.c"
                            "bt_app_av.c"
                            "bt_app_core.c"
                            "main.c"
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES bt)
