/* MKHELP V2.0.1  - Dump an ascii text to a C string.
 * By Jean-Marc Jacquet <littleigloo@chez.com> 
 * Copyright (C) 1998 Little Igloo Org  http://www.chez.com/littleigloo
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define VERSION "MKHELP V2.0.1 (c) 1998 Little Igloo Org"

static char const rcsid[] =
    "$Id$";


int
main (int argc, char *argv[])
{
  FILE *in, *out;
  char c;
  int compt = 0;

  printf ("%s [Dump a text file to a C string] \n", VERSION);
  if (argc < 3)
    {
      printf ("USAGE :  mkhelp <document_name> <header_name>\n");
      exit (2);
    }

  if (access (argv[1], R_OK))
    {
      printf ("\nCan't read file : %s\n", argv[1]);
      exit (1);
    }

  in = fopen (argv[1], "r");
  out = fopen (argv[2], "w");

  fprintf (out, "/* Generated by %s */", VERSION);
  fprintf (out, "\nunsigned char %s_STRING[] = { \n", argv[1]);

  while ((c = getc (in)) != EOF)
    {
      fprintf (out, "%i, ", c);
      if (compt++ == 10)
	{
	  compt = 0;
	  fprintf (out, "\n");
	}
    }
  fprintf (out, "0 };\n/* End Of File*/\n");
  fclose (in);
  fclose (out);

  return 0;
}
