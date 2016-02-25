#include "fio_strings.h"

#include <iostream>
#include <fstream>

#include "defines.h"
#include "aux_tools/stringutils.h"
#include "file/fio_common.h"

extern std::string FILEPATH;
extern std::string GAMEPATH;

#define STRINGS_INGAME_FILENAME "/strings_ingame.dat"
#define STRINGS_COMMON_FILENAME "/common_strings.dat"

fio_strings::fio_strings()
{
}


namespace format_v4 {

    fio_strings::fio_strings()
    {
    }

    std::string fio_strings::get_ingame_string(int n)
    {
        if (string_list.size() == 0) {
            string_list = load_game_strings();
        }
        if (n < 0 || n > string_list.size()) {
            return "";
        }
        return string_list.at(n);
    }


    std::vector<std::string> fio_strings::load_game_strings()
    {
        return load_game_strings_from_file(get_game_strings_filename());
    }

    std::vector<std::string> fio_strings::load_game_strings_from_file(std::string filename)
    {
        std::vector<std::string> res;
        filename = StringUtils::clean_filename(filename);
        std::ifstream fp(filename.c_str());

        if (!fp.is_open()) {
            std::cout << "[WARNING] file_io::load_game_strings - file '" << filename << "' not found, will generate default..." << std::endl;
            if (filename == get_game_strings_filename()) {
                create_default_ingame_strings();
            } else if (filename == get_common_strings_filename()) {
                create_default_common_strings();
            }
            fp.open(filename.c_str(), std::ios::in | std::ios::binary | std::ios::app);
            if (!fp.is_open()) {
                std::cout << "[WARNING] file_io::load_game_strings - Critical error, can't open' '" << filename << "' for reading." << std::endl;
            }
        }

        std::string str;
        while (getline(fp, str)) {
            StringUtils::replace_all(str, "\n", "");
            StringUtils::replace_all(str, "\r", "");
            res.push_back(str);
        }
        fp.close();

        if (res.size() == 0) {
            if (filename == get_game_strings_filename()) {
                create_default_ingame_strings();
            } else if (filename == get_common_strings_filename()) {
                create_default_common_strings();
            }
        }

        return res;
    }

    void fio_strings::save_game_strings(std::vector<std::string> list, std::string filename)
    {
        std::ofstream fp(filename.c_str());
        if (!fp.is_open()) {
            std::cout << ">> fio_strings::create_default_ingame_strings: Could not open '" << filename << "' for writting." << std::endl;
            return;
        }

        for (int i=0; i<strings_ingame_COUNT; i++) {
            std::string line = list.at(i) + std::string("\n");
            fp << line.c_str();
        }
        fp.close();
    }

    std::string fio_strings::get_common_strings_filename()
    {
        std::string filename = FILEPATH + STRINGS_COMMON_FILENAME;
        filename = StringUtils::clean_filename(filename);
        return filename;
    }

    std::string fio_strings::get_game_strings_filename()
    {
        std::string filename = std::string(GAMEPATH) + "/shared/" + STRINGS_INGAME_FILENAME;
        filename = StringUtils::clean_filename(filename);
        return filename;
    }


    bool format_v4::fio_strings::file_exists(std::string filename) const
    {
        bool res = false;
        FILE *fp;
        fp = fopen(filename.c_str(), "rb");
        if (fp) {
            res = true;
            fclose(fp);
        }
        return res;
    }

    void fio_strings::create_default_ingame_strings()
    {
        char lines[strings_ingame_COUNT][STRINGS_LINE_SIZE];

        sprintf(lines[strings_ingame_newgame], "%s", "NEW GAME");
        sprintf(lines[strings_ingame_loadgame], "%s", "LOAD GAME");
        sprintf(lines[strings_ingame_config], "%s", "CONFIG");
        sprintf(lines[strings_ingame_about], "%s", "ABOUT");
        sprintf(lines[strings_ingame_password], "%s", "PASSWORD");
        sprintf(lines[strings_ingame_gameover], "%s", "GAME OVER");
        sprintf(lines[strings_ingame_and], "%s", "AND");
        sprintf(lines[strings_ingame_selectgame], "%s", "SELECT GAME");
        sprintf(lines[strings_ingame_savegameerror1], "%s", "ERROR WHILE SAVING GAME,");
        sprintf(lines[strings_ingame_savegameerror2], "%s", "PLEASE CHECK THAT THE DEVICE OR");
        sprintf(lines[strings_ingame_savegameerror3], "%s", "FILE IS NOT WRITE-PROTECTED.");
        sprintf(lines[strings_ingame_copyrightline], "%s", "\xA9 2009-2016 UPPERLAND STUDIOS");
        //sprintf(lines[strings_ingame_copyrightline], "%s", "(c) 2009-2016 UPPERLAND STUDIOS");
        sprintf(lines[strings_ingame_audio], "%s", "AUDIO");
        sprintf(lines[strings_ingame_input], "%s", "INPUT");
        sprintf(lines[strings_ingame_video], "%s", "VIDEO");
        sprintf(lines[strings_ingame_leavestage], "%s", "LEAVE STAGE");
        sprintf(lines[strings_ingame_video_windowed], "%s", "WINDOWED");
        sprintf(lines[strings_ingame_video_fullscreen], "%s", "FULLSCREEN");
        sprintf(lines[strings_ingame_video_noscale], "%s", "NO SCALE  ");
        sprintf(lines[strings_ingame_video_size2x], "%s", "SIZE2X    ");
        sprintf(lines[strings_ingame_video_scale2x], "%s", "SCALE2X   ");
        sprintf(lines[strings_ingame_config_restart1], "%s", "PLEASE RESTART THE GAME");
        sprintf(lines[strings_ingame_config_restart2], "%s", "FOR THE CONFIGURATION");
        sprintf(lines[strings_ingame_config_restart3], "%s", "TO TAKE EFFECT");
        sprintf(lines[strings_ingame_config_presstorestart], "%s", "PRESS A BUTTON TO RETURN");
        sprintf(lines[strings_ingame_pressanykey], "%s", "PRESS ANY KEY OR BUTTON");
        sprintf(lines[strings_ingame_config_set], "%s", "SET");
        sprintf(lines[strings_ingame_config_key_up], "%s", "UP");
        sprintf(lines[strings_ingame_config_key_down], "%s", "DOWN");
        sprintf(lines[strings_ingame_config_key_left], "%s", "LEFT");
        sprintf(lines[strings_ingame_config_key_right], "%s", "RIGHT");
        sprintf(lines[strings_ingame_config_key_jump], "%s", "JUMP");
        sprintf(lines[strings_ingame_config_key_dash], "%s", "DASH");
        sprintf(lines[strings_ingame_config_key_fire], "%s", "FIRE");
        sprintf(lines[strings_ingame_config_key_start], "%s", "START");
        sprintf(lines[strings_ingame_config_key_keyl], "%s", "BUTTON-L");
        sprintf(lines[strings_ingame_config_key_keyr], "%s", "BUTTON-R");
        sprintf(lines[strings_ingame_config_key_pressnew], "%s", "PRESS NEW KEY/BUTTON");
        sprintf(lines[strings_ingame_config_key_reset], "%s", "RESET TO DEFAULT");
        sprintf(lines[strings_ingame_config_key_directional], "%s", "DIRECTIONAL");
        sprintf(lines[strings_ingame_config_key_directional_analog], "%s", "ANALOG");
        sprintf(lines[strings_ingame_config_key_directional_digital], "%s", "DIGITAL");
        sprintf(lines[strings_ingame_passwordinvalid], "%s", "PASSWORD INVALID");
        sprintf(lines[strings_ingame_pressstart], "%s", "PRESS START");
        sprintf(lines[strings_ingame_engineerror], "%s", "ROCKBOT ENGINE ERROR");
        sprintf(lines[strings_ingame_nogames], "%s", "NO GAMES AVAILABLE");
        sprintf(lines[strings_ingame_quitgame], "%s", "QUIT GAME?");
        sprintf(lines[strings_ingame_yes], "%s", "YES");
        sprintf(lines[strings_ingame_no], "%s", "NO");
        sprintf(lines[strings_ingame_life], "%s", "LIFE");
        sprintf(lines[strings_ingame_item], "%s", "ITEM");
        sprintf(lines[strings_ingame_gotarmor_type_ability], "%s", "GIVE YOU THE ABILITY TO");
        sprintf(lines[strings_ingame_gotarmor_type_arms], "%s", "THIS IMPROVED ARMS WILL");
        sprintf(lines[strings_ingame_gotarmor_type_arms_msg1], "%s", "FIRE ALWAYS CHARGED");
        sprintf(lines[strings_ingame_gotarmor_type_arms_msg2], "%s", "CHARGE A LASER BEAM");
        sprintf(lines[strings_ingame_gotarmor_type_arms_msg3], "%s", "FIRE A SUPER-SHOT!");
        sprintf(lines[strings_ingame_gotarmor_type_arms_msg4], "%s", "THROW A HADOUKEN");
        sprintf(lines[strings_ingame_gotarmor_type_legs], "%s", "THOSE LIGHTER LEGS");
        sprintf(lines[strings_ingame_gotarmor_type_legs_msg1], "%s", "DASH IN MIDDLE-AIR.");
        sprintf(lines[strings_ingame_gotarmor_type_legs_msg2], "%s", "EXECUTE DOUBLE JUMP");
        sprintf(lines[strings_ingame_gotarmor_type_legs_msg3], "%s", "SHOURUYKEN (UP+DASH)");
        sprintf(lines[strings_ingame_gotarmor_type_legs_msg4], "%s", " ");
        sprintf(lines[strings_ingame_gotarmor_type_body], "%s", "THIS FORTIFIED BODY WILL");
        sprintf(lines[strings_ingame_gotarmor_type_body_msg1], "%s", "BE INTANGIBLE MORE TIME");
        sprintf(lines[strings_ingame_gotarmor_type_body_msg2], "%s", "TAKE HALF DAMAGE");
        sprintf(lines[strings_ingame_gotarmor_type_body_msg3], "%s", "AVOID PUSH-BACK ON HIT");
        sprintf(lines[strings_ingame_gotarmor_type_body_msg4], "%s", "RESIST SPIKES");
        sprintf(lines[strings_ingame_difficulty_select], "%s", "SELECT DIFFICULTY:");
        sprintf(lines[strings_ingame_difficulty_easy], "%s", "EASY");
        sprintf(lines[strings_ingame_difficulty_normal], "%s", "NORMAL");
        sprintf(lines[strings_ingame_difficulty_hard], "%s", "HARD");
        sprintf(lines[strings_ingame_config_input_selected_joystick], "%s", "SELECTED JOYSTICK");
        sprintf(lines[strings_ingame_config_input_buttons], "%s", "CONFIG BUTTONS");



        /// @TODO: add assert to check that we set all the values from the enum


        std::vector<std::string> res;
        for (int i=0; i<strings_ingame_COUNT; i++) {
            std::string line = std::string(lines[i]) + std::string("\n");

            std::cout << "fio_strings::create_default_ingame_strings[" << i << "]: " << line << std::endl;
            res.push_back(line);
        }

        save_game_strings(res, get_game_strings_filename());

    }

    void fio_strings::create_default_common_strings()
    {
        std::vector<std::string> res;
        for (int i=0; i<FS_MAX_STAGES; i++) {
            char line_value[FS_CHAR_NAME_SIZE];
            sprintf(line_value, "DIALOG_PERSON_NAME #%d", i);
            res.push_back(line_value);
        }

        // stage-start dialogs
        for (int i=0; i<FS_MAX_STAGES; i++) {
            // person dialogs
            char line_value[FS_COMMON_STRINGS_DIALOG];
            sprintf(line_value, "START-STAGE DIALOG #%d", i);
            res.push_back(line_value);
            // players dialogs
            for (int j=0; j<4; j++) {
                for (int k=0; k<3; k++) {
                    char player_line_id[FS_COMMONSTRING_ID_SIZE];
                    char player_line_value[FS_COMMON_STRINGS_DIALOG];
                    sprintf(player_line_id, "STAGE_DLG_PLAYER_%d_%d_%d", j, i, k);
                    sprintf(player_line_value, "STAGE DIALOG PLAYER %d %d %d", j, i, k);
                    res.push_back(player_line_value);
                }
            }
        }


        // stage-boss dialogs
        for (int i=0; i<FS_MAX_STAGES; i++) {
            // person dialogs
            char line_value[FS_COMMON_STRINGS_DIALOG];
            sprintf(line_value, "BOSS DIALOG #%d", i);
            res.push_back(line_value);
            // players dialogs
            for (int j=0; j<4; j++) {
                // 3 lines
                for (int k=0; k<3; k++) {
                    char player_line_id[FS_COMMONSTRING_ID_SIZE];
                    char player_line_value[FS_COMMON_STRINGS_DIALOG];
                    sprintf(player_line_id, "BOSS_DLG_PLAYER_%d_%d %d", j, i, k);
                    sprintf(player_line_value, "BOSS DIALOG PLAYER %d %d %d", j, i, k);
                    res.push_back(player_line_value);
                }
            }
        }

        save_common_strings(res);
    }




    std::vector<std::string> fio_strings::get_common_strings()
    {
        if (FILEPATH == "") {
            std::cout << "FIO_STRINGS - NO FILEPATH count: " << common_strings_list.size() << std::endl;
            return common_strings_list;
        }

        if (common_strings_list.size() == 0) {
            std::cout << "FIO_STRINGS - LOAD count: " << common_strings_list.size() << std::endl;
            common_strings_list = load_game_strings_from_file(get_common_strings_filename());
        }
        return common_strings_list;
    }

    std::string fio_strings::get_common_string(int id)
    {

        if (id == -1) {
            return std::string("");
        }
        if (FILEPATH == "") {
            return std::string("");
        }

        std::cout << "### fio_strings::get_common_string - id: " << id << std::endl;

        if (common_strings_list.size() == 0) {
            common_strings_list = load_game_strings_from_file(get_common_strings_filename());
        }

        if (id >= common_strings_list.size()) {
            return std::string("");
        }

        return common_strings_list.at(id);
    }


    void fio_strings::save_common_strings(std::vector<std::string> data)
    {
        save_game_strings(data, get_common_strings_filename());
    }

    void fio_strings::create_files()
    {
        create_default_ingame_strings();
        create_default_common_strings();
    }










}// namepsace
