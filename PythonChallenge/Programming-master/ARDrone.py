	

    """
    A simple python script to control a Parrot AR Drone 2.0 quadcopter.
    Uses curses to display some simple graphics and handle various
    key controls nicely. Written as a solution to the UNH Cyber
    Security Club's Quadcopter Hacking event.
     
    MAKE SURE YOUR TERMINAL WINDOW IS AT LEAST 80x20 CHARACTERS!
     
    Author: Adam M. Holmes
    """
     
    import socket
    import curses
    from time import sleep
     
    # Drone IP and UDP port
    AR_IP = "192.168.1.1";
    AR_PORT = 5556;
     
    #########################################################################################
     
    def send_command(c, sock):
        for x in range(1, 1000):
            sock.sendto(c, (AR_IP, AR_PORT));
     
    #########################################################################################
     
    def input_loop(win, sock):
        curses.init_pair(2, curses.COLOR_BLACK, curses.COLOR_BLACK);
        counter = 0;
        while True:
            c = win.getch();
            counter += 1;
            if (counter > 1024): counter = 1;
            win.refresh();
            if (c == ord('q')):
                # Quit
                curses.nocbreak();
                win.keypad(0);
                curses.echo()
                curses.endwin();
                exit(1);
            elif (c == ord('t')):
                # Takeoff
                win.addstr(10, 16, "[t]", curses.color_pair(2));
                win.refresh();
                send_command("AT*REF=" + str(counter) + ",290718208\r", sock);
                win.addstr(10, 16, "[t]", curses.A_REVERSE);
            elif (c == ord('l')):
                # Land
                win.addstr(11, 16, "[l]", curses.color_pair(2));
                win.refresh();
                send_command("AT*REF=" + str(counter) + ",290717696\r", sock);
                win.addstr(11, 16, "[l]", curses.A_REVERSE);
            elif (c == ord('e')):
                # Set emergency
                win.addstr(16, 16, "[e]", curses.color_pair(2));
                win.refresh();
                sock.sendto("AT*REF=" + str(counter) + ",290717952\r", (AR_IP, AR_PORT));
                sock.sendto("AT*REF=" + str(counter) + ",290717952\r", (AR_IP, AR_PORT));
                win.addstr(16, 16, "[e]", curses.A_REVERSE);
            elif (c == ord('c')):
                # Clear emergency
                win.addstr(17, 16, "[c]", curses.color_pair(2));
                win.refresh();
                sock.sendto("AT*REF=" + str(counter) + ",290717952\r", (AR_IP, AR_PORT));
                sock.sendto("AT*REF=" + str(counter) + ",290717952\r", (AR_IP, AR_PORT));
                win.addstr(17, 16, "[c]", curses.A_REVERSE);
            elif (c == ord('w')):
                # Up
                win.addstr(9, 38, "[w]", curses.color_pair(2));
                win.refresh();
                send_command("AT*PCMD=" + str(counter) + ",1,0,0,1056964608,0\r", sock);
                win.addstr(9, 38, "[w]", curses.A_REVERSE);
            elif (c == ord('s')):
                # Down
                win.addstr(10, 38, "[s]", curses.color_pair(2));
                win.refresh();
                send_command("AT*PCMD=" + str(counter) + ",1,0,0,-1110651699,0\r", sock);
                win.addstr(10, 38, "[s]", curses.A_REVERSE);
            elif (c == ord('a')):
                # Rotate left
                win.addstr(9, 60, "[a]", curses.color_pair(2));
                win.refresh();
                send_command("AT*PCMD=" + str(counter) + ",1,0,0,0,1056964608\r", sock);
                win.addstr(9, 60, "[a]", curses.A_REVERSE);
            elif (c == ord('d')):
                # Rotate right
                win.addstr(10, 60, "[d]", curses.color_pair(2));
                win.refresh();
                send_command("AT*PCMD=" + str(counter) + ",1,0,0,0,-1090519040\r", sock);
                win.addstr(10, 60, "[d]", curses.A_REVERSE);
            elif (c == curses.KEY_UP):
                # Move forward
                win.addstr(15, 44, "[/\]", curses.color_pair(2));
                win.refresh();
                send_command("AT*PCMD=" + str(counter) + ",1,0,-1090519040,0,0\r", sock);
                win.addstr(15, 44, "[/\]", curses.A_REVERSE);
            elif (c == curses.KEY_DOWN):
                # Move backward
                win.addstr(17, 44, "[\/]", curses.color_pair(2));
                win.refresh();
                send_command("AT*PCMD=" + str(counter) + ",1,0,1056964608,0,0\r", sock);
                win.addstr(17, 44, "[\/]", curses.A_REVERSE);
            elif (c == curses.KEY_LEFT):
                # Move left
                win.addstr(16, 41, "[<]", curses.color_pair(2));
                win.refresh();
                send_command("AT*PCMD=" + str(counter) + ",1,1056964608,0,0,0\r", sock);
                win.addstr(16, 41, "[<]", curses.A_REVERSE);
            elif (c == curses.KEY_RIGHT):
                # Move right
                win.addstr(16, 48, "[>]", curses.color_pair(2));
                win.refresh();
                send_command("AT*PCMD=" + str(counter) + ",1,-1090519040,0,0,0\r", sock);
                win.addstr(16, 48, "[>]", curses.A_REVERSE);
     
    #########################################################################################
     
    def draw_layout(win):
        # Banner
        curses.init_pair(1, curses.COLOR_BLUE, curses.COLOR_BLACK);
        win.addstr(1, 36, " _   _ _   _ _   _  ____  ____   ____ ", curses.color_pair(1));
        win.addstr(2, 36, "| | | | \ | | | | |/ ___|/ ___| / ___|", curses.color_pair(1));
        win.addstr(3, 36, "| | | |  \| | |_| | |    \___ \| |    ", curses.color_pair(1));
        win.addstr(4, 36, "| |_| | |\ |  _  | |___  ___) | |___ ", curses.color_pair(1));
        win.addstr(5, 36, " \___/|_| \_|_| |_|\____||____/ \____|", curses.color_pair(1));
        # Settings box
        win.addstr(2, 4, "SETTINGS", curses.A_BOLD);
        win.addstr(3, 4, "IP: \t" + str(AR_IP));
        win.addstr(4, 4, "Port: \t" + str(AR_PORT));
        win.hline(1, 3, '#', 28);
        win.hline(5, 3, '#', 28);
        win.vline(1, 2, '#', 5);
        win.vline(1, 30, '#', 5);
        # Commands box
        win.addstr(8, 4, "COMMANDS", curses.A_BOLD);
        win.addstr(9, 4, "Quit:");
        win.addstr(10, 4, "Takeoff:");
        win.addstr(11, 4, "Land:");
        win.addstr(9, 16, "[q]", curses.A_REVERSE);
        win.addstr(10, 16, "[t]", curses.A_REVERSE);
        win.addstr(11, 16, "[l]", curses.A_REVERSE);
        win.hline(7, 3, '#', 20);
        win.hline(12, 3, '#', 20);
        win.vline(7, 2, '#', 6);
        win.vline(7, 22, '#', 6);
        # Emergency box
        win.addstr(15, 4, "EMERGENCY", curses.A_BOLD);
        win.addstr(16, 4, "Set:");
        win.addstr(17, 4, "Clear:");
        win.addstr(16, 16, "[e]", curses.A_REVERSE);
        win.addstr(17, 16, "[c]", curses.A_REVERSE);
        win.hline(14, 3, '#', 20);
        win.hline(18, 3, '#', 20);
        win.vline(14, 2, '#', 5);
        win.vline(14, 22, '#', 5);
        # Altitude box
        win.addstr(8, 27, "ALTITUDE", curses.A_BOLD);
        win.addstr(9, 27, "Up:");
        win.addstr(10, 27, "Down:");
        win.addstr(9, 38, "[w]", curses.A_REVERSE);
        win.addstr(10, 38, "[s]", curses.A_REVERSE);
        win.hline(7, 25, '#', 20);
        win.hline(11, 25, '#', 20);
        win.vline(7, 25, '#', 5);
        win.vline(7, 44, '#', 5);
        # Rotation box
        win.addstr(8, 49, "ROTATION", curses.A_BOLD);
        win.addstr(9, 49, "Left:");
        win.addstr(10, 49, "Right:");
        win.addstr(9, 60, "[a]", curses.A_REVERSE);
        win.addstr(10, 60, "[d]", curses.A_REVERSE);
        win.hline(7, 47, '#', 20);
        win.hline(11, 47, '#', 20);
        win.vline(7, 47, '#', 5);
        win.vline(7, 66, '#', 5);
        # Steering box
        win.addstr(14, 27, "STEERING", curses.A_BOLD);
        win.addstr(15, 27, "Forward:");
        win.addstr(16, 27, "Left/Right:");
        win.addstr(17, 27, "Backward:");
        win.addstr(15, 44, "[/\]", curses.A_REVERSE);
        win.addstr(17, 44, "[\/]", curses.A_REVERSE);
        win.addstr(16, 41, "[<]", curses.A_REVERSE);
        win.addstr(16, 48, "[>]", curses.A_REVERSE);
        win.hline(13, 25, '#', 29);
        win.hline(18, 25, '#', 29);
        win.vline(13, 25, '#', 5);
        win.vline(13, 53, '#', 5);
        # Art
        win.addstr(13, 56, "ARDrone Control Script");
        win.addstr(14, 56, "By: Adam M. Holmes");
        win.addstr(15, 60, "_________", curses.color_pair(1));
        win.addstr(16, 60, "  ,-'-.____()", curses.color_pair(1));
        win.addstr(17, 60, " (____.--\"\"\"", curses.color_pair(1));
        win.addstr(18, 60, " -'--'-", curses.color_pair(1));
       
     
    #########################################################################################
     
    def main():
        # Create connection to drone
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM);
     
        # Initialize curses window settings
        scr = curses.initscr();
        (x, y) = scr.getmaxyx();
        if (x < 20 or y < 80):
            curses.nocbreak();
            curses.echo()
            curses.endwin();
            exit(-1);
        win = curses.newwin(20, 80, 0, 0);
        curses.noecho();
        curses.cbreak();
        curses.curs_set(0)
        curses.start_color();
        win.keypad(1);
        win.border(0);
     
        # Draw curses window to screen, start input loop
        draw_layout(win);
        win.refresh();
        input_loop(win, sock);
     
    #########################################################################################
     
    main();

