-----------------------------------------------------Circular buffer-----------------------------------------------------------------
							cirbuff.c
1. Structure of appropriate members has been created (head, tail, buff, count, size)
2. In CircBuf_size size is allocated to a structure(defined in cirbuff.h ) pointer 
   on the heap, followed by buffer initialization, where memory of size uint8_t 
   is being allocated to a pointer  buff on the heap and head, tail are initially 
   made to point to the first position,buff always points to first position 
   in the circular buffer
3. is_buffer_empty and is_buffer_full will check whether the buffer is empty of full 
   by comparing structure member count and size. If count zero buffer is empty, and if 
   count is equal to size buffer is full
4. The size given to the buffer on the heap is destroyed by free(ptr)
5. add_item, an item is added in the circular buffer by first calling initialize_buffer
   and then adding the item by dereferencing the head pointer and then incrementing the 
   head pointer, this function takes care of wrap_around_condtion on itself
6. remove_item the data is first read at the tail position, then the tail is incremented
   by one place. This function also takes care of the wrap_around_condition.
7. CircBuf_peak: This function gives value of the data at required index in the circular
   buffer.

							cirbuff.h
All the functions used in the cirbuff.c are defined in this file. Structure and enum are 
defined in the header file and include guard is included in this file to avoid the redefi-
nition of the commands. All the function operations and function parameters and returns 
are well explained in the comments.

							uni.h
This header file includes an enum which has return status of all the functions in the source files. This file is included in all source files and all test.c files.


----------------------------------------------------------UNIT TESTS------------------------------------------------------------------

                                                  	test_data.c - 

Unit tests for Invalid pointer, functionality big_to_little32 and little_to_big32 are included in this file. (stdlib, stdio, stdarg, stddef, setjmp, cmocka libraries are included in test_data.c). data.h and uni.h are included in the in the test_data.h. 
All the unit test functions call appropriate function which are defined in the .h files. For testing
cmocka unit test framework is used.
This test returns PASS or FAIL for each unit test function. 
Total 4 tests

-------------------------------------------------------test_memory.c------------------------------------------------------------------
                                                    	memmove - 
Unit test functions for Invalid pointer, No overlap, Source in Destination, Destination in source is written and the output of "make test" will give PASS or FAIL for each of the unit tests by chekcing the functionality of the code and using cmocka uint test framework.
                                                   	 memset -
Unit test functions for Invalid pointer and Check_set are included in this file. The output of the command
"make test" will give PASS or FAIL for each of the unit tests by chekcing the functionality of the code and using cmocka unit test framwork.
                                                    	memzero -
Unit test functions for Invalid pointer and Check_set are included in this file. The output of the command
"make test" will give PASS or FAIL for each of the unit tests by chekcing the functionality of the code and using cmocka unit test framwork.
                                                   	my_rev -
Uint test functions for Invalid pointer, Odd reverse, even reverse and character set reverse included in the file and the output of the command "make test" will give either PASS or FAIL, based on the functionality of the code and cmocka unit test framwork.
Total - 12 tests

-----------------------------------------------------test_cirbuff.c-------------------------------------------------------------------
Unit tests for Allocate-free, Invalid Pointer, NonInitialized buffer, Buffer full, buffer empty, wrapadd, wrapremove, overfill, overempty and Add-Remove are included in the file. The output of the command "make test" will either give PASS or FAIL depending upon the functionality of the code and cmocka unit 
test framework. 
Total - 10 tests (stdlib, stdio, stdarg, stddef, setjmp, cmocka libraries included)
--------------------------------------------------------Test.c------------------------------------------------------------------------
It has the conglomeration of all the unit test functions described above, when prompted a "make test" command it will give PASS or FAIL for each of the unit test functions included (total = 26). All the header files (cirbuff.h, data.h, memory.h uni.h) are included in this file. 
Total - 26 tests (stdlib, stdio, stdarg, stddef, setjmp, cmocka libraries included)

--------------------------------------------------------Makefile--------------------------------------------------------------
Changed the path of THIRD_PARTY_DIR to libraries. Then added the conditional loop which will select the source file on which the unit tests need to be performed. If TEST="data" then "make test" will run uint tests of test_data.c for TEST="memory" test_memory.c and if nothing is specified the same command will give all unit tests for all the test.cs. This make file also has log-host and log-bbb.

---------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------Logger Application------------------------------------------------------------------
The logger application has main use of interacting with devices that do not support standard input output functions like FRDM. For this we have written c programs stored in the folder named log. Description of each C file is given below

UART.c/h
In this C file we have written functions that help us to communicate to and from the device using UART. We have functions that can do this by both polling as well as interrupts. UART_init() is used to initialize the UART0 at PINS 1 and 2 of port A. Function sendbyte, receivebyte, sendnbyte use polling to transmit and receive data. send_n_bytes() receive_n_bytes() use interrputs to achieve the same objective. We have also written an IRQ handler to manage interrupts.

cirbuff.c
Refer to the previous explanation. 

analysedata.c
This c file includes functions that perform important data calculations in order to obtain the functionality of identifying the input characters as alphabets, numbers, punctuations and misc. This is done by the function name analyse_data(). Another function defined in this c file is my_itoa(). Here data, base, destination address are passed as parameters and the function returs the starting address of the destination. This function converts the given data into an ascii string, while also converting the number into the specified base. The string stored at the destination address is null terminated.

Logger.c 
This the most essential part of the whole application the functions in the c file are used to log different kinds of data strings, integer or just generic data. The function log_data(), takes a data pointer and length as parameters and logs the data uptil specified length using UART for FRDM and Printf for the host machine. Function log_string() does not have length as its parameteres and hence it calculates the length uptil the null character. Now the pointer and length are passed to log_data(). 
log_integer() converts an input integer data to an ascii string whose starting address is passed log_string(). log_flush() is used to flush out data from any given circular buffer through the transmit buffer and hence displaying contents of the buffer via UART for FRDM and printf for host machine. 
Create_log_item() initializes log structure with values. It assigns log ID, length and PAYLOAD to the structure pointer passed as a parameter. log_item() is used to display or log items depending on the log structure initialization it passes the contents of log strctures log_data(), log_string(), log_integer().
In order to perform logging we always need to create a log item and then call log_item(). To overcome repeated calling of two functions we have defined a macro LOGIT.




							



