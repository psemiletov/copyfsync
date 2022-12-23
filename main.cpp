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

inline float get_percent (float total, float value)
{
  return (float) value / total * 100;
}


int main(int argc, char *argv[])
{
  int DYNBUFSIZE = 1048576 * 2;


  FILE *file_in;
  FILE *file_out;

  //char *buffer;

//  char buffer[BUFSIZE] = {0};

  char *buf;

  char *fname_in = 0;
  char fname_out[4096] = {0};

  size_t bytes_total = 0;
  size_t bytes_total_readed = 0;

  size_t bytes_readed;
  size_t bytes_to_write;

  if (argc < 3)
     return 0;

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


  //file_in = fopen(argv[1], "r");
  //file_out = fopen(argv[2], "w");

  buf = (char*) malloc(DYNBUFSIZE);
  //memset (buf, 0, BUFSIZE);

//  bytes_total = get_file_size ("/mnt/big1/mus/KINOSHKI/Polustanok_DVDRip.avi");

  bytes_total = get_file_size (fname_out);

  printf("\rFile size MB:%u\n",bytes_total / 1048576);


  //file_out = fopen ("/run/media/rox/FLASHDRIVE/Polustanok_DVDRip.avi", "w+");

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
//         bytes_readed = fread(buffer, sizeof(char), BUFSIZE, file_in);

           bytes_readed = fread(buf, sizeof(char), DYNBUFSIZE, file_in);


        //printf("222 \n");


        if (bytes_readed)
           {  // fread success

            bytes_total_readed += bytes_readed;
//            float d = get_percent ((float) bytes_total, (float)bytes_total_readed);


            //float d = (float) bytes_total / (float) bytes_total_readed;

            //printf("Number of characters has been read = %i\n", bytes_readed);
            //printf("buffer = %s\n", buffer);

            //printf("\r%.2f%%", d);
            //printf("\n");

            //printf("\rBytes wrote %u from %u", bytes_total_readed, bytes_total);

            printf("\rMB Wrote %u", bytes_total_readed / 1048576);


            fflush(stdout);
            //int r = fwrite(buffer, sizeof (char), bytes_readed, file_out);
            int r = fwrite(buf, sizeof (char), bytes_readed, file_out);



            fflush(file_out);
            fsync(file_out_no);

         //   printf("buffer write done\n");


           }
        else
            {
             if (ferror(file_in))
                perror( "Error reading myfile" );
             else if (feof(file_in))
                   perror( "EOF found" );
             break;
            }

       //printf("333 \n");

      }

   //r = fwrite(file, A, strlen(A));
   //if (r < -1) {
     // perror("write()");
      //exit(1); }

   //fsync(file_out);

   free (buf);

   fclose(file_in);
   fclose(file_out);

   printf("\n");

   printf("good \n");


   return 0;
}
