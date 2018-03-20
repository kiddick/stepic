fd_set watch_list;

FD_ZERO(&watch_list); - null all
FD_SET(f1, &watch_list); //-- look for f1
FD_CLR(f1, &watch_list); // except f1 from looking

int select(number_of_fd, fd_set_read, fd_set_write, fd_set_except, time_wait);
// return number of ready descriptors
FD_ISSET(f1, &watch_list)
