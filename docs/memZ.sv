/******************************************************************************************
   MODULE NAME: memZ
   FILENAME: memZ.sv
   DESCRIPTION: It is the memory in which the result of the convolution is stored

   PARAMETERS:
         DATA_WIDTH -> Defines the number of bits that the data to save will have
         ADDR_WIDTH -> Defines the number of bits needed to write memory addresses
   
   AUTHOR: Fernando Gallo Hinojosa
   EMAIL: TAE2024.18@cinvestav.mx

   DATA: 5/05/2024
******************************************************************************************/

module memZ (
  input logic clk,
  input logic [2:0] address,
  input logic writeEnable,
  input logic [7:0] writeData,
  input logic readEnable,
  output logic [7:0] readDataX,
  output logic [7:0] readDataY
);

  // Declaración de la memoria con elementos separados para datos X e Y
  reg [7:0] memoryX [0:4];  // Memoria para datos X
  reg [7:0] memoryY [0:4];  // Memoria para datos Y

  always @(posedge clk) begin
    if (writeEnable) begin
      // Se escriben los datos según el bit menos significativo de la dirección
      // Las direcciones pares (0, 2, 4) almacenan datos X
      // Las direcciones impares (1, 3) almacenan datos Y
      if (address[0] == 0) begin
        memoryX[address] <= writeData;
      end else begin
        memoryY[address] <= writeData;
      end
    end

    if (readEnable) begin
      // Se leen los datos según la dirección
      readDataX <= memoryX[address];
      readDataY <= memoryY[address];
    end
  end

endmodule

