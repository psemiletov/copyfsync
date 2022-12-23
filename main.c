#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <libgen.h>

//10 MB
//#define BUFSIZE 104857600

//const int BUFSIZE = 1048576;

//const int BUFSIZE = 1048576 * 4;




size_t get_file_size (const char *filename)
{
  struct stat file_status;
  if (stat(filename, &file_status) < 0)
      return -1;


  return file_status.st_size;
}



int main(int argc, char *argv[])
{
  int DYNBUFSIZE = 1048576 * 2;


  FILE *file_in;
  FILE *file_out;

  char *buf;

  char *fname_in = 0;
  char fname_out[4096] = {0};

  size_t bytes_total = 0;
  size_t bytes_total_readed = 0;

  size_t bytes_readed;
  size_t bytes_to_write;

  if (argc < 3)
    {
     printf ("============================\n");
     printf ("copyfsync by Peter Semiletov\n");
     printf ("============================\n");

     printf ("The utility to copy file with synchronize \n");
     printf ("after each copying iteration.\n");
     printf ("Good for copy large file to USB stick.\n");

     printf ("============================\n");

     printf ("Usage:\n");


     printf ("copyfsync filename destnation_dir\n");
     printf ("or\n");
     printf ("copyfsync buffer_size filename destnation_dir\n");

    printf ("\n");

   printf ("Examples...\n");

   printf ("Copy movie.avi to /run/media/rox/FLASHDRIVE/:\n");

   printf ("copyfsync movie.avi /run/media/rox/FLASHDRIVE/\n");

   printf ("Copy movie.avi to /run/media/rox/FLASHDRIVE/ with 4 MB buffer (default 2 MB):\n");

   printf ("copyfsync 4 movie.avi /run/media/rox/FLASHDRIVE/\n");


   printf ("============================\n");
   printf ("If you like this program you can donate via:\n");
    printf ("Paypal: peter.semiletov@gmail.com\n");
     printf ("BTC: 1PCo2zznEGMFJey4qFKGQ8CoFK2nzNnJJf\n");
     printf ("============================\n");

     return 0;
    }

  if (argc == 4)
    {
     //argv[1] is the buffer size in MB

     char *ptr;
     long ret;

     DYNBUFSIZE  = strtol(argv[1], &ptr, 10) * 1048576;


     fname_in = argv[2];

     strcat (fname_out, argv[3]);
     strcat (fname_out, "/");
     strcat (fname_out, basename (argv[2]));

     printf ("fname_out: %s\n", fname_out);
     printf ("DYNBUFSIZE: %d\n", DYNBUFSIZE);

    }
  else
  if (argc == 3)
    {
     fname_in = argv[1];

     strcat (fname_out, argv[2]);
     strcat (fname_out, "/");
     strcat (fname_out, basename (argv[1]));

     printf ("fname_out: %s\n", fname_out);
    }


    //file_in = fopen("/home/rox/devel/syncopy/1.txt", "r");

  //file_in = fopen("/mnt/big1/mus/KINOSHKI/Polustanok_DVDRip.avi", "r");
  //file_in = fopen (argv[1], "r");
   file_in = fopen (fname_in, "r");


  if (! file_in)
      {
      perror("cannot open file\n");
      exit(1);
     }



  buf = (char*) malloc(DYNBUFSIZE);


  bytes_total = get_file_size (fname_out);

  printf("\rFile size MB:%u\n",bytes_total / 1048576);



   file_out = fopen (fname_out, "w+");


   if (! file_out)
      {
      printf("cannot create file %s\n", fname_out);
      exit(1);
     }

     int file_out_no = fileno (file_out);


   printf("1111 \n");

   while (1)
        {

           bytes_readed = fread(buf, sizeof(char), DYNBUFSIZE, file_in);



        if (bytes_readed)
           {

            bytes_total_readed += bytes_readed;


            printf("\rMB Wrote %u", bytes_total_readed / 1048576);


            fflush(stdout);
            int r = fwrite(buf, sizeof (char), bytes_readed, file_out);



            fflush(file_out);
            //fsync(file_out_no);

            fdatasync (file_out_no);



           }
        else
            {
             if (ferror(file_in))
                perror( "Error reading myfile" );
             else if (feof(file_in))
                   perror( "EOF found" );
             break;
            }


      }


   free (buf);

   fclose(file_in);
   fclose(file_out);

   printf("\n");

   printf("good \n");


   return 0;
}
