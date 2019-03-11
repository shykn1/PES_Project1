/**
*	@file 	Readme_autotest_result.txt
*	@brief	Check the result of the rudimentary autometed test is the same as the expectation of the result
*
*	@author 	Tim Chien		
*	@date 		Feb 25 2019 
*	@version  	1.0
*/

Commands from testscript file			Goal																				Expecxtation of the result																				Detail

C0												Print out all commands' information 								Print out information of C0 to C6

C2 2												Allocate two words (4-byte) memory to block 0					Success. An absoluted address for block 0														absolut address : A
 
C2 200											Allocate 512 words (4-byte) memory to block 1				Success. An absoluted address for block 1														absolut address : A + 0x000000000020

C3 2												Free the memory in Block 2											Failed, Block 2 has not been allocated

C3 1												Free the memory in Block 1											Success. Block 1 has been free

C3 1												Free the memory in Block 1											Failed. Block 1 has not been allocated

C0												Print out all commands' information 								Print out information of C0 to C6

C4 0 0 2										Display the data in Block 0 with offset 0 and range 2			Success. Two data in two absolute address are zero										absolut address  1 : A;	 	absolut address 2: A + 0x000000000004			

C4 0 1 1										Display the data in Block 0 with offset 1 and range 1			Success. One data in one absolute address is zero											absolut address  1 : A+ 0x000000000004 	

C4 1 0 3										Display the data in Block 1 with offset 0 and range 3			Failed. The range exceeds the boundary for this set of block and offset				Block 0 just has been allocated in 2 words (less than 3 (offset+range))

C4 0 1 2										Display the data in Block 0 with offset 1 and range 2			Failed. The range exceeds the boundary for this set of block and offset				Block 1 has been free

C5 0 0 0x123									Write memory words 0x123 to Block 0 with offset 0			Success. Data in the first address in Block 0 becomes 0x123

C5 0 1 0x1234								Write memory words 0x1234 to Block 0 with offset 1		Success. Data in the first address in Block 0 becomes 0x1234

C5 0 3 0x1234								Write memory words 0x1234 to Block 0 with offset 3		Failed. The offset exceeds the boundary for this block										Block 0 just has been allocated in 2 words (less than 3 (offset+range))

C5 1 0 0x1234								Write memory words 0x1234 to Block 1 with offset 0		Failed. The offset exceeds the boundary for this block										Block 1 has been free

C5 0 1 0x123412345						Write value 0x123412345 to Block 0 with offset 1				Failed. Data larger than 32-bit range

C4 0 0 2										Display the data in Block 0 with offset 0 and range 2			Success. Two data in two absolute address are 0x123 and 0x1234					absolut address  1 : A;	 	absolut address 2: A + 0x000000000004	

C6 0 0 2										Invert the data in Block 0 with offset 0 and range 2			Success. Print out the time cost.																	time cost is 144 ns

C6 0 0 3										Invert the data in Block 0 with offset 0 and range 3			Failed. The range exceeds the boundary for this set of block and offset				Block 0 just has been allocated in 2 words (less than 3 (offset+range))

C6 1 0 2										Invert the data in Block 1 with offset 0 and range 2			Failed. The range exceeds the boundary for this set of block and offset				Block 1 has been free

C6 0 2 2										Invert the data in Block 0 with offset 2 and range 2			Failed. The range exceeds the boundary for this set of block and offset				Block 2 has not been allocated

C4 0 0 2										Display the data in Block 0 with offset 0 and range 2			Success. Two data in two absolute address are 0xfffffedc and 0xfffffedcb 			inverted value of 0x123 and 0x1234

C1												Exit																				Go back to Terminal

