
    #####################################################
    #                                                   #
    #   NCursed                                         #
    #       A Simple TUI Game written in C++            #
    #       using the NCurses library                   #
    #                                                   #
    #       Written by jcdotcom, started 01/26/2025     #
    #               current ver: 0.03a   06/30/2025     #
    #                                                   #
    #####################################################


~~~~~{   HELP   }~~~~~

    W,A,S,D to move
    SPACE to pick up items

~~~~~{   CHANGELOG   }~~~~~

    ---[ 0.03a - 07/02/2025 ]---

        -bug fixes on message window
        -more progress on key and locked door generation / handling
        -added functionality for multiple levels

    ---[ 0.021a - 06/30/2025 ]---

        -bug fixes on door generation and room transitions
        -began adding key and locked door generation

    ---[ 0.02a - 06/19/2025 ]---

        -began rework of room procedural generation

    ---[ 0.01a - 02/09/2025 ]---

        -expanded game area for wall rendering
        -started writing functionality for generating and 
            getting rooms
        -started building the data structure which will 
            hold all of the Area objects, using a 2d 
            vector for now (not currently working)
        -started building room switch functionality
            getRoom(), generateRoom()

    ---[ 0.01 - 02/02/2025 ]---

