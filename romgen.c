// Tool for converting ordinary binary file into case statement
// to be inferred as ROM with Lattice Synthesis Engine.
// Crappy coded by TinLethax 2022/05/16 +7
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int main(int argc, char *argv[]){
	uint8_t temp_read; 
	FILE *fpbin;// for Binary file
	FILE *fpcase;// for output case statement.

	//scan for help
	for(int i = 0; i < argc; i ++){
		if( (strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0) ){
			printf("iCE40 ROM generator v1.0\n");
                	printf("Coded by TinLethax\n");
                	printf("\nUsage : ");
                	printf("romgen [input binary] [input binary size] [address bit width] [output filename]\n");
                	printf("\nExample :\n");
                	printf("  romgen epp_font.bin 1024 10 rom_case.v\n");
			return 0;
		}
	}


	switch(argc){
	case 1:
		printf("iCE40 ROM generator v1.0\n");
		printf("Coded by TinLethax\n");
		printf("\nUsage : ");
		printf("romgen [input binary] [input binary size] [address bit width] [output filename]\n");
		printf("\nExample :\n");
		printf("  romgen epp_font.bin 1024 10 rom_case.v\n");	
		return 0;
	case 2:
	case 3:
	case 4:
		printf("romgen require at lease 4 arguments!\n");
		printf("See romgen -h or romgen --help\n");
		return 0;
	case 5:
		break;
	}

	// Open binary file
	fpbin = fopen(argv[1], "rb");
	if(fpbin == NULL){
		printf("%s is not found!\n", argv[1]);
		return 0;
	}
	
	int bin_size, bit_size;
	bin_size = atoi(argv[2]);
	bit_size = atoi(argv[3]);
	printf("Binary size : %d\n", bin_size);
	printf("Bit width : %d\n", bit_size);
	// Open and create output file
	fpcase = fopen(argv[4], "w");
	
	// write case(addr).
	fprintf(fpcase, "module rom(data, addr);\n");
	fprintf(fpcase, "\toutput reg [7:0] data  /* synthesis syn_romstyle = \"BRAM\" */;\n");
	fprintf(fpcase, "\tinput [%d:0] addr;\n", bit_size - 1); 
	fprintf(fpcase, "\talways @(addr) begin\n");
	fprintf(fpcase, "\t\tcase(addr)");

	// write each ROM address.
	for(int i=0; i < bin_size; i++){
		fread(&temp_read, sizeof(uint8_t), 1, fpbin);
		fprintf(fpcase, "\n\t\t\t%d: data = 'h%x;", i, temp_read);
	}

	// default case
	fprintf(fpcase, "\n\t\t\tdefault : data = 'h0;");
	// write endcase
	fprintf(fpcase, "\n\t\tendcase\n");
	fprintf(fpcase, "\tend\n");
	fprintf(fpcase, "endmodule");
	// Done
	fclose(fpcase);
	fclose(fpbin);

	printf("Done \n");

	return 0;
}

