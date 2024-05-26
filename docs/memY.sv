/******************************************************************************************
   MODULE NAME: memY
   FILENAME: memY.sv
   DESCRIPTION: It is the memory in which some data is saved to perform the convolution, 
                this data can be defined by the user

   PARAMETERS:
         DATA_WIDTH -> Defines the number of bits that the data to save will have
         ADDR_WIDTH -> Defines the number of bits needed to write memory addresses
         SIZE -> Defines the number of data that has been saved in memory
   
   AUTHOR: Fernando Gallo Hinojosa
   EMAIL: TAE2024.18@cinvestav.mx

   DATA: 5/05/2024
******************************************************************************************/

module memY (
  input logic clk,
  input logic [2:0] address,
  input logic [7:0] writeData,
  input logic writeEnable,
  input logic readEnable,
  output logic [7:0] readData
);

  logic [7:0] memory [0:4];

  // Carga de datos desde el archivo .txt al inicializar
  initial begin
    $readmemh("C:/Quartus/memY.txt", memory);
  end

  // Procesos de escritura y lectura sincrónicos
  always @(posedge clk) begin
    if (writeEnable)
      memory[address] <= writeData;
    
    if (readEnable)
      readData <= memory[address];
  end

endmodule
