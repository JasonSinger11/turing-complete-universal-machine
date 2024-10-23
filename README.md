# Universal-Machine

Names: Jason Singer and Anna Zou

What has been correctly implemented: Everything (hopefully !)

Departures from design: We created a 3rd module for operations, found in the
op.c and op.h files. We also did not fully understand some instructions like
load program, but mostly stuck to the design we had layed out

Architecture of the System:


UM module:

The UM is represented mainly by the UM module (um.c and um.h). At the highest
level, there is a UM struct, containign an array of 32bit registers, a pointer
to the allSegments struct (segments module), a program counter that keeps track
of what number instruction is being executed, and a pointer to an array of 
function pointers that represents the 3 register operations (operations module)

Secrets known:
- Eight Registers are only accesible and modifyable within the UM module
- pointer to inilized allSegments struct only accesible within UM module
- program counter only known and modifyable by the UM module
- pointer to function array of operations only inilized in this module


Segment module:

The segments, along with the memory allocated to each segment, are represented 
using the segment module (seg.c & seg.h). Two structs – one of type allSegments
and the other of type segment – are privately defined in the implementation 
file seg.c. The seg module also contains helper functions initializing, 
retrieving, freeing, and duplicating individual segments. 


Secrets Known
-  Hansen Sequences for mapped and unmapped segments only accesible and mutable
        in this module
- Instances of segment structs, including the ability to allocate and free 
        memory associated with segments, and the number of words within a 
        segment
- Changing or directly accesing the memory associated with a given segment only
        available in this module without the use of getters/setters

Operation module: 

Functions responsible for carrying out individual operations are represented 
using an op module (op.h & op.c). There is an array of function pointers of 
type void func_ptr (unsigned rA, unsigned rB, unsigned rC, Um universe) that 
points to all the operation functions except for load value.

How the segment & operation module work together: Whenever the UM encounters 
a segment-based instruction (e.g. map_segment), the corresponding function 
in op.c will call helper functions in seg.c dealing with certain operations 
(e.g. init_segment) that need to be performed upon selected segments.

Scerets Known:
- Contains definitions of the operation functions pointed to in the UM module,

For the most part, the operations module uses the client available functions in
the UM and segment modules together to preform the instuctions.


List of UM tests

    halt: tests whether the halt instruction terminates the execution loop 
    and the program

    halt-verbose: tests whether the loadval AND the halt instructions are 
    working correctly by checking whether the UM outputs the designated output 
    "BAD!" and then terminates. (This is a modifyed version from the lab 
    that is supposed to print BAD!)

    add: tests whether the add instruction alone works correctly.
        Since there is no output in this test, we used our print_register() 
        function to ensure that our registers were storing the correct value
        after the instructions had been carried out.

    print-six: tests whether the add instruction AND the output 
    instruction are working correctly by checking if the UM prints out the 
    correct value. 

    inNout: tests whether the input instruction works correctly by checking if 
    the UM actually receives our input and outputs it again. Done by calling 
    the input and output functions on the same register.

    multiply: tests whether the multiply instruction works correctly by 
    checking if the UM outputs the correct product of the two values loaded.
    Since there is no output in this test, we used our print_register() 
    function to ensure that our registers were storing the correct value
    after the instructions had been carried out.

    multiply-big: tests whether the multiply instruction works correctly for 
    large products where not all of its bits could be represented but the 
    multiply instruction is expected to save the rightmost 32 bits.
    Done by calling multiply on two registers that have extremely large vals
    loaded into them  Since there is no output in this test, we used
    our print_register()  function to ensure that our registers were 
    storing the correct value after the instructions had been carried out.

    build_divide: tests whether the divide instruction works correctly by 
    checking if the UM outputs the correct quotient of the two values loaded.
    Done by calling loadval on two registers, calling divide on the two 
    registers and storing the 

    NAND:  tests the bitwise NAND operation on two identical values by 
    calling loadval on two registers with the same vals, then calling nand 
    on those registers. We checked the correct value using the 
    print_register() function (since this function) has no output, and checked 
    the value matched the output of an online NAND checker


    NAND_same: tests the bitwise NAND operation on two identical values by 
    calling loadval on two registers with the same vals, then calling nand 
    on those registers. We checked the correct value using the 
    print_register() function (since this function) has no output, and checked 
    the value matched the output of an online NAND checker


    seg_store: tests if map_segment, segment store, and segment load are  
    working correctly by checking whether the initial value in rC gets loaded 
    into the corresponding segment m[rA][rB] AND whether that value gets 
    loaded back to rC. For this test the UM will output the original value 
    stored in rC.

    load_p: tests the load program instruction. The UM is expected to skip
    a divide instruction that causes a seg fault if load program is implemented
    correctly AND output 100 as the value for a particular register. 

    map_and_unmap: Tests the mapping function by mapping a segment and then 
    the unmapping function by unmapping that segment. We then used print 
    statements throughout the two functions to show that the size of the two
    sequences correctly changed thoughout the test.

    test_all: a holistic test that covers the majority of the 14 instructions 
    (e.g. load program, load value, add, load segment)output instructions are
    inserted along the way to check whether the correct values are loaded into 
    the registers after many instructions have been run.

    map_unmap_remap: calls the mapping function, then unmapping function, 
    then the mapping function again to test the process of unmapped IDs being 
    reused. The value in the registers is outputted twice (one time after 
    adding 90 to make it a readable ASCII value), before and after the
    unmapping to show that the semgent ID is reused/

    print_abc: tests if the add and output instructions work correctly using  
    a loop to increment the starter value (97 in this case) by 1 each time for 
    26 times. The UM is expected to print out a complete set of the 26-letter 
    alphabet.Calls the loadval function on the ascii chracter a, then adds 1
    26 times and output to print the alphabet. 
    
    build_cmov: tests if the conditional move instruction works correctly; the 
    test consists of a case where rC ! 0 and another where rC == 0. In the  
    first case the UM is expected to output the intended value for rA, while 
    in the second case rA is expected to maintain its value from the previous 
    case.
