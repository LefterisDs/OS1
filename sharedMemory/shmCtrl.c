#include "shmCtrl.h"


key_t create_store_shmemkey(const char* pathname, int proj_id , const char* keyfile){

   key_t shmkey;
   int shm_fd;

   if((shmkey = ftok(pathname , proj_id)) < 0){
     perror("Couldn't create a key with ftok!");
     return(-1);
   }

   shm_fd = open(keyfile , O_WRONLY | O_TRUNC | O_EXCL | O_CREAT , 0644);

   if (shm_fd < 0){
     perror("Could not open sem.Paintkey");
     return(-1);
   }

   if (write(shm_fd , &shmkey , sizeof(key_t)) < 0){
     perror("Could not write key to file");
     return(-2);
   }

   close(shm_fd);

   return shmkey;
}


key_t get_shmemkey(const char* keyfile){

   int shm_fd;
   key_t shmkey;

   shm_fd = open(keyfile , O_RDONLY);

   if (shm_fd < 0){
     perror("Could not open file");
     return(-1);
   }

   if (read(shm_fd , &shmkey , sizeof(key_t)) != sizeof(key_t)){
     perror("Could not read key from file");
     return(-2);
   }

   return shmkey;
}

int shm_delete(int shmid){
   if(shmctl(shmid , IPC_RMID , 0) < 0){
      perror("shared memory delete error!");
      return -1;
   }
   return 0;
}
