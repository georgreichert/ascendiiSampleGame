#include "../headers/fightclub.h"

std::vector<Ability*> Database::abilities;
std::vector<Fighter*> Database::fighters;
bool Database::initialized = false;
Sprite* Database::hitSprite = nullptr;
Sprite* Database::threeTwoOne[3];

std::vector<Ability*> Database::getAbilities() {
    Database::initialize();
    return Database::abilities;
}

Ability* Database::getAbility(std::string name) {
    Database::initialize();
    for (Ability* ab : Database::abilities) {
        if (ab->getName().compare(name) == 0) {
            return ab;
        }
    }
    return nullptr;
}

std::vector<Fighter*> Database::getFighters() {
    Database::initialize();
    return Database::fighters;
}

Fighter* Database::getFighter(std::string name) {
    Database::initialize();
    for (Fighter* fi : Database::fighters) {
        if (fi->getName().compare(name) == 0) {
            return fi;
        }
    }
    return nullptr;
}

Sprite* Database::getHitSprite() {
    Database::initialize();
    return Database::hitSprite;
}

Sprite* Database::getThreeTwoOne(int index) {
    Database::initialize();
    return Database::threeTwoOne[index];
}

void Database::initialize() {
    if (!Database::initialized) {
        Database::initialized = true;

        Database::abilities.push_back(new Ability("Right Hook"));
        Database::abilities.push_back(new Ability("Left Hook", 0.9f, 1.1f, 0.1f));
        Database::abilities.push_back(new Ability("Roundhouse Kick", 1.3f, 0.6f, 0.5f));
        Database::abilities.push_back(new Ability("Safe Blow", 0.7f, 1.4f, 0.1f));
        Database::abilities.push_back(new Ability("Targeted Strike", 1.2f, 0.8f, 0.0f));
        Database::abilities.push_back(new Ability("Bodyslam", 1.8f, 0.4f, 0.5f));

        std::string butch[28] = {
            "@@@@@@@@@@@&@&@@@ @@&%%%%%%###########%&@@@@@@@@@@@@@@@@@@@@",
            "@@@@@@@@@@@&&@@@&&%&%%#(*,,.          ..,*((#%&@@@@@@@@@@@@@",
            "@@@@@@@@@@@@@@&%#/**,,,.                 ,,*,*(#(%&@&@@@@@@@",
            "@@@@@@@@@@@@@#*,,*,.,                        .**/(#@@@@@@@@@",
            "@@@@&&@@#&@#//***,..                            .,*&@@@@@@@%",
            "@@@@@@@%&&/*..,,,..                              .,*/@@@@@# ",
            "@@@@@@@@#,,   ...,, .                             ,,/(@@@@@@",
            "@@@@@@@/*       .....,,...          .      ....,,,,*//%@@@@@",
            "@@@@@@&,*..   . ..,.,..,,,,*.,......      ..,,,,***//((@@@@@",
            "@@@@@@(*.....,,..... ......,.. ..........   ..,*****/((%&%%&",
            "@@@@@@/*  .,.....,..       ..       ,.,,**,,,,,*****/(#%&&%&",
            "@@@@&,(*     .             ..,,***/(/(###(((///(/(/((##%&&&&",
            "@@&&,%. .@(,. .  ..    .   ,(#&&@@@@@&&@@@@@@%(/#@@@@%%%&&%%",
            "@@@&,. ,. (/(    .......  .... ,(%%#(((##/%%%##*/@@@&@&%%&%%",
            "@@@& ./((%@*  ..,.,,,......    .. .*/***(%##%,  .(#%#%%&%%%%",
            "@@@&,,.//&&  .,****,,..,,.,,,,,,,.  .,*(((%%.   .,###%&%&%%%",
            "@@@&&, .     ****//*,*,,,,**/((/*,....,*#(      ./(((%&%%%##",
            "@@@&&&%(...*.,.*,**,,,**/((####(///*/((/%&&@@@@@%%%(#%%%&%%#",
            "@@@&&&%,/@&%@(,,,...**((%%#%((/****(%(,. ..#%#&@(((#%%%#####",
            "@@@&&@(..(@@@#,,.,//((%%%&%((/***/%/.,,*//((%%#%#(#%#####%##",
            "@&&&&@,...%@@#**/((((#(#((/**/*,,(((##(((/(((((%%###########",
            "@@&&@(  .../&%#%%##%%##(///*(/**#%&%%%&%%%%&&@@&#%##########",
            "@@&%&  ....,/(@@@@@@@@@%####((#%&%%%%%&&%%%%%#%%&###########",
            "@%#*//. .,,,,/%&@@@@@@@@@&&&#%%&&%&%%%%%%&&&&&%%%###(####(((",
            "%#%%####/,*****(&@@@@@@@@@@@@@@@&#(/*,.,*((##%&%#####(###(((",
            "(/#(#%%#(###/*//(%@@@@@@@@@@@@@@@@@@&&%&%%%#%&%##########(((",
            "&#((/(#%&&%&%&(((#%&@@@@@@@@@@@@@@@@@@@@@@@@@#######((((((#/",
            "@@&&%&##(#&@@@&&#(##&&@@@@@@@@@@@@@@@@@&%##########(((((((/."
        };
        Database::fighters.push_back(new Fighter("Butch Coolidge", 100.0f, 15.0f, 1.0f, 1.5f,
                Database::getAbility("Right Hook"), Database::getAbility("Targeted Strike"), new Sprite(butch, COLOR_WHITE, butch[0].length(), 28)));
        std::string clegane[28] = {
            ",,,,,************.                    .(   ,    /*******/***",
            ",,,,,*,,*****,                      . .#%&## ,*    ///////**",
            ",,,,,,,,,***,                  /&&%#&@&%#&&&&%%%#./../(////*",
            ",,,,,,,,*** *              ,/%@@@@@@@@@&&&##((%@@@&%****///*",
            ",..,,,,,,*                *#%@@@@@@@@@@@%#*/*//&@@@@&@ ,*///",
            ".....,,,,  /       ( ,,(////(%&&&@@&%%#((*,,,,/(@@@@@@@.////",
            ",,,...,,, .*/,**   #/(//(//////(**//*******,,,*/#@@@@@@(**//",
            ",,..      .,(/*/*/*(#/*/(%///***%************,**/#@@@@@&****",
            ",,.    .   .////(///((/*/#/*/***(/*********,*,***#&@@@@/,,,,",
            ",,,....     */*/(((((#/(///*****(((**********,,,*%&@@@#,,,,,",
            ",,,,,,,    */(#%@&%(/((*/((/*/***(*/***,*,**,,,,,#&@&@(..,,,",
            ",,,,,,,   ,*((#((((#&&#////*/*,.,(/**********,,,,/%@@#...,,.",
            ",,,,*,.    #(/(((&%**#(##%#*(,/*(%%&&%%##/*,,,,,,/@&(*(.....",
            "**,,,.  * .(///((/(((#%&%#(***((%@&//*******,,,,*#&#**( .  .",
            "*/**, ./((/((((//(((##(///(///((##((((/*,*//*,,,/&%#*,.    .",
            "////   /@%/(((///////&#/(/***,,///(/*****//***,*#&%(, .....,",
            "///*, .*@@&#((//(*/##///@****/#/**(*/////****,*(&&.* ,,...,,",
            "****  .&@@@%#(///(%##%%/**,,,**#/*/**,****,**/%&@/ ,,,..    ",
            "///   *@@@&&%(/(&&@@@@@%#%#%%(/(#/*/*,,,***/#&@%/,,,*,,.    ",
            "      #@@@@&#%%@&%@@@&(#/#&&&&&&&#///*/**(#&@@/*,,,,,,,.    ",
            "     , @@@@@&@&&&#(/(((#####&%%&&&/(((#%&@@@@/,....,,,,,.   ",
            "  //##(@@@@@@@@@&%###&&##/**//#%&&#&&&@@&@@&(,,,.,,,,,,,.   ",
            "//((#%&%@@@@@@@@@@@&&&&&%%#%##%%&@#%&%@@@@&#,,,,,........   ",
            "/((##%%&@@@@@@@@@@@@@@@@&&&@@@@@@@@@@@@@@& .,,..........    ",
            "#(##%%%&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/.     .. ......    ",
            "(((#%@%%%&&@&@@@@@@@@@@@@@@@@@@@@@@@@@#(..,,,..     ....    ",
            "((((#%#%&%&%&@@&@@@@@@@@@@@@@@@@@@@%((/*.,,,,*,,,    ....   ",
            "#(#####%%&%%%%&%@&%%%&&@@&@@&%%####(//**,,*,.,,,,,    ....  "
        };
        Database::fighters.push_back(new Fighter("Gregor Clegane", 120.0f, 22.0f, 0.70f, 1.3f,
                Database::getAbility("Right Hook"), Database::getAbility("Bodyslam"), new Sprite(clegane, COLOR_WHITE, clegane[0].length(), 28)));
        Database::fighters.push_back(new Fighter("Rocky Balboa", 90.0f, 18.0f, 1.2f, 1.5f,
                Database::getAbility("Safe Blow"), Database::getAbility("Targeted Strike")));
        Database::fighters.push_back(new Fighter("Fat Bastard", 120.0f, 11.0f, 1.4f, 2.0f,
                Database::getAbility("Left Hook"), Database::getAbility("Bodyslam")));
        Database::fighters.push_back(new Fighter("Chuck Norris", 100.0f, 15.0f, 1.1f, 1.4f,
                Database::getAbility("Targeted Strike"), Database::getAbility("Roundhouse Kick")));

        std::string hit[10] = {
            "        A    _ ",
            "       /*\  /*|",
            "  ____/***\/**/",
            "  \**********/ ",
            "   \********/  ",
            "    \******/   ",
            "    /******\   ",
            "   /**_/\***\  ",
            "  /*_/   \**|  ",
            "  |/      \/   "
        };
        Database::hitSprite = new Sprite(hit, COLOR_PINK, hit[0].length(), 10);

        std::string three[11] = {
            "   ########   ",
            " ####    #### ",
            "##          ##",
            "            ##",
            "         #### ",
            "      #####   ",
            "         #### ",
            "            ##",
            "##          ##",
            " ####    #### ",
            "   ########   ",
        };
        Database::threeTwoOne[0] = new Sprite(three, COLOR_YELLOW, three[0].length(), 11);

        std::string two[11] = {
            "     ######   ",
            "   ########## ",
            " ####     ####",
            "           ###",
            "         #### ",
            "       ####   ",
            "     ####     ",
            "   ####       ",
            " ####         ",
            " #############",
            " #############",
        };
        Database::threeTwoOne[1] = new Sprite(two, COLOR_YELLOW, two[0].length(), 11);

        std::string one[11] = {
            "    #####",
            "   ######",
            "  ### ###",
            " ###  ###",
            "###   ###",
            "      ###",
            "      ###",
            "      ###",
            "      ###",
            "      ###",
            "      ###",
        };
        Database::threeTwoOne[2] = new Sprite(one, COLOR_YELLOW, one[0].length(), 11);
    }
}

void Database::destroy() {
    if (Database::initialized) {
        for (Ability* ability : Database::abilities) {
            delete ability;
        }
        for (Fighter* fighter : Database::fighters) {
            delete fighter;
        }
        delete Database::hitSprite;
        for (int i = 0; i < 3; i++) {
            delete Database::threeTwoOne[i];
        }
    }
}
