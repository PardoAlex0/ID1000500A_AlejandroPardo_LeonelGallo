/******************************************************************************************
   MODULE NAME: Convolucion
   FILENAME: Convolucion.sv
   DESCRIPTION: State machine of the convolution process

   PARAMETERS:
        
   AUTHOR: Fernando Gallo Hinojosa
   EMAIL: TAE2024.18@cinvestav.mx

   DATA: 5/05/2024
******************************************************************************************/

module Convolucion (
  input logic clk,
  input logic reset,
  output logic done
);
  // Estados de la máquina de estados
  typedef enum logic [2:0] {
    IDLE,
    LOAD_MEMY,
    LOAD_MEMX,
    CONVOLUTION,
    WRITE_MEMZ,
    FINISH
  } State;

  State current_state, next_state;

  // Señales de control para la máquina de estados
  logic memY_leerHabilitar, memX_leerHabilitar, memZ_escribirHabilitar;
  logic [2:0] direccion_memY, direccion_memX, direccion_memZ;
  logic [7:0] datos_memY, datos_memX, datos_memZ;

  // Declaración de señales adicionales
  logic start_convolution;
  logic [2:0] direccion_actual;
  logic memY_data_ready, memX_data_ready;
  logic [7:0] memY_datos_memY, memX_datos_memX;
  logic convolution_done;
  logic [7:0] resultado_convolucion;
  logic memZ_write_done;
  logic [2:0] direccion_final;

  // Instanciar los módulos de memoria
  memY memY_inst (
    .clk(clk),
    .address(direccion_memY),
    .writeData(datos_memY),
    .writeEnable(memY_leerHabilitar),
    .readEnable(memY_leerHabilitar),
    .readData(datos_memY)
  );

  memX memX_inst (
    .clk(clk),
     .address(direccion_memX),
    .writeData(datos_memX),
    .writeEnable(memX_leerHabilitar),
    .readEnable(memX_leerHabilitar),
    .readData(datos_memX)
  );

  memZ memZ_inst (
    .clk(clk),
    .address(direccion_memZ),
    .writeEnable(memZ_escribirHabilitar),
    .writeData(datos_memZ),
    .readEnable(memY_leerHabilitar),
    .readData(datos_memY | datos_memX)
  );

  always_ff @(posedge clk) begin
    if (reset) begin
      current_state <= IDLE;
      memY_leerHabilitar <= 0;
      memX_leerHabilitar <= 0;
      memZ_escribirHabilitar <= 0;
    end 
    else begin
      current_state <= next_state;
      memY_leerHabilitar <= 0;
      memX_leerHabilitar <= 0;
      memZ_escribirHabilitar <= 0;
      direccion_memY <= 0;
      direccion_memX <= 0;
      direccion_memZ <= 0;
      datos_memY <= 0;
      datos_memX <= 0;
      datos_memZ <= 0;
    end
    
      case (current_state)
        IDLE: begin
                if (start_convolution) begin
                  next_state = LOAD_MEMY;
                end
              end
        LOAD_MEMY: begin
                      memY_leerHabilitar <= 1;
                      direccion_memY <= direccion_actual; // Asignar la dirección actual
                      if (memY_data_ready) begin
                        next_state = LOAD_MEMX;
                      end
                   end
        LOAD_MEMX: begin
                         memX_leerHabilitar <= 1;
                         direccion_memX <= direccion_actual; // Asignar la dirección actual
                         if (memX_data_ready) begin
                           next_state = CONVOLUTION;
                         end
                     end
        CONVOLUTION: begin
                       //Realizar la convolución utilizando los datos obtenidos de las memorias
                       //y guardar el resultado en resultado_convolucion
                      integer i, j;
                      logic [15:0] suma;
                      suma = 0;

                      for (i = -1; i <= 1; i = i + 1) begin
                        for (j = -1; j <= 1; j = j + 1) begin
                          suma = suma + (memY_datos_memY[i+direccion_actual] * memX_datos_memX[j+direccion_actual]);
                        end
                      end

                      resultado_convolucion = suma[7:0];

                      if (convolution_done) begin
                        next_state = WRITE_MEMZ;
                      end
                     end
        WRITE_MEMZ: begin
                      memZ_escribirHabilitar <= 1;
                      direccion_memZ <= direccion_actual; // Asignar la dirección actual
                      datos_memZ <= resultado_convolucion;
                      if (memZ_write_done) begin
                        if (direccion_actual == direccion_final) begin
                          next_state = FINISH;
                        end else begin
                          next_state = LOAD_MEMY;
                        end
                      end
                     end
        FINISH: begin
                  done = 1;
                end
      endcase
    end
endmodule

