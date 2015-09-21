/*!
  \file xmms-helper.c

  \brief Just implements some additional controls that the xmms
  control interface API provides, but for some stupid reason xmms
  command line does not handle.

  gcc -o xmms-helper `xmms-config --cflags` xmms-helper.c  `xmms-config --libs`
*/

#include <stdio.h>
#include <xmms/xmmsctrl.h>

int main(int argc, char** argv) {
  int i;
  int volume, playback;
  int level;
  
  if (argc < 2) {
    printf ("Usage: %s -[v|p|P]\n", argv[0]);
    printf ("\n Options:\n"
	    " -v: volume\n"
	    " -p: play state\n"
	    " -P: pause state\n"
	    " -S [+|-]level: volume level. +|- implies relative\n"
	    " Only one option may be specified\n");
    return 1;
  }

  if (argv[1][0] == '-') {
    switch (argv[1][1]) {
    case 'v':
      volume = xmms_remote_get_main_volume(0);
      printf ("%d\n", volume);
      break;
    case 'p':
      playback = xmms_remote_is_playing(0);
      printf("%d\n", playback);
      break;
    case 'P':
      playback = xmms_remote_is_paused(0);
      printf("%d\n", playback);
      break;
    case 'S':
      if ((argv[2][0] == '+') || (argv[2][0] == '-')) {
	volume = xmms_remote_get_main_volume(0);
	volume += atoi(argv[2]);
      } else {
	volume = atoi(argv[2]);
      }
      xmms_remote_set_main_volume(0, volume);
      break;
    default:
      printf ("Unsupported option\n");
      return 1;
    }
  }

  
  return 0;
}
