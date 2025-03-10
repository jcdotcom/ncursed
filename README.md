
    #####################################################
    #                                                   #
    #   NCursed                                         #
    #       A Simple TUI Game written in C++            #
    #       using the NCurses library                   #
    #                                                   #
    #       Written by jcdotcom, started 01/26/2025     #
    #               current ver: 0.01a   02/09/2025     #
    #                                                   #
    #####################################################


~~~~~{   HELP   }~~~~~

    W,A,S,D to move
    SPACE to pick up items

~~~~~{   CHANGELOG   }~~~~~

    ---[ 0.01b - 03/10/2025 ]---

        -changing the usage of mapXs and mapYs to be declared at start
        -changing room generation: all rooms generated at init now

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

