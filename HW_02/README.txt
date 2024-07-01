# PROJECT : HW_02
- To implement a c progam for search system call that prints the directories and files in hireracal manner with options -S, -s, -f, -t f and -t d.

# COMPILATION & EXECUTION
- We can compile the program with 
    - make 
    - gcc -o a pyata_HW_02.c
- This compilation command convers the c file into executable a file.
- Now execute the following command : 
    - ./a
    - ./a ../HW_02
    - ./a ../HW_01
    - ./a -S
    - ./a -s 5024
    - ./a -f proj 4
    - ./a -t f
    - ./a -t d
    - ./a -S -s 5024 -f proj 4 -t f

# PROGRAM
- The program calls the directories_and_files and depending on the options it prints the outputs.
- The main function has the following options :     
    1. option_S
    2. Option_s, option_s_max_file_size
    3. option_f_stringPattern, option_f_max_depth
    4. option_t, option_tf, option_td
- These variable values are assigned based on the arguments that are specified.
- Then the main function calls the directories_and_files function to print the files hireracally.
- Depending on the options or arguments passed, the function will call the following function :     
    - symbolic_link_file : This function returns the sysmbolic link file
    - file_permissions : This function prints the permission of the files
    - print_option_S : this function prints teh details of the files that passed.
- pointerAsFunction function is used to pass the function as a pointer.


# The outputs are : 
![alt text](image.png)
![alt text](image-1.png)
![alt text](image-2.png)
![alt text](image-3.png)