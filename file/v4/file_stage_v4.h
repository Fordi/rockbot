#ifndef FILE_STAGE_v301H
#define FILE_STAGE_v301H

#include "file/format/st_common.h"
#include "defines.h"

namespace format_v4 {


struct file_dialog { // DONE - Stage x2
    char face_graphics_filename[20];
    bool top_side;
    Sint8 text1_string_ids[FS_DIALOG_LINES];
    Sint8 text2_string_ids[FS_DIALOG_LINES];
    Sint8 answer1_string_ids[FS_DIALOG_LINES];
    Sint8 answer2_string_ids[FS_DIALOG_LINES];


    file_dialog() {
        top_side = true;
        face_graphics_filename[0] = '\0';
        for (int i=0; i<FS_DIALOG_LINES; i++) {
            text1_string_ids[i] = -1;
            text2_string_ids[i] = -1;
            answer1_string_ids[i] = -1;
            answer2_string_ids[i] = -1;
        }
    }
};

// defines a castle intro and details
struct file_castle {
    st_position points[CASTLE_STAGES_MAX];
    char filename[FS_FILENAME_SIZE];                                        // castle background image
    file_dialog boss_defeated_dialog;                                       // boss defeated dialog
};




struct file_link { // DONE - Stage
    Sint8 id_map_origin;
    Sint8 id_map_destiny;
    st_position_uint8 pos_origin;
    st_position_uint8 pos_destiny;
    Uint8 size;
    bool bidirecional;
    bool is_door;
    Sint8 type;
    file_link() {
        id_map_origin = -1;
        id_map_destiny = -1;
        size = 1;
        bidirecional = false;
        is_door = false;
        type = LINK_VERTICAL;
    }
};

struct file_boss { // DONE - Stage
    Sint8 id_npc;
    Sint8 id_weapon;
    char name[20];
    Sint8 name_string_id;
    char face_graphics_filename[20];
    file_boss() {
        name_string_id = -1;
        id_npc = -1;
        id_weapon = -1;
        sprintf(name, "%s", "Boss");
        face_graphics_filename[0] = '\0';
    }
};


struct file_colorcycle { // DONE - Stage
    st_color color[FS_COLORCYCLE_MAX_ITEMS][COLOR_KEY_LENGTH];
    Sint16 duration[FS_COLORCYCLE_MAX_ITEMS][COLOR_KEY_LENGTH];
};

struct file_stage {
    char name[FS_CHAR_NAME_SIZE];
    char bgmusic_filename[FS_CHAR_FILENAME_SIZE];
    file_link links[FS_STAGE_MAX_LINKS];
    file_boss boss;
    file_dialog intro_dialog;
    file_dialog boss_dialog;
    file_colorcycle colorcycle;
    char tileset_filename[FS_CHAR_FILENAME_SIZE];
    bool autoscroll;

    // CONSTRUCTOR //
    file_stage() {
        autoscroll = false;
        boss = file_boss();
        sprintf(name, "%s", "Stage");
        bgmusic_filename[0] = '\0';
        tileset_filename[0] = '\0';
    }
};





/**
 * @brief
 *
 */
struct file_stages {
    file_stage stages[FS_MAX_STAGES];
    file_stages() {
        for (int i=0; i<FS_MAX_STAGES; i++) {
            sprintf(stages[i].name, "Stage [%d]", i);
        }
    }
};

}

#endif // FILE_STAGE_H


