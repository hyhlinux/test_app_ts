#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/inotify.h>
#include <linux/limits.h>
#include <sys/poll.h>
#include <linux/input.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include "getevent.h"

static struct pollfd *ufds;
static char **device_names;
static int nfds; enum {
	PRINT_DEVICE_ERRORS = 1U << 0,
			    PRINT_DEVICE = 1U << 1,
			    PRINT_DEVICE_NAME = 1U << 2,
			    PRINT_DEVICE_INFO = 1U << 3,
			    PRINT_VERSION = 1U << 4,
			    PRINT_POSSIBLE_EVENTS = 1U << 5,
			    PRINT_INPUT_PROPS = 1U << 6,
			    PRINT_HID_DESCRIPTOR = 1U << 7,
			    PRINT_ALL_INFO = (1U << 8) - 1,
			    PRINT_LABELS = 1U << 16,
};


/****************************add hyh*****************************************/
#ifndef EV_SYN
#define EV_SYN 0
#endif

char *events[EV_MAX + 1] = { 
	[0 ... EV_MAX] = NULL,
	[EV_SYN] = "Sync",            [EV_KEY] = "Key",
	[EV_REL] = "Relative",            [EV_ABS] = "Absolute",
	[EV_MSC] = "Misc",            [EV_LED] = "LED",
	[EV_SND] = "Sound",            [EV_REP] = "Repeat",
	[EV_FF] = "ForceFeedback",        [EV_PWR] = "Power",
	[EV_FF_STATUS] = "ForceFeedbackStatus",
};

char *keys[KEY_MAX + 1] = {
	[0 ... KEY_MAX] = NULL,
	[KEY_RESERVED] = "Reserved",        [KEY_ESC] = "Esc",
	[KEY_1] = "1",                [KEY_2] = "2",
	[KEY_3] = "3",                [KEY_4] = "4",
	[KEY_5] = "5",                [KEY_6] = "6",
	[KEY_7] = "7",                [KEY_8] = "8",
	[KEY_9] = "9",                [KEY_0] = "0",
	[KEY_MINUS] = "Minus",            [KEY_EQUAL] = "Equal",
	[KEY_BACKSPACE] = "Backspace",        [KEY_TAB] = "Tab",
	[KEY_Q] = "Q",                [KEY_W] = "W",
	[KEY_E] = "E",                [KEY_R] = "R",
	[KEY_T] = "T",                [KEY_Y] = "Y",
	[KEY_U] = "U",                [KEY_I] = "I",
	[KEY_O] = "O",                [KEY_P] = "P",
	[KEY_LEFTBRACE] = "LeftBrace",        [KEY_RIGHTBRACE] = "RightBrace",
	[KEY_ENTER] = "Enter",            [KEY_LEFTCTRL] = "LeftControl",
	[KEY_A] = "A",                [KEY_S] = "S",
	[KEY_D] = "D",                [KEY_F] = "F",
	[KEY_G] = "G",                [KEY_H] = "H",
	[KEY_J] = "J",                [KEY_K] = "K",
	[KEY_L] = "L",                [KEY_SEMICOLON] = "Semicolon",
	[KEY_APOSTROPHE] = "Apostrophe",    [KEY_GRAVE] = "Grave",
	[KEY_LEFTSHIFT] = "LeftShift",        [KEY_BACKSLASH] = "BackSlash",
	[KEY_Z] = "Z",                [KEY_X] = "X",
	[KEY_C] = "C",                [KEY_V] = "V",
	[KEY_B] = "B",                [KEY_N] = "N",
	[KEY_M] = "M",                [KEY_COMMA] = "Comma",
	[KEY_DOT] = "Dot",            [KEY_SLASH] = "Slash",
	[KEY_RIGHTSHIFT] = "RightShift",    [KEY_KPASTERISK] = "KPAsterisk",
	[KEY_LEFTALT] = "LeftAlt",        [KEY_SPACE] = "Space",
	[KEY_CAPSLOCK] = "CapsLock",        [KEY_F1] = "F1",
	[KEY_F2] = "F2",            [KEY_F3] = "F3",
	[KEY_F4] = "F4",            [KEY_F5] = "F5",
	[KEY_F6] = "F6",            [KEY_F7] = "F7",
	[KEY_F8] = "F8",            [KEY_F9] = "F9",
	[KEY_F10] = "F10",            [KEY_NUMLOCK] = "NumLock",
	[KEY_SCROLLLOCK] = "ScrollLock",    [KEY_KP7] = "KP7",
	[KEY_KP8] = "KP8",            [KEY_KP9] = "KP9",
	[KEY_KPMINUS] = "KPMinus",        [KEY_KP4] = "KP4",
	[KEY_KP5] = "KP5",            [KEY_KP6] = "KP6",
	[KEY_KPPLUS] = "KPPlus",        [KEY_KP1] = "KP1",
	[KEY_KP2] = "KP2",            [KEY_KP3] = "KP3",
	[KEY_KP0] = "KP0",            [KEY_KPDOT] = "KPDot",
	[KEY_ZENKAKUHANKAKU] = "Zenkaku/Hankaku", [KEY_102ND] = "102nd",
	[KEY_F11] = "F11",            [KEY_F12] = "F12",
	[KEY_RO] = "RO",            [KEY_KATAKANA] = "Katakana",
	[KEY_HIRAGANA] = "HIRAGANA",        [KEY_HENKAN] = "Henkan",
	[KEY_KATAKANAHIRAGANA] = "Katakana/Hiragana", [KEY_MUHENKAN] = "Muhenkan",
	[KEY_KPJPCOMMA] = "KPJpComma",        [KEY_KPENTER] = "KPEnter",
	[KEY_RIGHTCTRL] = "RightCtrl",        [KEY_KPSLASH] = "KPSlash",
	[KEY_SYSRQ] = "SysRq",            [KEY_RIGHTALT] = "RightAlt",
	[KEY_LINEFEED] = "LineFeed",        [KEY_HOME] = "Home",
	[KEY_UP] = "Up",            [KEY_PAGEUP] = "PageUp",
	[KEY_LEFT] = "Left",            [KEY_RIGHT] = "Right",
	[KEY_END] = "End",            [KEY_DOWN] = "Down",
	[KEY_PAGEDOWN] = "PageDown",        [KEY_INSERT] = "Insert",
	[KEY_DELETE] = "Delete",        [KEY_MACRO] = "Macro",
	[KEY_MUTE] = "Mute",            [KEY_VOLUMEDOWN] = "VolumeDown",
	[KEY_VOLUMEUP] = "VolumeUp",        [KEY_POWER] = "Power",
	[KEY_KPEQUAL] = "KPEqual",        [KEY_KPPLUSMINUS] = "KPPlusMinus",
	[KEY_PAUSE] = "Pause",            [KEY_KPCOMMA] = "KPComma",
	[KEY_HANGUEL] = "Hanguel",        [KEY_HANJA] = "Hanja",
	[KEY_YEN] = "Yen",            [KEY_LEFTMETA] = "LeftMeta",
	[KEY_RIGHTMETA] = "RightMeta",        [KEY_COMPOSE] = "Compose",
	[KEY_STOP] = "Stop",            [KEY_AGAIN] = "Again",
	[KEY_PROPS] = "Props",            [KEY_UNDO] = "Undo",
	[KEY_FRONT] = "Front",            [KEY_COPY] = "Copy",
	[KEY_OPEN] = "Open",            [KEY_PASTE] = "Paste",
	[KEY_FIND] = "Find",            [KEY_CUT] = "Cut",
	[KEY_HELP] = "Help",            [KEY_MENU] = "Menu",
	[KEY_CALC] = "Calc",            [KEY_SETUP] = "Setup",
	[KEY_SLEEP] = "Sleep",            [KEY_WAKEUP] = "WakeUp",
	[KEY_FILE] = "File",            [KEY_SENDFILE] = "SendFile",
	[KEY_DELETEFILE] = "DeleteFile",    [KEY_XFER] = "X-fer",
	[KEY_PROG1] = "Prog1",            [KEY_PROG2] = "Prog2",
	[KEY_WWW] = "WWW",            [KEY_MSDOS] = "MSDOS",
	[KEY_COFFEE] = "Coffee",        [KEY_DIRECTION] = "Direction",
	[KEY_CYCLEWINDOWS] = "CycleWindows",    [KEY_MAIL] = "Mail",
	[KEY_BOOKMARKS] = "Bookmarks",        [KEY_COMPUTER] = "Computer",
	[KEY_BACK] = "Back",            [KEY_FORWARD] = "Forward",
	[KEY_CLOSECD] = "CloseCD",        [KEY_EJECTCD] = "EjectCD",
	[KEY_EJECTCLOSECD] = "EjectCloseCD",    [KEY_NEXTSONG] = "NextSong",
	[KEY_PLAYPAUSE] = "PlayPause",        [KEY_PREVIOUSSONG] = "PreviousSong",
	[KEY_STOPCD] = "StopCD",        [KEY_RECORD] = "Record",
	[KEY_REWIND] = "Rewind",        [KEY_PHONE] = "Phone",
	[KEY_ISO] = "ISOKey",            [KEY_CONFIG] = "Config",
	[KEY_HOMEPAGE] = "HomePage",        [KEY_REFRESH] = "Refresh",
	[KEY_EXIT] = "Exit",            [KEY_MOVE] = "Move",
	[KEY_EDIT] = "Edit",            [KEY_SCROLLUP] = "ScrollUp",
	[KEY_SCROLLDOWN] = "ScrollDown",    [KEY_KPLEFTPAREN] = "KPLeftParenthesis",
	[KEY_KPRIGHTPAREN] = "KPRightParenthesis", [KEY_F13] = "F13",
	[KEY_F14] = "F14",            [KEY_F15] = "F15",
	[KEY_F16] = "F16",            [KEY_F17] = "F17",
	[KEY_F18] = "F18",            [KEY_F19] = "F19",
	[KEY_F20] = "F20",            [KEY_F21] = "F21",
	[KEY_F22] = "F22",            [KEY_F23] = "F23",
	[KEY_F24] = "F24",            [KEY_PLAYCD] = "PlayCD",
	[KEY_PAUSECD] = "PauseCD",        [KEY_PROG3] = "Prog3",
	[KEY_PROG4] = "Prog4",            [KEY_SUSPEND] = "Suspend",
	[KEY_CLOSE] = "Close",            [KEY_PLAY] = "Play",
	[KEY_FASTFORWARD] = "Fast Forward",    [KEY_BASSBOOST] = "Bass Boost",
	[KEY_PRINT] = "Print",            [KEY_HP] = "HP",
	[KEY_CAMERA] = "Camera",        [KEY_SOUND] = "Sound",
	[KEY_QUESTION] = "Question",        [KEY_EMAIL] = "Email",
	[KEY_CHAT] = "Chat",            [KEY_SEARCH] = "Search",
	[KEY_CONNECT] = "Connect",        [KEY_FINANCE] = "Finance",
	[KEY_SPORT] = "Sport",            [KEY_SHOP] = "Shop",
	[KEY_ALTERASE] = "Alternate Erase",    [KEY_CANCEL] = "Cancel",
	[KEY_BRIGHTNESSDOWN] = "Brightness down", [KEY_BRIGHTNESSUP] = "Brightness up",
	[KEY_MEDIA] = "Media",            [KEY_UNKNOWN] = "Unknown",
	[BTN_0] = "Btn0",            [BTN_1] = "Btn1",
	[BTN_2] = "Btn2",            [BTN_3] = "Btn3",
	[BTN_4] = "Btn4",            [BTN_5] = "Btn5",
	[BTN_6] = "Btn6",            [BTN_7] = "Btn7",
	[BTN_8] = "Btn8",            [BTN_9] = "Btn9",
	[BTN_LEFT] = "LeftBtn",            [BTN_RIGHT] = "RightBtn",
	[BTN_MIDDLE] = "MiddleBtn",        [BTN_SIDE] = "SideBtn",
	[BTN_EXTRA] = "ExtraBtn",        [BTN_FORWARD] = "ForwardBtn",
	[BTN_BACK] = "BackBtn",            [BTN_TASK] = "TaskBtn",
	[BTN_TRIGGER] = "Trigger",        [BTN_THUMB] = "ThumbBtn",
	[BTN_THUMB2] = "ThumbBtn2",        [BTN_TOP] = "TopBtn",
	[BTN_TOP2] = "TopBtn2",            [BTN_PINKIE] = "PinkieBtn",
	[BTN_BASE] = "BaseBtn",            [BTN_BASE2] = "BaseBtn2",
	[BTN_BASE3] = "BaseBtn3",        [BTN_BASE4] = "BaseBtn4",
	[BTN_BASE5] = "BaseBtn5",        [BTN_BASE6] = "BaseBtn6",
	[BTN_DEAD] = "BtnDead",            [BTN_A] = "BtnA",
	[BTN_B] = "BtnB",            [BTN_C] = "BtnC",
	[BTN_X] = "BtnX",            [BTN_Y] = "BtnY",
	[BTN_Z] = "BtnZ",            [BTN_TL] = "BtnTL",
	[BTN_TR] = "BtnTR",            [BTN_TL2] = "BtnTL2",
	[BTN_TR2] = "BtnTR2",            [BTN_SELECT] = "BtnSelect",
	[BTN_START] = "BtnStart",        [BTN_MODE] = "BtnMode",
	[BTN_THUMBL] = "BtnThumbL",        [BTN_THUMBR] = "BtnThumbR",
	[BTN_TOOL_PEN] = "ToolPen",        [BTN_TOOL_RUBBER] = "ToolRubber",
	[BTN_TOOL_BRUSH] = "ToolBrush",        [BTN_TOOL_PENCIL] = "ToolPencil",
	[BTN_TOOL_AIRBRUSH] = "ToolAirbrush",    [BTN_TOOL_FINGER] = "ToolFinger",
	[BTN_TOOL_MOUSE] = "ToolMouse",        [BTN_TOOL_LENS] = "ToolLens",
	[BTN_TOUCH] = "Touch",            [BTN_STYLUS] = "Stylus",
	[BTN_STYLUS2] = "Stylus2",        [BTN_TOOL_DOUBLETAP] = "Tool Doubletap",
	[BTN_TOOL_TRIPLETAP] = "Tool Tripletap", [BTN_GEAR_DOWN] = "WheelBtn",
	[BTN_GEAR_UP] = "Gear up",        [KEY_OK] = "Ok",
	[KEY_SELECT] = "Select",        [KEY_GOTO] = "Goto",
	[KEY_CLEAR] = "Clear",            [KEY_POWER2] = "Power2",
	[KEY_OPTION] = "Option",        [KEY_INFO] = "Info",
	[KEY_TIME] = "Time",            [KEY_VENDOR] = "Vendor",
	[KEY_ARCHIVE] = "Archive",        [KEY_PROGRAM] = "Program",
	[KEY_CHANNEL] = "Channel",        [KEY_FAVORITES] = "Favorites",
	[KEY_EPG] = "EPG",            [KEY_PVR] = "PVR",
	[KEY_MHP] = "MHP",            [KEY_LANGUAGE] = "Language",
	[KEY_TITLE] = "Title",            [KEY_SUBTITLE] = "Subtitle",
	[KEY_ANGLE] = "Angle",            [KEY_ZOOM] = "Zoom",
	[KEY_MODE] = "Mode",            [KEY_KEYBOARD] = "Keyboard",
	[KEY_SCREEN] = "Screen",        [KEY_PC] = "PC",
	[KEY_TV] = "TV",            [KEY_TV2] = "TV2",
	[KEY_VCR] = "VCR",            [KEY_VCR2] = "VCR2",
	[KEY_SAT] = "Sat",            [KEY_SAT2] = "Sat2",
	[KEY_CD] = "CD",            [KEY_TAPE] = "Tape",
	[KEY_RADIO] = "Radio",            [KEY_TUNER] = "Tuner",
	[KEY_PLAYER] = "Player",        [KEY_TEXT] = "Text",
	[KEY_DVD] = "DVD",            [KEY_AUX] = "Aux",
	[KEY_MP3] = "MP3",            [KEY_AUDIO] = "Audio",
	[KEY_VIDEO] = "Video",            [KEY_DIRECTORY] = "Directory",
	[KEY_LIST] = "List",            [KEY_MEMO] = "Memo",
	[KEY_CALENDAR] = "Calendar",        [KEY_RED] = "Red",
	[KEY_GREEN] = "Green",            [KEY_YELLOW] = "Yellow",
	[KEY_BLUE] = "Blue",            [KEY_CHANNELUP] = "ChannelUp",
	[KEY_CHANNELDOWN] = "ChannelDown",    [KEY_FIRST] = "First",
	[KEY_LAST] = "Last",            [KEY_AB] = "AB",
	[KEY_NEXT] = "Next",            [KEY_RESTART] = "Restart",
	[KEY_SLOW] = "Slow",            [KEY_SHUFFLE] = "Shuffle",
	[KEY_BREAK] = "Break",            [KEY_PREVIOUS] = "Previous",
	[KEY_DIGITS] = "Digits",        [KEY_TEEN] = "TEEN",
	[KEY_TWEN] = "TWEN",            [KEY_DEL_EOL] = "Delete EOL",
	[KEY_DEL_EOS] = "Delete EOS",        [KEY_INS_LINE] = "Insert line",
	[KEY_DEL_LINE] = "Delete line",
};

char *absval[5] = { "Value", "Min ", "Max ", "Fuzz ", "Flat " };

char *relatives[REL_MAX + 1] = {
	[0 ... REL_MAX] = NULL,
	[REL_X] = "X",            [REL_Y] = "Y",
	[REL_Z] = "Z",            [REL_HWHEEL] = "HWheel",
	[REL_DIAL] = "Dial",        [REL_WHEEL] = "Wheel",
	[REL_MISC] = "Misc",    
};

char *absolutes[ABS_MAX + 1] = {
	[0 ... ABS_MAX] = NULL,
	[ABS_X] = "X",            [ABS_Y] = "Y",
	[ABS_Z] = "Z",            [ABS_RX] = "Rx",
	[ABS_RY] = "Ry",        [ABS_RZ] = "Rz",
	[ABS_THROTTLE] = "Throttle",    [ABS_RUDDER] = "Rudder",
	[ABS_WHEEL] = "Wheel",        [ABS_GAS] = "Gas",
	[ABS_BRAKE] = "Brake",        [ABS_HAT0X] = "Hat0X",
	[ABS_HAT0Y] = "Hat0Y",        [ABS_HAT1X] = "Hat1X",
	[ABS_HAT1Y] = "Hat1Y",        [ABS_HAT2X] = "Hat2X",
	[ABS_HAT2Y] = "Hat2Y",        [ABS_HAT3X] = "Hat3X",
	[ABS_HAT3Y] = "Hat 3Y",        [ABS_PRESSURE] = "Pressure",
	[ABS_DISTANCE] = "Distance",    [ABS_TILT_X] = "XTilt",
	[ABS_TILT_Y] = "YTilt",        [ABS_TOOL_WIDTH] = "Tool Width",
	[ABS_VOLUME] = "Volume",    [ABS_MISC] = "Misc",

	//add hyh for touch point
	[ABS_MT_SLOT]="MT solt"/* MT slot being modified */,
	[ABS_MT_TOUCH_MAJOR]="Major axis of touching ellipse",
	[ABS_MT_TOUCH_MINOR]="Minor axis (omit if circular)",
	[ABS_MT_WIDTH_MAJOR]="Major axis of approaching ellipse" ,
	[ABS_MT_WIDTH_MINOR]="Minor axis (omit if circular) ",
	[ABS_MT_ORIENTATION]="Ellipse orientation ",
	[ABS_MT_POSITION_X] ="Center X touch position" , 
	[ABS_MT_POSITION_Y] ="Center Y touch position" ,
	[ABS_MT_TOOL_TYPE]  ="Type of touching device" ,
	[ABS_MT_BLOB_ID]    ="Group a set of packets as a blob ",
	[ABS_MT_TRACKING_ID]="Unique ID of initiated contact   ",
	[ABS_MT_PRESSURE]   ="Pressure on contact area ",
	[ABS_MT_DISTANCE]   ="Contact hover distance   ",
//	[ABS_MT_TOOL_X]     ="Center X tool position   ",
//	[ABS_MT_TOOL_Y]	    ="Center Y tool position   ",

};

char *misc[MSC_MAX + 1] = {
	[ 0 ... MSC_MAX] = NULL,
	[MSC_SERIAL] = "Serial",    [MSC_PULSELED] = "Pulseled",
	[MSC_GESTURE] = "Gesture",    [MSC_RAW] = "RawData",
	[MSC_SCAN] = "ScanCode",
};

char *leds[LED_MAX + 1] = {
	[0 ... LED_MAX] = NULL,
	[LED_NUML] = "NumLock",        [LED_CAPSL] = "CapsLock",
	[LED_SCROLLL] = "ScrollLock",    [LED_COMPOSE] = "Compose",
	[LED_KANA] = "Kana",        [LED_SLEEP] = "Sleep",
	[LED_SUSPEND] = "Suspend",    [LED_MUTE] = "Mute",
	[LED_MISC] = "Misc",
};

char *repeats[REP_MAX + 1] = {
	[0 ... REP_MAX] = NULL,
	[REP_DELAY] = "Delay",        [REP_PERIOD] = "Period"
};

char *sounds[SND_MAX + 1] = {
	[0 ... SND_MAX] = NULL,
	[SND_CLICK] = "Click",        [SND_BELL] = "Bell",
	[SND_TONE] = "Tone"
};


char **names[EV_MAX + 1] = {
	[0 ... EV_MAX] = NULL,
	[EV_SYN] = events,            [EV_KEY] = keys,
	[EV_REL] = relatives,            [EV_ABS] = absolutes,
	[EV_MSC] = misc,            [EV_LED] = leds,
	[EV_SND] = sounds,            [EV_REP] = repeats,
};

#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
#define OFF(x) ((x)%BITS_PER_LONG)
#define BIT(x) (1UL<<OFF(x))
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array)    ((array[LONG(bit)] >> OFF(bit)) & 1)

/****************************add hyh*****************************************/

static const char *get_label(const struct label *labels, int value)
{
	while(labels->name && value != labels->value) {
		labels++;
	}
	return labels->name;
}

static int print_input_props(int fd)
{
	uint8_t bits[INPUT_PROP_CNT / 8];
	int i, j;
	int res;
	int count;
	const char *bit_label;

	printf(" input props:\n");
	res = ioctl(fd, EVIOCGPROP(sizeof(bits)), bits);
	if(res < 0) {
		printf(" <not available\n");
		return 1;
	}
	count = 0;
	for(i = 0; i < res; i++) {
		for(j = 0; j < 8; j++) {
			if (bits[i] & 1 << j) {
				bit_label = get_label(input_prop_labels, i * 8 + j);
				if(bit_label)
					printf(" %s\n", bit_label);
				else
					printf(" %04x\n", i * 8 + j);
				count++;
			}
		}
	}
	if (!count)
		printf(" <none>\n");
	return 0;
}

static int print_possible_events(int fd, int print_flags)
{
	uint8_t *bits = NULL;
	ssize_t bits_size = 0;
	const char* label;
	int i, j, k;
	int res, res2;
	struct label* bit_labels;
	const char *bit_label;

	printf(" events:\n");
	for(i = EV_KEY; i <= EV_MAX; i++) { // skip EV_SYN since we cannot query its available codes
		int count = 0;
		while(1) {
			res = ioctl(fd, EVIOCGBIT(i, bits_size), bits);
			if(res < bits_size)
				break;
			bits_size = res + 16;
			bits = realloc(bits, bits_size * 2);
			if(bits == NULL) {
				fprintf(stderr, "failed to allocate buffer of size %d\n", (int)bits_size);
				return 1;
			}
		}
		res2 = 0;
		switch(i) {
			case EV_KEY:
				res2 = ioctl(fd, EVIOCGKEY(res), bits + bits_size);
				label = "KEY";
				bit_labels = key_labels;
				break;
			case EV_REL:
				label = "REL";
				bit_labels = rel_labels;
				break;
			case EV_ABS:
				label = "ABS";
				bit_labels = abs_labels;
				break;
			case EV_MSC:
				label = "MSC";
				bit_labels = msc_labels;
				break;
			case EV_LED:
				res2 = ioctl(fd, EVIOCGLED(res), bits + bits_size);
				label = "LED";
				bit_labels = led_labels;
				break;
			case EV_SND:
				res2 = ioctl(fd, EVIOCGSND(res), bits + bits_size);
				label = "SND";
				bit_labels = snd_labels;
				break;
			case EV_SW:
				res2 = ioctl(fd, EVIOCGSW(bits_size), bits + bits_size);
				label = "SW ";
				bit_labels = sw_labels;
				break;
			case EV_REP:
				label = "REP";
				bit_labels = rep_labels;
				break;
			case EV_FF:
				label = "FF ";
				bit_labels = ff_labels;
				break;
			case EV_PWR:
				label = "PWR";
				bit_labels = NULL;
				break;
			case EV_FF_STATUS:
				label = "FFS";
				bit_labels = ff_status_labels;
				break;
			default:
				res2 = 0;
				label = "???";
				bit_labels = NULL;
		}
		for(j = 0; j < res; j++) {
			for(k = 0; k < 8; k++)
				if(bits[j] & 1 << k) {
					char down;
					if(j < res2 && (bits[j + bits_size] & 1 << k))
						down = '*';
					else
						down = ' ';
					if(count == 0)
						printf(" %s (%04x):", label, i);
					else if((count & (print_flags & PRINT_LABELS ? 0x3 : 0x7)) == 0 || i == EV_ABS)
						printf("\n ");
					if(bit_labels && (print_flags & PRINT_LABELS)) {
						bit_label = get_label(bit_labels, j * 8 + k);
						if(bit_label)
							printf(" %.20s%c%*s", bit_label, down, (int) (20 - strlen(bit_label)), "");
						else
							printf(" %04x%c ", j * 8 + k, down);
					} else {
						printf(" %04x%c", j * 8 + k, down);
					}
					if(i == EV_ABS) {
						struct input_absinfo abs;
						if(ioctl(fd, EVIOCGABS(j * 8 + k), &abs) == 0) {
							printf(" : value %d, min %d, max %d, fuzz %d, flat %d, resolution %d",
									abs.value, abs.minimum, abs.maximum, abs.fuzz, abs.flat,
									abs.resolution);
						}
					}
					count++;
				}
		}
		if(count)
			printf("\n");
	}
	free(bits);
	return 0;
}

static void print_event(int type, int code, int value, int print_flags)
{
	const char *type_label, *code_label, *value_label;

	if (print_flags & PRINT_LABELS) {
		type_label = get_label(ev_labels, type);
		code_label = NULL;
		value_label = NULL;

		switch(type) {
			case EV_SYN:
				code_label = get_label(syn_labels, code);
				break;
			case EV_KEY:
				code_label = get_label(key_labels, code);
				value_label = get_label(key_value_labels, value);
				break;
			case EV_REL:
				code_label = get_label(rel_labels, code);
				break;
			case EV_ABS:
				code_label = get_label(abs_labels, code);
				switch(code) {
					case ABS_MT_TOOL_TYPE:
						value_label = get_label(mt_tool_labels, value);
				}
				break;
			case EV_MSC:
				code_label = get_label(msc_labels, code);
				break;
			case EV_LED:
				code_label = get_label(led_labels, code);
				break;
			case EV_SND:
				code_label = get_label(snd_labels, code);
				break;
			case EV_SW:
				code_label = get_label(sw_labels, code);
				break;
			case EV_REP:
				code_label = get_label(rep_labels, code);
				break;
			case EV_FF:
				code_label = get_label(ff_labels, code);
				break;
			case EV_FF_STATUS:
				code_label = get_label(ff_status_labels, code);
				break;
		}

		if (type_label)
			printf("%-12.12s", type_label);
		else
			//printf("%04x ", type);
			printf("%4d ", type);

		if (code_label)
			printf(" %-20.20s", code_label);
		else
		//	printf(" %04x ", code);
			printf(" %4d ", code);
		if (value_label)
			printf(" %-20.20s", value_label);
		else
			//printf(" %08x ", value);
			printf(" %4d   ", value);

	} else {
		//printf("xxx%04x %04x %08x", type, code, value);
		//printf("hyh:type %d code %d value %d", type, code, value);
		printf("hyh:type %d (%s) code %d (%s)value %d\n", type, events[type] ? events[type] : "?",\
				code, names[type] ? (names[type][code] ? names[type][code] : "?") : "?",
				value);
	}
}

static void print_hid_descriptor(int bus, int vendor, int product)
{
	const char *dirname = "/sys/kernel/debug/hid";
	char prefix[16];
	DIR *dir;
	struct dirent *de;
	char filename[PATH_MAX];
	FILE *file;
	char line[2048];

	snprintf(prefix, sizeof(prefix), "%04X:%04X:%04X.", bus, vendor, product);

	dir = opendir(dirname);
	if(dir == NULL)
		return;
	while((de = readdir(dir))) {
		if (strstr(de->d_name, prefix) == de->d_name) {
			snprintf(filename, sizeof(filename), "%s/%s/rdesc", dirname, de->d_name);

			file = fopen(filename, "r");
			if (file) {
				printf(" HID descriptor: %s\n\n", de->d_name);
				while (fgets(line, sizeof(line), file)) {
					fputs(" ", stdout);
					fputs(line, stdout);
				}
				fclose(file);
				puts("");
			}
		}
	}
	closedir(dir);
}

static int open_device(const char *device, int print_flags)
{
	int version;
	int fd;
	int clkid = CLOCK_MONOTONIC;
	struct pollfd *new_ufds;
	char **new_device_names;
	char name[80];
	char location[80];
	char idstr[80];
	struct input_id id;

	fd = open(device, O_RDWR);
	if(fd < 0) {
		if(print_flags & PRINT_DEVICE_ERRORS)
			fprintf(stderr, "could not open %s, %s\n", device, strerror(errno));
		return -1;
	}

	if(ioctl(fd, EVIOCGVERSION, &version)) {
		if(print_flags & PRINT_DEVICE_ERRORS)
			fprintf(stderr, "could not get driver version for %s, %s\n", device, strerror(errno));
		return -1;
	}
	if(ioctl(fd, EVIOCGID, &id)) {
		if(print_flags & PRINT_DEVICE_ERRORS)
			fprintf(stderr, "could not get driver id for %s, %s\n", device, strerror(errno));
		return -1;
	}
	name[sizeof(name) - 1] = '\0';
	location[sizeof(location) - 1] = '\0';
	idstr[sizeof(idstr) - 1] = '\0';
	if(ioctl(fd, EVIOCGNAME(sizeof(name) - 1), &name) < 1) {
		//fprintf(stderr, "could not get device name for %s, %s\n", device, strerror(errno));
		name[0] = '\0';
	}
	if(ioctl(fd, EVIOCGPHYS(sizeof(location) - 1), &location) < 1) {
		//fprintf(stderr, "could not get location for %s, %s\n", device, strerror(errno));
		location[0] = '\0';
	}
	if(ioctl(fd, EVIOCGUNIQ(sizeof(idstr) - 1), &idstr) < 1) {
		//fprintf(stderr, "could not get idstring for %s, %s\n", device, strerror(errno));
		idstr[0] = '\0';
	}

#if  0
	if (ioctl(fd, EVIOCSCLOCKID, &clkid) != 0) {
		fprintf(stderr, "Can't enable monotonic clock reporting: %s\n", strerror(errno));
		// a non-fatal error
	}
#endif

	new_ufds = realloc(ufds, sizeof(ufds[0]) * (nfds + 1));
	if(new_ufds == NULL) {
		fprintf(stderr, "out of memory\n");
		return -1;
	}
	ufds = new_ufds;
	new_device_names = realloc(device_names, sizeof(device_names[0]) * (nfds + 1));
	if(new_device_names == NULL) {
		fprintf(stderr, "out of memory\n");
		return -1;
	}
	device_names = new_device_names;

	if(print_flags & PRINT_DEVICE)
		printf("add device %d: %s\n", nfds, device);
	if(print_flags & PRINT_DEVICE_INFO)
		printf(" bus: %04x\n"
				" vendor %04x\n"
				" product %04x\n"
				" version %04x\n",
				id.bustype, id.vendor, id.product, id.version);
	if(print_flags & PRINT_DEVICE_NAME)
		printf(" name: \"%s\"\n", name);
	if(print_flags & PRINT_DEVICE_INFO)
		printf(" location: \"%s\"\n"
				" id: \"%s\"\n", location, idstr);
	if(print_flags & PRINT_VERSION)
		printf(" version: %d.%d.%d\n",
				version >> 16, (version >> 8) & 0xff, version & 0xff);

	if(print_flags & PRINT_POSSIBLE_EVENTS) {
		print_possible_events(fd, print_flags);
	}

	if(print_flags & PRINT_INPUT_PROPS) {
		print_input_props(fd);
	}
	if(print_flags & PRINT_HID_DESCRIPTOR) {
		print_hid_descriptor(id.bustype, id.vendor, id.product);
	}

	ufds[nfds].fd = fd;
	ufds[nfds].events = POLLIN;
	device_names[nfds] = strdup(device);
	nfds++;

	return 0;
}

int close_device(const char *device, int print_flags)
{
	int i;
	for(i = 1; i < nfds; i++) {
		if(strcmp(device_names[i], device) == 0) {
			int count = nfds - i - 1;
			if(print_flags & PRINT_DEVICE)
				printf("remove device %d: %s\n", i, device);
			free(device_names[i]);
			memmove(device_names + i, device_names + i + 1, sizeof(device_names[0]) * count);
			memmove(ufds + i, ufds + i + 1, sizeof(ufds[0]) * count);
			nfds--;
			return 0;
		}
	}
	if(print_flags & PRINT_DEVICE_ERRORS)
		fprintf(stderr, "remote device: %s not found\n", device);
	return -1;
}

static int read_notify(const char *dirname, int nfd, int print_flags)
{
	int res;
	char devname[PATH_MAX];
	char *filename;
	char event_buf[512];
	int event_size;
	int event_pos = 0;
	struct inotify_event *event;

	res = read(nfd, event_buf, sizeof(event_buf));
	if(res < (int)sizeof(*event)) {
		if(errno == EINTR)
			return 0;
		fprintf(stderr, "could not get event, %s\n", strerror(errno));
		return 1;
	}
	//printf("got %d bytes of event information\n", res);

	strcpy(devname, dirname);
	filename = devname + strlen(devname);
	*filename++ = '/';

	while(res >= (int)sizeof(*event)) {
		event = (struct inotify_event *)(event_buf + event_pos);
		//printf("%d: %08x \"%s\"\n", event->wd, event->mask, event->len ? event->name : "");
		if(event->len) {
			strcpy(filename, event->name);
			if(event->mask & IN_CREATE) {
				open_device(devname, print_flags);
			}
			else {
				close_device(devname, print_flags);
			}
		}
		event_size = sizeof(*event) + event->len;
		res -= event_size;
		event_pos += event_size;
	}
	return 0;
}

static int scan_dir(const char *dirname, int print_flags)
{
	char devname[PATH_MAX];
	char *filename;
	DIR *dir;
	struct dirent *de;
	dir = opendir(dirname);
	if(dir == NULL)
		return -1;
	strcpy(devname, dirname);
	filename = devname + strlen(devname);
	*filename++ = '/';
	while((de = readdir(dir))) {
		if(de->d_name[0] == '.' &&
				(de->d_name[1] == '\0' ||
				 (de->d_name[1] == '.' && de->d_name[2] == '\0')))
			continue;
		strcpy(filename, de->d_name);
		open_device(devname, print_flags);
	}
	closedir(dir);
	return 0;
}

static void usage(char *name)
{
	fprintf(stderr, "Usage: %s [-t] [-n] [-s switchmask] [-S] [-v [mask]] [-d] [-p] [-i] [-l] [-q] [-c count] [-r] [device]\n", name);
	fprintf(stderr, " -t: show time stamps\n");
	fprintf(stderr, " -n: don't print newlines\n");
	fprintf(stderr, " -s: print switch states for given bits\n");
	fprintf(stderr, " -S: print all switch states\n");
	fprintf(stderr, " -v: verbosity mask (errs=1, dev=2, name=4, info=8, vers=16, pos. events=32, props=64)\n");
	fprintf(stderr, " -d: show HID descriptor, if available\n");
	fprintf(stderr, " -p: show possible events (errs, dev, name, pos. events)\n");
	fprintf(stderr, " -i: show all device info and possible events\n");
	fprintf(stderr, " -l: label event types and names in plain text\n");
	fprintf(stderr, " -q: quiet (clear verbosity mask)\n");
	fprintf(stderr, " -c: print given number of events then exit\n");
	fprintf(stderr, " -r: print rate events are received\n");
}

int main(int argc, char *argv[])
{
	int c;
	int i;
	int res;
	int get_time = 0;
	int print_device = 0;
	char *newline = "\n";
	uint16_t get_switch = 0;
	struct input_event event;
	int print_flags = 0;
	int print_flags_set = 0;
	int dont_block = -1;
	int event_count = 0;
	int sync_rate = 0;
	int64_t last_sync_time = 0;
	const char *device = NULL;
	const char *device_path = "/dev/input";

	opterr = 0;
	do {
		c = getopt(argc, argv, "tns:Sv::dpilqc:rh");
		if (c == EOF)
			break;
		switch (c) {
			case 't':
				get_time = 1;
				break;
			case 'n':
				newline = "";
				break;
			case 's':
				get_switch = strtoul(optarg, NULL, 0);
				if(dont_block == -1)
					dont_block = 1;
				break;
			case 'S':
				get_switch = ~0;
				if(dont_block == -1)
					dont_block = 1;
				break;
			case 'v':
				if(optarg)
					print_flags |= strtoul(optarg, NULL, 0);
				else
					print_flags |= PRINT_DEVICE | PRINT_DEVICE_NAME | PRINT_DEVICE_INFO | PRINT_VERSION;
				print_flags_set = 1;
				break;
			case 'd':
				print_flags |= PRINT_HID_DESCRIPTOR;
				break;
			case 'p':
				print_flags |= PRINT_DEVICE_ERRORS | PRINT_DEVICE
					| PRINT_DEVICE_NAME | PRINT_POSSIBLE_EVENTS | PRINT_INPUT_PROPS;
				print_flags_set = 1;
				if(dont_block == -1)
					dont_block = 1;
				break;
			case 'i':
				print_flags |= PRINT_ALL_INFO;
				print_flags_set = 1;
				if(dont_block == -1)
					dont_block = 1;
				break;
			case 'l':
				print_flags |= PRINT_LABELS;
				break;
			case 'q':
				print_flags_set = 1;
				break;
			case 'c':
				event_count = atoi(optarg);
				dont_block = 0;
				break;
			case 'r':
				sync_rate = 1;
				break;
			case '?':
				fprintf(stderr, "%s: invalid option -%c\n",
						argv[0], optopt);
			case 'h':
				usage(argv[0]);
				exit(1);
		}
	} while (1);
	if(dont_block == -1)
		dont_block = 0;

	if (optind + 1 == argc) {
		device = argv[optind];
		optind++;
	}
	if (optind != argc) {
		usage(argv[0]);
		exit(1);
	}
	nfds = 1;
	ufds = calloc(1, sizeof(ufds[0]));
	ufds[0].fd = inotify_init();
	ufds[0].events = POLLIN;

	if(device) {
		if(!print_flags_set)
			print_flags |= PRINT_DEVICE_ERRORS;
		res = open_device(device, print_flags);
		if(res < 0) {
			return 1;
		}
	} else {
		if(!print_flags_set)
			print_flags |= PRINT_DEVICE_ERRORS | PRINT_DEVICE | PRINT_DEVICE_NAME;
		print_device = 1;
		res = inotify_add_watch(ufds[0].fd, device_path, IN_DELETE | IN_CREATE);
		if(res < 0) {
			fprintf(stderr, "could not add watch for %s, %s\n", device_path, strerror(errno));
			return 1;
		}
		res = scan_dir(device_path, print_flags);
		if(res < 0) {
			fprintf(stderr, "scan dir failed for %s\n", device_path);
			return 1;
		}
	}

	if(get_switch) {
		for(i = 1; i < nfds; i++) {
			uint16_t sw;
			res = ioctl(ufds[i].fd, EVIOCGSW(1), &sw);
			if(res < 0) {
				fprintf(stderr, "could not get switch state, %s\n", strerror(errno));
				return 1;
			}
			sw &= get_switch;
			printf("%04x%s", sw, newline);
		}
	}

	if(dont_block)
		return 0;

	while(1) {
		//int pollres =
		poll(ufds, nfds, -1);
		//printf("poll %d, returned %d\n", nfds, pollres);
		if(ufds[0].revents & POLLIN) {
			read_notify(device_path, ufds[0].fd, print_flags);
		}
		for(i = 1; i < nfds; i++) {
			if(ufds[i].revents) {
				if(ufds[i].revents & POLLIN) {
					res = read(ufds[i].fd, &event, sizeof(event));
					if(res < (int)sizeof(event)) {
						fprintf(stderr, "could not get event\n");
						return 1;
					}
					if(get_time) {
						printf("[%8ld.%06ld] ", event.time.tv_sec, event.time.tv_usec);
					}
					if(print_device)
						printf("%s: ", device_names[i]);
					print_event(event.type, event.code, event.value, print_flags);
					if(sync_rate && event.type == 0 && event.code == 0) {
						int64_t now = event.time.tv_sec * 1000000LL + event.time.tv_usec;
						if(last_sync_time)
							printf(" rate %lld", 1000000LL / (now - last_sync_time));
						last_sync_time = now;
					}
					printf("%s", newline);
					if(event_count && --event_count == 0)
						return 0;
				}
			}
		}
	}

	return 0;
}


