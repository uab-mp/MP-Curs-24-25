#ifndef __KEYBOARD_SDL_INCLUDED_
#define __KEYBOARD_SDL_INCLUDED_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)
#include <SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#endif


#define NUM_KEYBOARD_KEY_CODES                           SDL_NUM_SCANCODES

#define KEYBOARD_NONE                                    SDLK_UNKNOWN


#define KEYBOARD_RETURN                                  SDLK_RETURN
#define KEYBOARD_ESCAPE                                  SDLK_ESCAPE
#define KEYBOARD_BACKSPACE                               SDLK_BACKSPACE
#define KEYBOARD_TAB                                     SDLK_TAB
#define KEYBOARD_SPACE                                   SDLK_SPACE
#define KEYBOARD_EXCLAIM                                 SDLK_EXCLAIM
#define KEYBOARD_QUOTEDBL                                SDLK_QUOTEDBL
#define KEYBOARD_HASH                                    SDLK_HASH
#define KEYBOARD_PERCENT                                 SDLK_PERCENT
#define KEYBOARD_DOLLAR                                  SDLK_DOLLAR
#define KEYBOARD_AMPERSAND                               SDLK_AMPERSAND
#define KEYBOARD_QUOTE                                   SDLK_QUOTE
#define KEYBOARD_LEFTPAREN                               SDLK_LEFTPAREN
#define KEYBOARD_RIGHTPAREN                              SDLK_RIGHTPAREN
#define KEYBOARD_ASTERISK                                SDLK_ASTERISK
#define KEYBOARD_PLUS                                    SDLK_PLUS
#define KEYBOARD_COMMA                                   SDLK_COMMA
#define KEYBOARD_MINUS                                   SDLK_MINUS
#define KEYBOARD_PERIOD                                  SDLK_PERIOD
#define KEYBOARD_SLASH                                   SDLK_SLASH
#define KEYBOARD_0                                       SDLK_0
#define KEYBOARD_1                                       SDLK_1
#define KEYBOARD_2                                       SDLK_2
#define KEYBOARD_3                                       SDLK_3
#define KEYBOARD_4                                       SDLK_4
#define KEYBOARD_5                                       SDLK_5
#define KEYBOARD_6                                       SDLK_6
#define KEYBOARD_7                                       SDLK_7
#define KEYBOARD_8                                       SDLK_8
#define KEYBOARD_9                                       SDLK_9
#define KEYBOARD_COLON                                   SDLK_COLON
#define KEYBOARD_SEMICOLON                               SDLK_SEMICOLON
#define KEYBOARD_LESS                                    SDLK_LESS
#define KEYBOARD_EQUALS                                  SDLK_EQUALS
#define KEYBOARD_GREATER                                 SDLK_GREATER
#define KEYBOARD_QUESTION                                SDLK_QUESTION
#define KEYBOARD_AT                                      SDLK_AT

#define KEYBOARD_LEFTBRACKET                             SDLK_LEFTBRACKET
#define KEYBOARD_BACKSLASH                               SDLK_BACKSLASH
#define KEYBOARD_RIGHTBRACKET                            SDLK_RIGHTBRACKET
#define KEYBOARD_CARET                                   SDLK_CARET
#define KEYBOARD_UNDERSCORE                              SDLK_UNDERSCORE
#define KEYBOARD_BACKQUOTE                               SDLK_BACKQUOTE
#define KEYBOARD_A                                       SDLK_a
#define KEYBOARD_B                                       SDLK_b
#define KEYBOARD_C                                       SDLK_c
#define KEYBOARD_D                                       SDLK_d
#define KEYBOARD_E                                       SDLK_e
#define KEYBOARD_F                                       SDLK_f
#define KEYBOARD_G                                       SDLK_g
#define KEYBOARD_H                                       SDLK_h
#define KEYBOARD_I                                       SDLK_i
#define KEYBOARD_J                                       SDLK_j
#define KEYBOARD_K                                       SDLK_k
#define KEYBOARD_L                                       SDLK_l
#define KEYBOARD_M                                       SDLK_m
#define KEYBOARD_N                                       SDLK_n
#define KEYBOARD_O                                       SDLK_o
#define KEYBOARD_P                                       SDLK_p
#define KEYBOARD_Q                                       SDLK_q
#define KEYBOARD_R                                       SDLK_r
#define KEYBOARD_S                                       SDLK_s
#define KEYBOARD_T                                       SDLK_t
#define KEYBOARD_U                                       SDLK_u
#define KEYBOARD_V                                       SDLK_v
#define KEYBOARD_W                                       SDLK_w
#define KEYBOARD_X                                       SDLK_x
#define KEYBOARD_Y                                       SDLK_y
#define KEYBOARD_Z                                       SDLK_z

#define KEYBOARD_CAPSLOCK                                SDLK_CAPSLOCK

#define KEYBOARD_F1                                      SDLK_F1
#define KEYBOARD_F2                                      SDLK_F2
#define KEYBOARD_F3                                      SDLK_F3
#define KEYBOARD_F4                                      SDLK_F4
#define KEYBOARD_F5                                      SDLK_F5
#define KEYBOARD_F6                                      SDLK_F6
#define KEYBOARD_F7                                      SDLK_F7
#define KEYBOARD_F8                                      SDLK_F8
#define KEYBOARD_F9                                      SDLK_F9
#define KEYBOARD_F10                                     SDLK_F10
#define KEYBOARD_F11                                     SDLK_F11
#define KEYBOARD_F12                                     SDLK_F12

#define KEYBOARD_PRINTSCREEN                             SDLK_PRINTSCREEN
#define KEYBOARD_SCROLLLOCK                              SDLK_SCROLLLOCK
#define KEYBOARD_PAUSE                                   SDLK_PAUSE
#define KEYBOARD_INSERT                                  SDLK_INSERT
#define KEYBOARD_HOME                                    SDLK_HOME
#define KEYBOARD_PAGEUP                                  SDLK_PAGEUP
#define KEYBOARD_DELETE                                  SDLK_DELETE
#define KEYBOARD_END                                     SDLK_END
#define KEYBOARD_PAGEDOWN                                SDLK_PAGEDOWN
#define KEYBOARD_RIGHT                                   SDLK_RIGHT
#define KEYBOARD_LEFT                                    SDLK_LEFT
#define KEYBOARD_DOWN                                    SDLK_DOWN
#define KEYBOARD_UP                                      SDLK_UP

#define KEYBOARD_NUMLOCKCLEAR                            SDLK_NUMLOCKCLEAR
#define KEYBOARD_KEYPAD_DIVIDE                           SDLK_KP_DIVIDE
#define KEYBOARD_KEYPAD_MULTIPLY                         SDLK_KP_MULTIPLY
#define KEYBOARD_KEYPAD_MINUS                            SDLK_KP_MINUS
#define KEYBOARD_KEYPAD_PLUS                             SDLK_KP_PLUS
#define KEYBOARD_KEYPAD_ENTER                            SDLK_KP_ENTER
#define KEYBOARD_KEYPAD_1                                SDLK_KP_1
#define KEYBOARD_KEYPAD_2                                SDLK_KP_2
#define KEYBOARD_KEYPAD_3                                SDLK_KP_3
#define KEYBOARD_KEYPAD_4                                SDLK_KP_4
#define KEYBOARD_KEYPAD_5                                SDLK_KP_5
#define KEYBOARD_KEYPAD_6                                SDLK_KP_6
#define KEYBOARD_KEYPAD_7                                SDLK_KP_7
#define KEYBOARD_KEYPAD_8                                SDLK_KP_8
#define KEYBOARD_KEYPAD_9                                SDLK_KP_9
#define KEYBOARD_KEYPAD_0                                SDLK_KP_0
#define KEYBOARD_KEYPAD_PERIOD                           SDLK_KP_PERIOD

#define KEYBOARD_APPLICATION                             SDLK_APPLICATION
#define KEYBOARD_POWER                                   SDLK_POWER
#define KEYBOARD_KEYPAD_EQUALS                           SDLK_KP_EQUALS
#define KEYBOARD_F13                                     SDLK_F13
#define KEYBOARD_F14                                     SDLK_F14
#define KEYBOARD_F15                                     SDLK_F15
#define KEYBOARD_F16                                     SDLK_F16
#define KEYBOARD_F17                                     SDLK_F17
#define KEYBOARD_F18                                     SDLK_F18
#define KEYBOARD_F19                                     SDLK_F19
#define KEYBOARD_F20                                     SDLK_F20
#define KEYBOARD_F21                                     SDLK_F21
#define KEYBOARD_F22                                     SDLK_F22
#define KEYBOARD_F23                                     SDLK_F23
#define KEYBOARD_F24                                     SDLK_F24
#define KEYBOARD_EXECUTE                                 SDLK_EXECUTE
#define KEYBOARD_HELP                                    SDLK_HELP
#define KEYBOARD_MENU                                    SDLK_MENU
#define KEYBOARD_SELECT                                  SDLK_SELECT
#define KEYBOARD_STOP                                    SDLK_STOP
#define KEYBOARD_AGAIN                                   SDLK_AGAIN
#define KEYBOARD_UNDO                                    SDLK_UNDO
#define KEYBOARD_CUT                                     SDLK_CUT
#define KEYBOARD_COPY                                    SDLK_COPY
#define KEYBOARD_PASTE                                   SDLK_PASTE
#define KEYBOARD_FIND                                    SDLK_FIND
#define KEYBOARD_MUTE                                    SDLK_MUTE
#define KEYBOARD_VOLUMEUP                                SDLK_VOLUMEUP
#define KEYBOARD_VOLUMEDOWN                              SDLK_VOLUMEDOWN
#define KEYBOARD_KEYPAD_COMMA                            SDLK_KP_COMMA
#define KEYBOARD_KEYPAD_EQUALSAS400                      SDLK_KP_EQUALSAS400


#define KEYBOARD_ALTERASE                                SDLK_ALTERASE
#define KEYBOARD_SYSREQ                                  SDLK_SYSREQ
#define KEYBOARD_CANCEL                                  SDLK_CANCEL
#define KEYBOARD_CLEAR                                   SDLK_CLEAR
#define KEYBOARD_PRIOR                                   SDLK_PRIOR
#define KEYBOARD_RETURN2                                 SDLK_RETURN2
#define KEYBOARD_SEPARATOR                               SDLK_SEPARATOR
#define KEYBOARD_OUT                                     SDLK_OUT
#define KEYBOARD_OPER                                    SDLK_OPER
#define KEYBOARD_CLEARAGAIN                              SDLK_CLEARAGAIN
#define KEYBOARD_CRSEL                                   SDLK_CRSEL
#define KEYBOARD_EXSEL                                   SDLK_EXSEL

#define KEYBOARD_KEYPAD_00                               SDLK_KP_00
#define KEYBOARD_KEYPAD_000                              SDLK_KP_000
#define KEYBOARD_THOUSANDSSEPARATOR                      SDLK_THOUSANDSSEPARATOR

#define KEYBOARD_DECIMALSEPARATOR                        SDLK_DECIMALSEPARATOR

#define KEYBOARD_CURRENCYUNIT                            SDLK_CURRENCYUNIT
#define KEYBOARD_CURRENCYSUBUNIT                         SDLK_CURRENCYSUBUNIT

#define KEYBOARD_KEYPAD_LEFTPAREN                        SDLK_KP_LEFTPAREN
#define KEYBOARD_KEYPAD_RIGHTPAREN                       SDLK_KP_RIGHTPAREN
#define KEYBOARD_KEYPAD_LEFTBRACE                        SDLK_KP_LEFTBRACE
#define KEYBOARD_KEYPAD_RIGHTBRACE                       SDLK_KP_RIGHTBRACE
#define KEYBOARD_KEYPAD_TAB                              SDLK_KP_TAB
#define KEYBOARD_KEYPAD_BACKSPACE                        SDLK_KP_BACKSPACE
#define KEYBOARD_KEYPAD_A                                SDLK_KP_A
#define KEYBOARD_KEYPAD_B                                SDLK_KP_B
#define KEYBOARD_KEYPAD_C                                SDLK_KP_C
#define KEYBOARD_KEYPAD_D                                SDLK_KP_D
#define KEYBOARD_KEYPAD_E                                SDLK_KP_E
#define KEYBOARD_KEYPAD_F                                SDLK_KP_F
#define KEYBOARD_KEYPAD_XOR                              SDLK_KP_XOR
#define KEYBOARD_KEYPAD_POWER                            SDLK_KP_POWER
#define KEYBOARD_KEYPAD_PERCENT                          SDLK_KP_PERCENT
#define KEYBOARD_KEYPAD_LESS                             SDLK_KP_LESS
#define KEYBOARD_KEYPAD_GREATER                          SDLK_KP_GREATER
#define KEYBOARD_KEYPAD_AMPERSAND                        SDLK_KP_AMPERSAND
#define KEYBOARD_KEYPAD_DBLAMPERSAND                     SDLK_KP_DBLAMPERSAND

#define KEYBOARD_KEYPAD_VERTICALBAR                      SDLK_KP_VERTICALBAR

#define KEYBOARD_KEYPAD_DBLVERTICALBAR                   SDLK_KP_DBLVERTICALBAR

#define KEYBOARD_KEYPAD_COLON                            SDLK_KP_COLON
#define KEYBOARD_KEYPAD_HASH                             SDLK_KP_HASH
#define KEYBOARD_KEYPAD_SPACE                            SDLK_KP_SPACE
#define KEYBOARD_KEYPAD_AT                               SDLK_KP_AT
#define KEYBOARD_KEYPAD_EXCLAM                           SDLK_KP_EXCLAM
#define KEYBOARD_KEYPAD_MEMSTORE                         SDLK_KP_MEMSTORE
#define KEYBOARD_KEYPAD_MEMRECALL                        SDLK_KP_MEMRECALL
#define KEYBOARD_KEYPAD_MEMCLEAR                         SDLK_KP_MEMCLEAR
#define KEYBOARD_KEYPAD_MEMADD                           SDLK_KP_MEMADD
#define KEYBOARD_KEYPAD_MEMSUBTRACT                      SDLK_KP_MEMSUBTRACT

#define KEYBOARD_KEYPAD_MEMMULTIPLY                      SDLK_KP_MEMMULTIPLY

#define KEYBOARD_KEYPAD_MEMDIVIDE                        SDLK_KP_MEMDIVIDE
#define KEYBOARD_KEYPAD_PLUSMINUS                        SDLK_KP_PLUSMINUS
#define KEYBOARD_KEYPAD_CLEAR                            SDLK_KP_CLEAR
#define KEYBOARD_KEYPAD_CLEARENTRY                       SDLK_KP_CLEARENTRY
#define KEYBOARD_KEYPAD_BINARY                           SDLK_KP_BINARY
#define KEYBOARD_KEYPAD_OCTAL                            SDLK_KP_OCTAL
#define KEYBOARD_KEYPAD_DECIMAL                          SDLK_KP_DECIMAL
#define KEYBOARD_KEYPAD_HEXADECIMAL                      SDLK_KP_HEXADECIMAL


#define KEYBOARD_LCTRL                                   SDLK_LCTRL
#define KEYBOARD_LSHIFT                                  SDLK_LSHIFT
#define KEYBOARD_LALT                                    SDLK_LALT
#define KEYBOARD_LGUI                                    SDLK_LGUI
#define KEYBOARD_RCTRL                                   SDLK_RCTRL
#define KEYBOARD_RSHIFT                                  SDLK_RSHIFT
#define KEYBOARD_RALT                                    SDLK_RALT
#define KEYBOARD_RGUI                                    SDLK_RGUI

#define KEYBOARD_MODE                                    SDLK_MODE

#define KEYBOARD_AUDIONEXT                               SDLK_AUDIONEXT
#define KEYBOARD_AUDIOPREV                               SDLK_AUDIOPREV
#define KEYBOARD_AUDIOSTOP                               SDLK_AUDIOSTOP
#define KEYBOARD_AUDIOPLAY                               SDLK_AUDIOPLAY
#define KEYBOARD_AUDIOMUTE                               SDLK_AUDIOMUTE
#define KEYBOARD_MEDIASELECT                             SDLK_MEDIASELECT
#define KEYBOARD_WWW                                     SDLK_WWW
#define KEYBOARD_MAIL                                    SDLK_MAIL
#define KEYBOARD_CALCULATOR                              SDLK_CALCULATOR
#define KEYBOARD_COMPUTER                                SDLK_COMPUTER
#define KEYBOARD_AC_SEARCH                               SDLK_AC_SEARCH
#define KEYBOARD_AC_HOME                                 SDLK_AC_HOME
#define KEYBOARD_AC_BACK                                 SDLK_AC_BACK
#define KEYBOARD_AC_FORWARD                              SDLK_AC_FORWARD
#define KEYBOARD_AC_STOP                                 SDLK_AC_STOP
#define KEYBOARD_AC_REFRESH                              SDLK_AC_REFRESH
#define KEYBOARD_AC_BOOKMARKS                            SDLK_AC_BOOKMARKS

#define KEYBOARD_BRIGHTNESSDOWN                          SDLK_BRIGHTNESSDOWN

#define KEYBOARD_BRIGHTNESSUP                            SDLK_BRIGHTNESSUP
#define KEYBOARD_DISPLAYSWITCH                           SDLK_DISPLAYSWITCH
#define KEYBOARD_KBDILLUMTOGGLE                          SDLK_KBDILLUMTOGGLE

#define KEYBOARD_KBDILLUMDOWN                            SDLK_KBDILLUMDOWN
#define KEYBOARD_KBDILLUMUP                              SDLK_KBDILLUMUP
#define KEYBOARD_EJECT                                   SDLK_EJECT
#define KEYBOARD_SLEEP                                   SDLK_SLEEP


#endif
